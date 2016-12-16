#include "my_error.h"
void error(const char *s)
{
	//perror(s);
	printf("Error Occur:%s\n",s);
	exit(-1);
}

void malloc_error()
{
	fprintf(stderr, "Malloc error\n");
	exit(-1);
}

void file_error(char *s)
{
	fprintf(stderr, "Couldn't open file: %s\n", s);
	exit(0);
}