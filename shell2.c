
#include "shell.h"

# define Green "\x1b[32m"
# define Blue "\x1b[34m"
# define Reset "\x1b[0m"

char *redirect (char ** args);


void execArgsPiped(char** parsed,int no_pipes)   
{
    int pipefd[2];

    int act_stdin = dup(0), loop_stdin = dup(0);
    int act_stdout = dup(1), loop_stdout = dup(1); 
    
    int pipe_in = 0;
    int pipe_out = 1;

    for (int i = 0; i < no_pipes+1; i++)
    {
        dup2(loop_stdin, 0);
        close(loop_stdin);
        int bufsize = 64;
        char **tok2 = malloc(bufsize * sizeof(char*));
        char **arr2 = parseSpace(parsed[i],tok2);
            if(i == no_pipes)
            {
                loop_stdout = dup(act_stdout);
            }
            else {
                pipe(pipefd);
                loop_stdin = pipefd[0];
                loop_stdout = pipefd[1];
            }
            dup2(loop_stdout, 1);
            close(loop_stdout);
            compare(arr2);
    
    }
    dup2(act_stdin,0);
    dup2(act_stdout,1);
    close(act_stdin);
    close(act_stdout);

}

char *redirect (char ** args){

	int fd1, fd2, fd3;
	char in[100];
	char out[100];
	char outdir[100];

	int flag1=0;
	int flag2=0;
	int flag3=0;

	int k = dup(1);
	int l = dup(0);

	int i = 0;

	while(args[i] != NULL)
	{
	  if (strncmp(args[i],"<",1) == 0)
	  {
	    args[i] = " ";
	    flag1 = 1;
	    strcpy(in,args[i+1]);
	    args[i+1] = " ";
	  }

	  if(strncmp(args[i],">>",2) == 0)
	  {
	    args[i] = " ";
	    flag3 = 1;
	    strcpy(outdir,args[i+1]);
	    args[i+1] = " ";
	  }

	  if((strncmp(args[i],">",1) == 0))
	  {
	    args[i] = " ";
	    flag2 = 1;
	    strcpy(out,args[i+1]);
	    args[i+1] = " "; 
	  }
	  i++;
	}
	int j = 0;
	char *str = malloc(64 * sizeof(char));;
	while(args[j] != NULL)
	{
	    strcat(str, args[j]);
	    strcat(str, " ");
	    j++;
	}
	args[j] = '\0';
	// printf("%d\n",flag1 );
	// printf("%d\n",flag2);
	// printf("%d\n",flag3 );

	if(flag1 == 1)
	{
	  fd1 = open(in, O_RDONLY,0);
	  if(fd1 < 0)
	  {
	    perror("Could not open the input file");
	    exit(0);
	  }
	  dup2(fd1,0);
	  close(fd1);
	}

	if(flag2 == 1)
	{
	  fd2 = open (out, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	  if(fd2<0)
	  {
	    perror("Could not open the output file");
	    exit(0);
	  }
	  dup2(fd2,1);
	  close(fd2);
	}

	if(flag3 == 1)
	{
	  fd3 = open (outdir, O_CREAT | O_APPEND | O_WRONLY , 0666);
	  if(fd3<0)
	  {
	    perror("Could not open the output file");
	    exit(0);
	  }
	  dup2(fd3,1);
	  close(fd3);
	}
	//Execution of command
	  char **tokens1 = malloc(64 * sizeof(char*));
	  char** arr3 = parseSpace(str,tokens1);
	  compare(arr3);

	  dup2(k,1);
	  close(k);
	  dup2(l,0);
	  close(l);
	return str;
}

int main()
{
	// int k = dup(1);
	char uname[1024],hostname[1024],homepath[1024];
	sprintf(homepath,"%s",getenv("PWD"));
	int len_homepath = strlen(homepath);
	sprintf(uname,"%s",getenv("USER"));
	gethostname(hostname, 1023);
	int carry = 0;
	signal(SIGINT,SIG_IGN);
	signal(SIGTSTP,SIG_IGN);
	while(carry == 0)
	{
		printf(Green"<%s@%s:~"Reset,uname,hostname);
		char buff[1024];
		getcwd( buff, FILENAME_MAX );
		int len_buff = strlen(buff);
		int i = 0;
		//Printing the prompt on the terminal
		if (len_homepath<=len_buff)
		{	
			for(i=len_homepath;i< len_buff;i++)
			{
				printf(Blue"%c"Reset,buff[i] );
			}

			printf(Green">"Reset);
		}
		else
			printf(Blue"%s"Reset Green">"Reset,buff);
		//Taking input from terminal
		char* string = takeInput();

		//Parsing through the string
		int bufsize = 64;
		char **tokens = malloc(bufsize * sizeof(char*));
		char** arr0 = parseEOF(string,tokens);

		char **tokens1 = malloc(bufsize * sizeof(char*));
		char** arr = parseSemicolon(arr0[0],tokens1);
		
		int pipe_flag = 0;
		int redirect_flag = 0;

		for (int i = 0; arr[i] != NULL; ++i)
		{
			int no_pipes = 0;
			for (int j = 0; j < strlen(arr[i]); j++)
			{
				if(arr[i][j] == '|')
				{
					no_pipes++;
					pipe_flag = 1;
				}
				if(arr[i][j] == '<' || arr[i][j] == '>')
					redirect_flag = 1;
			}
			if(pipe_flag == 1)
			{
				if(redirect_flag == 0)
				{
					for(int j = 0;j < strlen(arr[i]);j++)
					{
						if(arr[i][j] == '|')
						{
							printf("PIPE FOUND\n");
							char **tokens2 = malloc(bufsize * sizeof(char*));
							char** arr2 = parsePipe(arr[i],tokens2);
							execArgsPiped(arr2,no_pipes);

						}
					}
				}
				else
				{
					printf("Piping with redirection\n");
				}
			}
			if(pipe_flag == 0)
			{
				if(redirect_flag == 1)
				{
					char **tokens = malloc(bufsize * sizeof(char*));
					char** arr1 = parseSpace(arr[i],tokens);
					char* arr2 = redirect(arr1);
				}
				else
				{
					char **tokens2 = malloc(bufsize * sizeof(char*));
					char **arr2 = parseSpace (arr[i], tokens2);
					compare(arr2);
				}
			}
		}
	}
	return 0;
}

















