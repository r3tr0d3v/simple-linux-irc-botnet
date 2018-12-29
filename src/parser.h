#ifndef __IRC_PARSER_H__
#define __IRC_PARSER_H__

#include "protocol.h"

typedef struct 
{
	char command[256];
	char parameter1[256];
	char parameter2[256];
	char parameter3[256];
	char parameter4[256];
} parser_t;

parser_t parser;

void parse_action(char *buffer, size_t len);
void handel_action(irc_t *irc);

#endif /* __IRC_PARSER_H__ */