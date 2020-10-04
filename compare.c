 #include "shell.h"

typedef struct  proc_list{
	pid_t pidd;
	char status[100];
	char name[100];
}proc_list;

proc_list proc[1000];

//pid_t back_proc[1000];
int bgproc = 0;

void func2(int sig)
{
	for (int i = 0; i < bgproc; i++)
	{
		if(strcmp(proc[i].status,"Foreground")==0)
		{
			kill(proc[i].pidd,SIGKILL);
		}
	}
}

void func1(int sig)
{
	for (int i = 0; i < bgproc; i++)
	{
		if(strcmp(proc[i].status,"Foreground")==0)
		{
			kill(proc[i].pidd,SIGSTOP);
			strcpy(proc[i].status, "Stopped");
		}
	}
}


void execute(char **command)
{
	int pid,status = 0;
	if ((pid  = fork())<0)
	{
		printf("Error\n");
		return;
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);

		execvp(command[0],command);
	}
	printf("rcnerhcberhce j her\n");
	proc[bgproc].pidd = pid;
	strcpy(proc[bgproc].status,"Running");
	strcpy(proc[bgproc].name,command[0]);

	proc[bgproc+1].pidd = 0;
	// strcpy(proc[bgproc+1].status,NULL);
	// strcpy(proc[bgproc+1].name, NULL);
	bgproc += 1;
	return;
}

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
		signal(SIGINT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);

		execvp(command[0],command);

	}
	proc[bgproc].pidd = pid;
	strcpy(proc[bgproc].status,"Foreground");
	strcpy(proc[bgproc].name,command[0]);

	proc[bgproc+1].pidd = 0;
	// strcpy(proc[bgproc+1].status,NULL);
	// strcpy(proc[bgproc+1].name,NULL);
	bgproc += 1;
	while(wait(&status)>0);
	return;
}

void remove_bgproc(pid_t pid)
{
	int i = 0,index;
	while(proc[i].pidd != 0)
	{
		if (proc[i].pidd == pid)
		{
			index = i;
			break;
		}
		i++;
	}
	int j = index + 1;
	
	while(proc[j].pidd != 0)
	{
		proc[j-1].pidd = proc[j].pidd;
		strcpy(proc[j-1].status,proc[j].status);
		strcpy(proc[j-1].name,proc[j].name);
		j++;
	}
	proc[j].pidd = 0;
	// strcpy(proc[j].status,NULL);
	// strcpy(proc[j].name,NULL);
	bgproc--;

}

