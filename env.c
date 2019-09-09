#include "def.h"

void setEnv(char *cur)
{
    cur = strtok(NULL, " \t");

    if(cur == NULL)
    {
        perror("Invalid number of arguments");
        return;
    }

    char var[MAX_SIZE], value[MAX_SIZE] = "";

    strcpy(var, cur);

    cur = strtok(NULL, " \t");

    if(cur != NULL)
    {
        strcpy(value, cur);

        cur = strtok(NULL, " \t");

        if(cur != NULL)
        {
            perror("Invalid number of arguments");
            return;
        }
    }

    setenv(var, value, 1);
}

void unsetEnv(char *cur)
{
    cur = strtok(NULL, " \t");

    if(cur == NULL)
    {
        perror("Invalid number of arguments");
        return;
    }

    char var[MAX_SIZE];

    strcpy(var, cur);

    cur = strtok(NULL, " \t");

    if(cur != NULL)
    {
        perror("Invalid number of arguments");
        return;
    }

    unsetenv(var);
}