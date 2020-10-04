#include <fcntl.h>
#include "compare.h"

char *redirect (char ** args){

int fd1, fd2, fd3;
char in[100];
char out[100];
char outdir[100];

int flag1=0;
int flag2=0;
int flag3=0;

int k = dup(1);

//Find whether there is a string for input and output

int i = 0;

while(args[i] != NULL){

  if (strncmp(args[i],"<",1) == 0){

    args[i] = " ";
    flag1 = 1;
    strcpy(in,args[i+1]);
    args[i+1] = " ";

  }

  if((strncmp(args[i],">",1)==0)){

    args[i] = " ";
    flag2 = 1;
    strcpy(out,args[i+1]);
    args[i+1] = " "; 

  }

  if(strncmp(args[i],">>",2)==0){

    args[i] = " ";
    flag3 = 1;
    strcpy(outdir,args[i+1]);
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

if(flag1==0 && flag2==0 && flag3==0)
  return str;
//If < was found in string inputted by user

if(flag1==1){

  fd1 = open(in, O_RDONLY,0);

  //if error
  if(fd1 < 0){
    perror("Could not open the input file");
    exit(0);
  }

  dup2(fd1,0);
  close(fd1);

}

if(flag2==1){
  // printf("etvgrtgvrtgvrtg\n");
  // printf("%s\n", out);
  fd2 = open (out, O_WRONLY | O_CREAT | O_TRUNC, 0666);
  if(fd2<0){
    perror("Could not open the output file");
    exit(0);
  }
  // printf("evcevrtevrtvtrv\n");
  dup2(fd2,1);
  // printf("wxwcrecferftrvrtvrt \n");
  close(fd2);
  char **tokens1 = malloc(64 * sizeof(char*));
  char** arr3 = parseSpace(str,tokens1);
  compare(arr3);

}

if(flag3==1){
  fd3 = open (outdir, O_CREAT | O_APPEND , 0666);
  if(fd3<0){
    perror("Could not open the output file");
    exit(0);
  }

  dup2(fd3,1);
  close(fd3);
}
  dup2(k,1);
  close(k);
return str;
}