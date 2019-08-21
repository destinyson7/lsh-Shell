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

#define MAX_SIZE (int)1e3+5

void prompt();
void cd(char *path, char *home);
void pwd();
void echo(char *cur);
void ls(char *token, char *home);
void pinfo(char *token, char *home);