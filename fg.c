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

    int savePid = 0;

    for(int i = 0; i < MAX_SIZE; i++)
    {
        if(proc[i].pid != -1)
        {
            processesSoFar++;

            if(processesSoFar == job)
            {
                kill(proc[i].pid, SIGCONT); // If the process was in stopped state, then it was causing problems
                savePid = proc[i].pid;
             
                proc[i].pid = -1; 
  
                signal(SIGINT, handleC);
                signal(SIGTSTP, handleZ);

                signal(SIGTTOU, SIG_IGN);
                tcsetpgrp(0, getpgid(savePid));
                kill(savePid, SIGCONT);
                
                signal(SIGTTOU, SIG_DFL);

                while(waitpid(savePid, NULL, WUNTRACED) != savePid)
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
                        setpgid(savePid, savePid);
                        kill(savePid, SIGSTOP);

                        proc[*proc_size].pid = savePid;
                        strcpy(proc[i].name, proc[*proc_size].name);
                        (*proc_size)++;

                        zFlag = 0;
                        break;
                    }
                }

                signal(SIGTTOU, SIG_IGN);
                tcsetpgrp(0, getpid());
                signal(SIGTTOU, SIG_DFL);
                
                return;
            }
        }
    }

    printf("Invalid job number\n");
}