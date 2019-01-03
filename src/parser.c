#include "includes.h"

void parse_action(char *buffer, size_t len)
{
	char *tmp;

	tmp = strtok(buffer, " ");

	if (strncmp(tmp, "PING", 4) == 0)
	{
		strncpy(parser.command, tmp, sizeof(parser.command));
		tmp = strtok(NULL, " ");
		strncpy(parser.parameter1, tmp, sizeof(parser.parameter1));
	}

	else if (strncmp(tmp, "view-file", 9) == 0)
	{
		strncmp(parser.command, tmp, sizeof(parser.command));
		memset(tmp, '\0', sizeof(tmp));
		strncpy(parser.parameter1, tmp, sizeof(parser.parameter1));
	}
}

void handel_action(irc_t *irc)
{
	if (strncmp(parser.command, "PING", 4) == 0)
	{
		if (strncmp(parser.parameter1, irc->nick, strlen(irc->nick)) == 0)
			irc_pong(irc);
	} 

	else if (strncmp(parser.command, "view-file", 9) == 0)
		view_file(irc, parser.parameter1);
}
