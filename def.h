#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <langinfo.h>
#include <sys/wait.h>

#define MAX_SIZE (int)1e3+5

typedef struct process
{
    int pid;
    char name[MAX_SIZE];
}process;

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

void prompt();
void cd(char *path, char *home);
void pwd();
void echo(char *cur);
void ls(char *token, char *home);
void pinfo(char *token, char *home);
void fg_bg(char *token, int flag, int *proc_size, process proc[]);