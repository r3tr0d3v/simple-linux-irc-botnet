#include "includes.h"

char *alphabet = "abcdefghijklmnopqrstuvwxyz0123456789";

char *rand_string(size_t length)
{
	srand(time(NULL));
	
	char *rand_str = malloc(length);

	for (int i = 0; i < length; ++i)
	{
		rand_str[i] = alphabet[rand() % strlen(alphabet)];
	}

	return rand_str;
}