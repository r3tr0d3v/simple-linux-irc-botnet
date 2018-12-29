#include "includes.h"

int get_socket(char *server, char *port) 
{
    struct addrinfo hints, *res;
    int result;
    int sockfd;

    memset(&hints, '\0', sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    result = getaddrinfo(server, port, &hints, &res);

    if (result != 0)
    {
    	fprintf(stderr, "%s\n", gai_strerror(result));
    	freeaddrinfo(res);
    	return -1;
    }

    sockfd = socket(res->ai_family, res->ai_socktype, 0);

    if (sockfd < 0)
    {
    	perror("socket");
    	freeaddrinfo(res);
    	return -1;
    }

    if ( connect(sockfd, res->ai_addr, res->ai_addrlen) < 0)
    {
    	perror("connect");
    	freeaddrinfo(res);
    	return -1;
    }

    freeaddrinfo(res);
    return sockfd;
}

int sckt_send(int s, char *buffer, size_t len)
{
    size_t sent;

    sent = send(s, buffer, len, 0);

    if (sent != len)
    {
    	fprintf(stderr, "Error Sending Message!\n");
    	return -1;
    }

    return sent;
}

int sckt_sendf(int s, char *fmt, ...)
{
	char send_buf[2048];
	int send_len;
	va_list args;

	if (strlen(fmt) != 0)
	{
		va_start(args, fmt);
		send_len = vsnprintf(send_buf, sizeof (send_buf), fmt, args);
    	va_end(args);

    	if (send_len > 2048)
    		send_len = 2048;

    	if(sckt_send(s, send_buf, send_len) <= 0)
    		return -1;
	}

	return send_len;
}

int sckt_recv(int s, char *buffer, size_t len)
{
	int r;

	r = recv(s, buffer, len, 0);
	if (r <= 0)
		return -1;

	return 0;
}