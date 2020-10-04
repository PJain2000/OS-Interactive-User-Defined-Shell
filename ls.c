

#include "shell.h"

void ls()
{ 
	char buff[1024];
  	getcwd( buff, FILENAME_MAX );
  	DIR *dir;
    struct dirent *dent;
    char buffer[2000];
    strcpy(buffer, buff);
    dir = opendir(buffer); 

    while ((dent = readdir(dir)) != NULL)
    {
    	if(dent->d_name[0] != '.')
            printf("%s\n", dent->d_name);
    }

    closedir(dir);

}
void ls_d(char* dirt)
{ 
	//char buff[1024];
  	//getcwd( buff, FILENAME_MAX );
  	DIR *dir;
    struct dirent *dent;
    char buffer[2000];
    strcpy(buffer, dirt);
    dir = opendir(buffer); 

    while ((dent = readdir(dir)) != NULL)
    {
    	if(dent->d_name[0] != '.')
            printf("%s\n", dent->d_name);
    }

    closedir(dir);

}
void ls_a()
{ 
	char buff[1024];
  	getcwd( buff, FILENAME_MAX );
  	DIR *dir;
    struct dirent *dent;
    char buffer[50];
    strcpy(buffer, buff);
    dir = opendir(buffer); 

    while ((dent = readdir(dir)) != NULL)
    { 
            printf("%s\n", dent->d_name);
    }

    closedir(dir);

}
void ls_ad(char* dirt)
{ 
	//char buff[1024];
  	//getcwd( buff, FILENAME_MAX );
  	DIR *dir;
    struct dirent *dent;
    char buffer[50];
    strcpy(buffer, dirt);
    dir = opendir(buffer); 

    while ((dent = readdir(dir)) != NULL)
    { 
            printf("%s\n", dent->d_name);
    }

    closedir(dir);

}

