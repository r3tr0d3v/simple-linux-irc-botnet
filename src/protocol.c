#include "includes.h"

irc_t *create_irc_ctx(char *nick, char *server, char *port)
{
	irc_t *irc = malloc(sizeof(irc_t));

	if (irc == NULL)
		return NULL;

	irc->nick = nick;
	irc->server = server;
	irc->port = port;

	sleep(1);

	irc->username = rand_string(50);

	irc->sockfd = get_socket(irc->server, irc->port);

	return irc;
}

int irc_nick(irc_t *irc)
{
	if (sckt_sendf(irc->sockfd, "NICK %s\r\n", irc->nick) <= 0)
		return -1;

	return 0;
}

int irc_user(irc_t *irc, char *hostname)
{
	if (sckt_sendf(irc->sockfd, "USER %s %s %s :%s\r\n", irc->username, hostname, irc->server, "parrot") <= 0)
		return -1;

	return 0;
}

int irc_ping(irc_t *irc, char *name) 
{
	if (sckt_sendf(irc->sockfd, "PING %s\r\n", name) <= 0)
		return -1;

	return 0;
}

int irc_pong(irc_t *irc)
{
	if (sckt_sendf(irc->sockfd, "PONG %s\r\n", irc->nick) <= 0)
		return -1;

	return 0;
}

int irc_join(irc_t *irc, char *channel)
{
	strncpy(irc->channel, channel, sizeof(irc->channel));

	if (sckt_sendf(irc->sockfd, "JOIN %s\r\n", irc->channel) <= 0)
		return -1;

	return 0;
}

int irc_part(irc_t *irc)
{
	if (sckt_sendf(irc->sockfd, "PART %s\r\n", irc->channel) <= 0)
		return -1;

	return 0;
}

int irc_private_message(irc_t *irc, char *receiver, char *message)
{
	if (sckt_sendf(irc->sockfd, "PRIVMSG %s :%s\r\n", receiver, message) <= 0)
		return -1;

	return 0;
}

int irc_quit(irc_t *irc, char *reason)
{
	if (reason == NULL)
	{
		if (sckt_send(irc->sockfd, "QUIT\r\n", 4) <= 0)
			return -1;
	}
	
	if (sckt_sendf(irc->sockfd, "QUIT :%s\r\n", reason) <= 0)
		return -1;

	return 0;
}