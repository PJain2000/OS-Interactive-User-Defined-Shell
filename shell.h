#include <wait.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <wait.h>



void execArgsPiped(char** parsed,int no_pipes);
char *redirect (char ** args);
char* takeInput();
void pwd(char **command);
void func_pinfo(int pid);
char** parseSemicolon(char *line,char **tokens);
char** parseArrow(char *line,char **tokens);
char** parsePipe(char *line,char **tokens);
char** parseSpace(char *line,char **tokens);
char** parseEOF(char *line,char **tokens);
void ls();
void ls_d(char* dirt);
void ls_a();
void ls_ad(char* dirt);
void ls_al();
void ls_ald(char* dirt);
void ls_l();
void ls_ld(char* dirt);
void execute_wait(char **command);
void cd(char **command);
void child_handler(int sig);
void compare(char** command);
void remove_bgproc(pid_t pid);
void execute(char **command);
void echo(char **command);