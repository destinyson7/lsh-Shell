#include "def.h"

int piping(char curCommand[], char *home)
{
    char **store = (char**) malloc(sizeof(char*) * MAX_SIZE);

    char *token = strtok(curCommand, " \t\n");

    int cnt = 0;

    while(token != NULL)
    {
        store[cnt] = token;
        // printf("%s %d\n", token, cnt);
        // store[cnt][strlen(token)] = '\0';
        cnt++;

        token = strtok(NULL, " \t");
        // printf("%s token\n", token);
    }
    store[cnt++] = NULL;

    int numberOfPipes = 0;

    for(int i = 0; i < cnt; i++)
    {
        if(strcmp(store[i], "|") == 0)
        {
            numberOfPipes++;

            if(store[i+1] == NULL)
            {
                perror("No argument on the other side of pipe");
                return 3;
            }
        }
    }

    if(numberOfPipes > 0)
    {
        return 1;
    }
}

