
#include "def.h"

int zFlag1 = 0, savePid = 0;

void handleZ1(int signal)
{
    zFlag1 = 1;

    return;
}

void fg_bg(char curCommand[], int flag, int *proc_size, process proc[])
{
    // printf("%s curCommand\n", curCommand);
    char **store = (char**) malloc(sizeof(char*) * MAX_SIZE);

    char saveName[MAX_SIZE];
    strcpy(saveName, curCommand);

    if(flag)
    {
        strcpy(proc[*proc_size].name, curCommand);
    }

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

        if(pid < 0)
        {
            perror(store[0]);
        }

        if(pid == 0)
        {
            setpgid(0, 0);
            // close(STDERR_FILENO); // So that processes like firefox does not print error after closing
            if(execvp(store[0], store) == -1)
            {
                printf("%s: Command Not Found\n", store[0]);
                // exit(0);
            }
        }
        
        if(pid > 0)
        {
            setpgid(pid, pid);
            
            proc[*proc_size].pid = pid;
            strcpy(proc[*proc_size].name, saveName);
            (*proc_size)++;
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
            savePid = pid;
            signal(SIGTSTP, handleZ1);
         
            int status;
            waitpid(pid, &status, WUNTRACED);
            
            if(zFlag1 == 1)
            {
                kill(savePid, SIGSTOP);
                
                proc[*proc_size].pid = savePid;
                strcpy(proc[*proc_size].name, saveName);
                (*proc_size)++;

                zFlag1 = 0;
            }
        }
    }
}