#include "shell.h"
void cd(char **command)
{
	int f = 0;
	if (strcmp(command[1],"~") == 0)
	{
		char homepath[1024];
		sprintf(homepath,"%s",getenv("PWD"));
		chdir(homepath);
		f = 1;
	}
	if (f == 0)
	{
		char buff[1024];
		getcwd( buff, FILENAME_MAX );
		chdir(command[1]);
		getcwd( buff, FILENAME_MAX );
	}
}