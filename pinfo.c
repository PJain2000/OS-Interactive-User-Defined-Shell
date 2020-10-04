#include "shell.h"
void func_pinfo(int pid)
{
	char stat1[1000];
  	char exec1[1000];

	sprintf(stat1,"/proc/%d/stat",pid);      
    sprintf(exec1,"/proc/%d/exe",pid);

    FILE *fp;

    fp=fopen(stat1,"r");

    char runstatus;
    long unsigned int mem;

    int pid_s;
    fscanf(fp,"%d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d",&pid_s,&runstatus,&mem);

    fclose(fp);

    printf("Process ID -- %d\n",pid);
    printf("Process Status -- %c\n",runstatus);
    printf("Memory -- %lu\n",mem);

    FILE *fp2=fopen(exec1,"r");
	char Path[101];
	ssize_t len=readlink(exec1,Path,sizeof(Path)-1);
	if(len!=-1)
	    Path[len]='\0';
	printf("Executable Path -- %s\n",Path);
}