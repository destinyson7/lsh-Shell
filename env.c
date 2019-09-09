#include "def.h"

void setEnv(char *token)
{
    token = strtok(NULL, " \t");

    if(token == NULL)
    {
        perror("Invalid number of arguments");
        return;
    }

    char var[MAX_SIZE], value[MAX_SIZE] = "";

    strcpy(var, token);

    token = strtok(NULL, " \t");

    if(token != NULL)
    {
        strcpy(value, token);

        token = strtok(NULL, " \t");

        if(token != NULL)
        {
            perror("Invalid number of arguments");
            return;
        }
    }

    setenv(var, value, 1);
}

void unsetEnv(char *token)
{
    token = strtok(NULL, " \t");

    if(token == NULL)
    {
        perror("Invalid number of arguments");
        return;
    }

    char var[MAX_SIZE];

    strcpy(var, token);

    token = strtok(NULL, " \t");

    if(token != NULL)
    {
        perror("Invalid number of arguments");
        return;
    }

    unsetenv(var);
}