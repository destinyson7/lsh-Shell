#include "def.h"

void fg_bg(char curCommand[], int flag)
{
    // printf("%s curCommand\n", curCommand);
    char **store = (char **) malloc(sizeof(char *) * MAX_SIZE);

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

    if(flag)
    {
        int pidf = fork();

        if(pidf < 0)
        {
            perror(store[0]);
        }

        if(pidf == 0)
        {
            int pids = fork();

            if(pids < 0)
            {
                perror(store[0]);
            }

            else if(pids == 0)
            {
                close(STDERR_FILENO);
                if(execvp(store[0], store) == -1)
                {
                    printf("%s: Command Not Found\n", store[0]);
                    exit(0);
                }
            } 

            else
            {
                wait(NULL);

                fprintf(stderr, "\n%s with pid %d exited normally\n", store[0], pids);
                exit(0);
            }
        }

        // else
        // {
        //     int status;

        //     while(wait(&status) != pidf)
        //     {
        //         continue;
        //     }
        // }
    }

    else
    {
        int pid = fork();

        if(pid < 0)
        {
            perror(store[0]);
        }

        else if(pid == 0)
        {
            if(execvp(store[0], store) == -1)
            {
                printf("%s: Command Not Found\n", store[0]);
                exit(0);
            }
        }

        else
        {
            int status;

            while(wait(&status) != pid)
            {
                continue;
            }
        }
    }
}