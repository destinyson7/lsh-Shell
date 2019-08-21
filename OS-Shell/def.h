#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_SIZE (int)1e3+5

void prompt();
void cd(char *path, char *home);
void pwd();
void echo(char *cur);
void pinfo(char *token, char *home);