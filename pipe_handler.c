// #include "compare.h"
// #include "parsing.h"

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
    printf("%d\n",flag1 );
    printf("%d\n",flag2);
    printf("%d\n",flag3 );

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
            redirect(arr2);
    
    }
    dup2(act_stdin,0);
    dup2(act_stdout,1);
    close(act_stdin);
    close(act_stdout);

}