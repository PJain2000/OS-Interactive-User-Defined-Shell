
#include "shell.h"
void child_handler(int sig)
{
	int status;
	pid_t wpid = waitpid(-1, &status, WNOHANG);
	if (wpid > 0)
	{
		if(!WIFEXITED(status))
			printf("\nProcess with pid: %d exited normally\n",wpid);
		if(!WIFSIGNALED(status))
			printf("\nProcess with pid: %d interrupted by signal %d\n",wpid,sig);
	}
	if(wpid < 0)
	{
		perror("waitpid");
	}
}