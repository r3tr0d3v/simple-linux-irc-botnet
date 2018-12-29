#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

typedef struct
{
   int sockfd;
   FILE *file;
   char channel[256];
   char *nick;
   char *username;
   char *server;
   char *port;
} irc_t; 



irc_t *create_irc_ctx(char *nick, char *server, char *port);

/* Protocol Functions */
int irc_nick(irc_t *irc);
int irc_user(irc_t *irc, char *hostname);
int irc_ping(irc_t *irc, char *name);
int irc_pong(irc_t *irc);
int irc_join(irc_t *irc, char *channel);
int irc_part(irc_t *irc);
int irc_private_message(irc_t *irc, char *nick, char *message);
int irc_quit(irc_t *irc, char *reason);

#endif /* __PROTOCOL_H__ */