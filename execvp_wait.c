
#include "shell.h"

void execute_wait(char **command)
{
	int pid,status = 0;
	if ((pid  = fork())<0)
	{
		printf("Error\n");
		return;
	}
	if (pid == 0)
	{
		SIGNAL ();

		execvp(command[0],command);

	}
	while(wait(&status)>0);
	return;
}