void compare(char** command)
{
	signal(SIGTSTP, func1);
	signal(SIGINT, func2);

	int flag1 = 0;
	if (strcmp(command[0],"echo") == 0)
	{
		flag1 = 1;
		echo(command); 
	}
	else if((strcmp(command[0],"pwd\n")==0) || (strcmp(command[0],"pwd")==0))
	{
		flag1 = 1;
		pwd(command);
	}
	else if (strcmp(command[0],"cd")==0)
	{
		flag1 = 1;
		cd(command);
	}
	else if (strcmp(command[0],"ls")==0)
	{
		flag1 = 1;
		int one_arg = 0,two_arg = 0, three_arg = 0;
		if (command[1] != NULL)
		{
			if(command[2] != NULL)
			{
				three_arg = 1;
			}
			else
			{
				two_arg = 1;
			} 	
		}
		else
		{
			one_arg = 1;
		}

		if(one_arg == 1)
		{
			ls();
		}
		if (two_arg == 1)
		{
			if (strcmp(command[1],"-l") == 0)
			{
				ls_l();
			}
			else if(strcmp(command[1],"-a") == 0)
			{
				ls_a();
			}
			else if((strcmp(command[1],"-al") == 0)||(strcmp(command[1],"-la") == 0))
			{
				ls_al();
			}
			else
			{
				ls_d(command[1]);
			}
		}
		if(three_arg == 1)
		{
			if (strcmp(command[1],"-l") == 0)
			{
				ls_ld(command[2]);
			}
			else if(strcmp(command[1],"-a") == 0)
			{
				ls_ad(command[2]);
			}
			else if((strcmp(command[1],"-al") == 0)||(strcmp(command[1],"-la") == 0))
			{
				ls_ald (command[2]);
			}
		}
	}
	else if (strcmp(command[0] ,"pinfo") == 0)
	{
		if(command[1] == NULL)
		{
			pid_t cur_pid=getpid();
			int pid = (int)cur_pid;
			func_pinfo(pid);
		}
		else
		{
			int pid = atoi(command[1]);
			func_pinfo(pid);
		}
	}
	else if (strcmp(command[0],"setenv") == 0)
	{
		if(command[1] != NULL)
		{
			if(command[2] != NULL)
			{
				char *str1 = malloc(64 * sizeof(char));
				for (int k = 1; k <= strlen(command[2]) - 2; k++)
				{
					str1[k-1] = command[2][k];
				}
				setenv(command[1],str1,1);
			}
			else
			{
				char string[0];
				setenv(command[1],string,1);
			}
		}
		else
		{
			printf("setenv var[value]\n");
		}
	}
	else if (strcmp(command[0],"unsetenv") == 0)
	{
		if(command[1] != NULL)
		{
			unsetenv(command[1]);
		}
		else
		{
			printf("unsetenv var\n");
		}
	}
	else if (strcmp(command[0],"jobs")==0)
	{
		for (int i = 0; i < bgproc; ++i)
		{
			printf("%d\n",proc[i].pidd);
			printf("%s\n",proc[i].status );
			printf("%s\n",proc[i].name );
			printf("****************************\n");
		}
	}
	else if (strcmp(command[0],"kjob")==0)
	{
		//remove this from back_proc
		pid_t pid = proc[atoi(command[1])-1].pidd;
		int sig = atoi(command[2]);
		kill(pid,sig);
		if(sig == 9)
			remove_bgproc(pid);
	}
	else if (strcmp(command[0],"overkill")==0)
	{
		int i = 0;
		while(proc[i].pidd != 0)
		{
			kill(proc[i].pidd,9);
			remove_bgproc(proc[i].pidd);
			i++;
		}
	}
	else if (strcmp(command[0],"fg")==0)
	{
		pid_t pids = proc[atoi(command[1])-1].pidd;
		//set to foreground
		int i = 0;
		while(proc[i].pidd != 0)
		{
			if(proc[i].pidd == pids)
			{
				strcpy(proc[i].status,"Foreground");
			}
			i++;
		}
		kill(pids,SIGCONT);
		waitpid(pids,NULL,WUNTRACED);
	}
	else if (strcmp(command[0],"bg")==0)
	{
		pid_t pids = proc[atoi(command[1])-1].pidd;
		int i = 0;
		while(proc[i].pidd != 0)
		{	
			int ret = strcmp(proc[i].status,"Stopped");
			if(proc[i].pidd == pids && ret == 0)
			{
				strcpy(proc[i].status,"Running");
			}
			i++;
		}
		kill(pids,SIGCONT);
	}
	else if (strcmp(command[0],"quit")==0)
	{
		exit(0);
	}
	else if(flag1 == 0)
	{
		if(command[0][0] == '\n')
			return;

		int flag2 = 0;
		for (int a = 0; command[a] != NULL; a++)
		{
			for (int b = 0; command[a][b] != '\0'; b++)
			{
				if (command[a][b] == '&') 
				{
					signal(SIGCHLD, child_handler);
					flag2 = 1;
				}
			}
		}
		if(flag2 == 0)
		{
			// flag2 = 1;
			execute_wait(command);
		}
		else
		{
			char **arr = malloc(64 * sizeof(char*));
			int i = 0,index;
			while(command[i] != NULL)
			{
				index = i;
				i++;
				
			}
			command[index] = NULL;
			execute(command);
		}
	}
}
