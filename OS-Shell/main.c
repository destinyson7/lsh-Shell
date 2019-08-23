#include "def.h"

int main(int argc, char *argv[])
{
    char curPath[MAX_SIZE];
    getcwd(curPath, MAX_SIZE);

    int n = strlen(argv[0]);

    for(int i = n-1; i >= 0; i--)
    {
        if(argv[0][i] == '/')
        {
            argv[0][i] = '\0';
            break;
        }
    }

    chdir(argv[0]);

    char home[MAX_SIZE];
    getcwd(home, MAX_SIZE);

    // printf("%s\n", curPath);
    chdir(curPath);

    while(1)
    {
        prompt(home);

        char *s = NULL;
        size_t len = 0;
        getline(&s, &len, stdin);

        s[strlen(s)-1] = '\0';

        // printf("%s", s);

        char command[MAX_SIZE][MAX_SIZE];

        int numberOfCommands = 0;

        char *token = strtok(s, ";");

        while(token != NULL)
        {   
            strcpy(strcat(command[numberOfCommands++], "\0"), token);
            // printf("%s\n", strcat(token, "\0"));
            token = strtok(NULL, ";");
        }   
        
        for(int i = 0; i < numberOfCommands; i++)
        {
            char duplicate[MAX_SIZE];
            strcpy(duplicate, command[i]);
            char *next = strtok(command[i], " \t\n");

            int flag = 0;

            for(int j = 0; next[j] != '\0'; j++)
            {
                if(next[j] == '&')
                {
                    flag = 1;
                    next[i] = '\0';
                    break;
                }
            }

            if(strcmp(next, "exit") == 0 || strcmp(next, "quit") == 0)
            {
                return 0;
            }

            else if(strcmp(next, "cd") == 0)
            {
                cd(next, home);
            }

            else if(strcmp(next, "pwd") == 0)
            {
                pwd();
            }

            else if(strcmp(next, "echo") == 0)
            {
                echo(next);
            }

            else if(strcmp(next, "ls") == 0)
            {
                ls(next, home);
            }

            else if(strcmp(next, "pinfo") == 0)
            {
                pinfo(next, home);
            }

            // printf("%s\n", next);

            else
            {
                int pid = fork();

                if(pid < 0)
                {
                    perror(next);
                }

                else if(pid == 0)
                {
                    char **send = (char **) malloc(MAX_SIZE * sizeof(char *));

                    char *cur = strtok(duplicate, " \t\n");

                    int index = 0;

                    while(cur != NULL)
                    {
                        send[index++] = cur;

                        cur = strtok(NULL, " \t\n");
                    }

                    send[index++] = NULL;
                    send[0] = next;

                    if(execvp(send[0], send) == -1)
                    {
                        perror(next);
                    }
                }

                else
                {
                    if(flag)
                    {

                    }

                    else
                    {
                        wait(NULL);
                    }
                }
            }

        }
    }

    return 0;
}