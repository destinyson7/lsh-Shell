#include "def.h"

void fg(char *token, process proc[])
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
                int status;
                while(waitpid(savePid, &status, WNOHANG) != savePid)
                {
                    // wait
                }
                
                return;
            }
        }
    }

    printf("Invalid job number\n");
}