void ls_al()
{ 
	char buff[1024];
  	getcwd( buff, FILENAME_MAX );
  	DIR *dir;
    struct dirent *dent;
    char buffer[50];
    strcpy(buffer, buff);
    dir = opendir(buffer); 

    while ((dent = readdir(dir)) != NULL)
    {
    	struct stat check;
    	stat(dent->d_name, &check);
    	char mBuf[2000];
    	strftime(mBuf, 2000, "%b %d", localtime(&check.st_mtime));
    	char aBuf[2000];
    	strftime(aBuf, 2000, "%H:%M", localtime(&check.st_atime));
        struct passwd *a = getpwuid(check.st_uid);;
        struct group *b = getgrgid(check.st_gid);
        
	    printf( (S_ISDIR(check.st_mode)) ? "d" : "-");
	    printf( (check.st_mode & S_IRUSR) ? "r" : "-");
	    printf( (check.st_mode & S_IWUSR) ? "w" : "-");
	    printf( (check.st_mode & S_IXUSR) ? "x" : "-");
	    printf( (check.st_mode & S_IRGRP) ? "r" : "-");
	    printf( (check.st_mode & S_IWGRP) ? "w" : "-");
	    printf( (check.st_mode & S_IXGRP) ? "x" : "-");
	    printf( (check.st_mode & S_IROTH) ? "r" : "-");
	    printf( (check.st_mode & S_IWOTH) ? "w" : "-");
	    printf( (check.st_mode & S_IXOTH) ? "x " : "- ");
	    //
	    printf("%lld ",(long long) check.st_nlink);
	    //
	    printf("%s ",a->pw_name);
	    //
	    printf("%s ",b->gr_name);
	    //
    	printf("%lld ",(long long int) check.st_size);
    	//
    	printf("%s ", mBuf);
    	//
    	printf("%s ", aBuf);
    	//
        printf("%s\n", dent->d_name);
    }
    closedir(dir);

}
void ls_ald(char* dirt)
{ 
	//char buff[1024];
  	//getcwd( buff, FILENAME_MAX );
  	DIR *dir;
    struct dirent *dent;
    char buffer[50];
    strcpy(buffer, dirt);
    dir = opendir(buffer); 

    while ((dent = readdir(dir)) != NULL)
    {
    	struct stat check;
    	stat(dent->d_name, &check);
    	char mBuf[2000];
    	strftime(mBuf, 2000, "%b %d", localtime(&check.st_mtime));
    	char aBuf[2000];
    	strftime(aBuf, 2000, "%H:%M", localtime(&check.st_atime));
        struct passwd *a = getpwuid(check.st_uid);;
        struct group *b = getgrgid(check.st_gid);
        
	    printf( (S_ISDIR(check.st_mode)) ? "d" : "-");
	    printf( (check.st_mode & S_IRUSR) ? "r" : "-");
	    printf( (check.st_mode & S_IWUSR) ? "w" : "-");
	    printf( (check.st_mode & S_IXUSR) ? "x" : "-");
	    printf( (check.st_mode & S_IRGRP) ? "r" : "-");
	    printf( (check.st_mode & S_IWGRP) ? "w" : "-");
	    printf( (check.st_mode & S_IXGRP) ? "x" : "-");
	    printf( (check.st_mode & S_IROTH) ? "r" : "-");
	    printf( (check.st_mode & S_IWOTH) ? "w" : "-");
	    printf( (check.st_mode & S_IXOTH) ? "x " : "- ");
	    //
	    printf("%lld ",(long long) check.st_nlink);
	    //
	    printf("%s ",a->pw_name);
	    //
	    printf("%s ",b->gr_name);
	    //
    	printf("%lld ",(long long int) check.st_size);
    	//
    	printf("%s ", mBuf);
    	//
    	printf("%s ", aBuf); 
    	//
        printf("%s\n", dent->d_name);
    }
    closedir(dir);

}
void ls_l()
{ 
	char buff[1024];
  	getcwd( buff, FILENAME_MAX );
  	DIR *dir;
    struct dirent *dent;
    char buffer[50];
    strcpy(buffer, buff);
    dir = opendir(buffer); 

    while ((dent = readdir(dir)) != NULL)
    {
    	if(dent->d_name[0] != '.')
    	{
	    	struct stat check;
	    	stat(dent->d_name, &check);
	    	char mBuf[2000];
	    	strftime(mBuf, 2000, "%b %d", localtime(&check.st_mtime));
	    	char aBuf[2000];
	    	strftime(aBuf, 2000, "%H:%M", localtime(&check.st_atime));
	        struct passwd *a = getpwuid(check.st_uid);;
	        struct group *b = getgrgid(check.st_gid);
	        
		    printf( (S_ISDIR(check.st_mode)) ? "d" : "-");
		    printf( (check.st_mode & S_IRUSR) ? "r" : "-");
		    printf( (check.st_mode & S_IWUSR) ? "w" : "-");
		    printf( (check.st_mode & S_IXUSR) ? "x" : "-");
		    printf( (check.st_mode & S_IRGRP) ? "r" : "-");
		    printf( (check.st_mode & S_IWGRP) ? "w" : "-");
		    printf( (check.st_mode & S_IXGRP) ? "x" : "-");
		    printf( (check.st_mode & S_IROTH) ? "r" : "-");
		    printf( (check.st_mode & S_IWOTH) ? "w" : "-");
		    printf( (check.st_mode & S_IXOTH) ? "x " : "- ");
		    //
		    printf("%lld ",(long long) check.st_nlink);
		    //
		    printf("%s ",a->pw_name);
		    //
		    printf("%s ",b->gr_name);
		    //
	    	printf("%lld ",(long long int) check.st_size);
	    	//
	    	printf("%s ", mBuf);
	    	//
	    	printf("%s ", aBuf);
	    	//
	        printf("%s\n", dent->d_name);
	    }
	}
    closedir(dir);

}
void ls_ld(char* dirt)
{ 
	//char buff[1024];
  	//getcwd( buff, FILENAME_MAX );
  	DIR *dir;
    struct dirent *dent;
    char buffer[50];
    strcpy(buffer, dirt);
    dir = opendir(buffer); 

    while ((dent = readdir(dir)) != NULL)
    {
    	if(dent->d_name[0] != '.')
    	{
	    	struct stat check;
	    	stat(dent->d_name, &check);
	    	char mBuf[2000];
	    	strftime(mBuf, 2000, "%b %d", localtime(&check.st_mtime));
	    	char aBuf[2000];
	    	strftime(aBuf, 2000, "%H:%M", localtime(&check.st_atime));
	        struct passwd *a = getpwuid(check.st_uid);;
	        struct group *b = getgrgid(check.st_gid);
	        
		    printf( (S_ISDIR(check.st_mode)) ? "d" : "-");
		    printf( (check.st_mode & S_IRUSR) ? "r" : "-");
		    printf( (check.st_mode & S_IWUSR) ? "w" : "-");
		    printf( (check.st_mode & S_IXUSR) ? "x" : "-");
		    printf( (check.st_mode & S_IRGRP) ? "r" : "-");
		    printf( (check.st_mode & S_IWGRP) ? "w" : "-");
		    printf( (check.st_mode & S_IXGRP) ? "x" : "-");
		    printf( (check.st_mode & S_IROTH) ? "r" : "-");
		    printf( (check.st_mode & S_IWOTH) ? "w" : "-");
		    printf( (check.st_mode & S_IXOTH) ? "x " : "- ");
		    //
		    printf("%lld ",(long long) check.st_nlink);
		    //
		    printf("%s ",a->pw_name);
		    //
		    printf("%s ",b->gr_name);
		    //
	    	printf("%lld ",(long long int) check.st_size);
	    	//
	    	printf("%s ", mBuf);
	    	//
	    	printf("%s ", aBuf);
	    	//
	        printf("%s\n", dent->d_name);
	    }
	}
    closedir(dir);

}
