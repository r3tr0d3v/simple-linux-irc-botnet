#ifndef __SCKT_H__
#define __SCKT_H__

int get_socket(char *domain, char *port);
int sckt_send(int s, char *buffer, size_t len);
int sckt_sendf(int s, char *fmt, ...);
int sckt_recv(int s, char *buffer, size_t len);

#endif /* __SCKT_H__*/