#include "def.h"

void cd(char *path, char *home)
{
    path = strtok(NULL, " \t");

    if(path == NULL)
    {
        path = "~";
    }

    char changePath[3*MAX_SIZE];

    if(path[0] == '~')
    {
        strcpy(changePath, strcat(home, path+1));
    }

    else
    {
        strcpy(changePath, path);
    }
    
    if(chdir(changePath) < 0)
    {
        printf("cd: %s: No such file or directory\n", path);
    }
}