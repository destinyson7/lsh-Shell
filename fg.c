#include "def.h"

int zFlag = 0, cFlag = 0;

void handleC(int signal)
{
    cFlag = 1;

    return;
}

void handleZ(int signal)
{
    zFlag = 1;

    return;
}

void fg(char *token, process proc[], int *proc_size)
{
    token = strtok(NULL, " \t");

    if(token == NULL)
    {
        perror("Invalid number of arguments");
        return;
    }

    char jobNumber[MAX_SIZE];
    strcpy(jobNumber, token);

    token = strtok(NULL, " \t");

    if(token != NULL)
    {
        perror("Invalid number of arguments");
        return;
    }

    int job = atoi(jobNumber);

    int processesSoFar = 0;

    for(int i = 0; i < MAX_SIZE; i++)
    {
        if(proc[i].pid != -1)
        {
            processesSoFar++;

            if(processesSoFar == job)
            {
                kill(proc[i].pid, SIGCONT); // If the process was in stopped state, then it was causing problems
                int savePid = proc[i].pid;
                proc[i].pid = -1; 

                signal(SIGINT, handleC);
                signal(SIGTSTP, handleZ);

                int status;
                while(waitpid(savePid, &status, WNOHANG) != savePid)
                {
                    // wait

                    if(cFlag == 1)
                    {
                        kill(savePid, SIGINT);

                        cFlag = 0;
                        break;
                    }

                    if(zFlag == 1)
                    {
                        kill(savePid, SIGSTOP);

                        proc[*proc_size].pid = savePid;
                        strcpy(proc[i].name, proc[*proc_size].name);
                        (*proc_size)++;

                        zFlag = 0;
                        break;
                    }
                }
                
                return;
            }
        }
    }

    printf("Invalid job number\n");
}