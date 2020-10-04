#include "shell.h"
char* takeInput()
{
    int bytes_read;
	size_t nbytes = 100;
	char* my_string;

	my_string = (char *) malloc (nbytes + 1);
    bytes_read = getline (&my_string, &nbytes, stdin);

 	return my_string;
}