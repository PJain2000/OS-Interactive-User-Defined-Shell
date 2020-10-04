#include "shell.h"
void echo(char **command)
{
	int i = 1;
	while(command[i] != NULL)
	{
		if(command[i][0] == '$')
		{
			char *str1 = malloc(64 * sizeof(char));
			char *str2 = malloc(64 * sizeof(char));
			for (int j = 1; j <= strlen(command[1]); ++j)
			{
				str2[j-1] = command[i][j];
			}
			str1 = getenv(str2);
			printf("%s ",str1);
		}
		else
			printf("%s ", command[i]);
		i++;
	}
	printf("\n");
}