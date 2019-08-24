#include "def.h"

void fg_bg(char curCommand[], int flag, int *proc_size, process proc[])
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

    // If '&' was present, then run in background
    if(flag)
    {
        int pid = fork();

        proc[*proc_size].pid = pid;
        strcpy(proc[*proc_size].name, store[0]);
        (*proc_size)++;

        setpgid(0, 0); // Runs in background

        if(pid < 0)
        {
            perror(store[0]);
        }

        if(pid == 0)
        {
            close(STDERR_FILENO); // So that processes like firefox does not print error after closing
            if(execvp(store[0], store) == -1)
            {
                perror(store[0]);
                exit(0);
            }
        }
    }

    // Run in foreground
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

            waitpid(pid, &status, WUNTRACED);
        }
    }
}