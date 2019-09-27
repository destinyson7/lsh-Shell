#include "def.h"

void cronjob(char *token, char home[], process proc[], int proc_size, char data[20][MAX_SIZE], int done, char duplicate[])
{
    // printf("**\n");
    token = strtok(NULL, " \t");

    char command[MAX_SIZE], dup[MAX_SIZE];
    int tim = -1;
    int periodd = -1;

    // printf("**\n");

    while(token != NULL)
    {
        // printf("**\n");

        if(strcmp(token, "-c") == 0)
        {
            token = strtok(NULL, " \t");

            // printf("* %s *\n", token);

            if(token != NULL)
            {
                strcpy(command, token);

                token = strtok(NULL, " \t");

                // printf("** %s **\n", token);

                while(token != NULL && strcmp(token, "-t") && strcmp(token, "-p"))
                {
                    // printf("**\n");
                    strcat(command, " ");
                    strcat(command, token);

                    token = strtok(NULL, " \t");
                }

                if(token == NULL)
                {
                    break;
                }
            }

            else
            {
                break;
            }
        }

        if(strcmp(token, "-t") == 0)
        {
            // printf("***\n");
            token = strtok(NULL, " \t");

            if(token != NULL)
            {
                tim = atoi(token);
            }

            else
            {
                break;
            }
        }

        if(strcmp(token, "-p") == 0)
        {
            token = strtok(NULL, " \t");

            if(token != NULL)
            {
                periodd = atoi(token);
            }

            else
            {
                break;
            }
        }

        token = strtok(NULL, " \t");
    }

    if(command == NULL || tim == -1 || periodd == -1)
    {
        printf("invalid syntax");
        return;
    }

    int numberOfTimes = periodd/tim;

    // printf("%s * %d * %d\n", command, tim, periodd);

    strcpy(dup, command);


    while(numberOfTimes--)
    {
        strcpy(dup, command);
        char *cur = strtok(dup, " \t\n");
       
        sleep(tim);
        printf("\n");

        // printf("** %s **\n", cur);

        if(numberOfTimes == 0)
        {
            execute(cur, home, proc, &proc_size, data, done, duplicate, 11, 0, 0);
        }

        else
        {
            execute(cur, home, proc, &proc_size, data, done, duplicate, 0, 0, 0);
        }
    }

}