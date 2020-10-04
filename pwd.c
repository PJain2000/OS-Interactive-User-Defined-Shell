#include "shell.h"
void pwd(char **command)
{
	char buff[1024];
	getcwd( buff, 1023);
	int len_buff = strlen(buff);
	char homepath[1024];
	sprintf(homepath,"%s",getenv("PWD"));
	int len_homepath = strlen(homepath);
	int i=0;
	if(len_homepath<len_buff)
	{
		for(i=len_homepath;i< len_buff;i++)
		{
			printf("%c",buff[i]);
		}
		printf("\n");
	}
	else if (len_homepath == len_buff)
	{
		printf("~\n");
	}
	else
		printf("%s\n",buff);
}