#include "def.h"

void jobs(char *token, process proc[])
{
    int numberOfProcesses = 0;

    for(int i = 0; i < MAX_SIZE; i++)
    {
        if(proc[i].pid != -1)
        {
            numberOfProcesses++;
            printf("[%d] ", numberOfProcesses);

            char checkStatus[MAX_SIZE] = "/proc/";
            char pid[MAX_SIZE];
            sprintf(pid, "%d", proc[i].pid);
            strcat(checkStatus, pid);
            strcat(checkStatus, "/stat");

            FILE *file = fopen(checkStatus, "r");
            char f[MAX_SIZE], s[MAX_SIZE], t[MAX_SIZE] = "";
            fscanf(file, "%s %s %s", f, s, t);

            if(strcmp(t, "R"))
            {
                printf("Running %s[%d]\n", proc[i].name, proc[i].pid);
            }

            else
            {
                printf("Stopped %s[%d]\n", proc[i].name, proc[i].pid);
            }
        }
    }
}

void kjob()
{
    
}