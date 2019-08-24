#include "def.h"

void checkSignal(int signal)
{
    // do nothing
    return;
}

int main(int argc, char *argv[])
{
    printf(BLUE "Welcome to " CYAN "lsh" BLUE " aka laaaad's Shell\n\n");
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

    int proc_size = 0;
    process proc[MAX_SIZE];

    for(int i = 0; i < MAX_SIZE; i++)
    {
        proc[i].pid = -1;
    }

    FILE *fp;

    char data[20][MAX_SIZE];

    int done = 0;
    fp = fopen("data.txt", "rb");
    
    if(fp == NULL)
    {
        for(int i = 0; i < 20; i++)
        {
            strcpy(data[i], "\0");
        }
    }

    else
    {
        fread(&data, sizeof(data), 1, fp);

        for(int i = 0; i < 20; i++)
        {
            // printf("%s\n", data[i]);
            if(data[i] != '\0')
            {
                done++;
            }
        }
        
        fclose(fp);
    }



    while(1)
    {
        prompt(home);

        signal(SIGINT, checkSignal);
        signal(SIGTSTP, checkSignal);

        int status;
        int get = waitpid(-1, &status, WNOHANG);

        if(get > 0)
        {
            if(!WIFEXITED(status))
            {
                char print[MAX_SIZE] = "Process";
                for(int i = 0; i < MAX_SIZE; i++)
                {
                    if(proc[i].pid == get)
                    {
                        proc[i].pid = -1;
                        strcpy(print, proc[i].name);
                    }
                }

                printf("\n%s with pid %d exited with exit status: %d\n", print, get, WEXITSTATUS(status));
                prompt(home);
            }
        }

        for(int i = 0; i < MAX_SIZE; i++)
        {
            if(kill(proc[i].pid, 0) == -1)
            {
                printf("\n%s with pid %d exited normally\n", proc[i].name, proc[i].pid);
                prompt(home);
                proc[i].pid = -1;
            }
        }

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
            int flag = 0;

            for(int j = 0; command[i][j] != '\0'; j++)
            {
                if(command[i][j] == '&')
                {
                    flag = 1;
                    command[i][j] = '\0';
                    break;
                }
            }

            if(strcmp(command[i], "\0") == 0)
            {
                continue;
            }

            // printf("%s cur\n", command[i]);
            char duplicate[MAX_SIZE];
            strcpy(duplicate, command[i]);

            char *next = strtok(command[i], " \t\n");

            done = storeHistory(done, data, duplicate);
            // printf("%d done\n", done);

            // for(int i = 0; i < 20; i++)
            // {
            //     printf("%s\n", data[i]);
            // }

            if(strcmp(next, "exit") == 0 || strcmp(next, "quit") == 0)
            {
                fp = fopen("data.txt", "wb");
                // printf("saved to file\n");
                fwrite(data, sizeof(data), 1, fp);
                fclose(fp);
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

            else if(strcmp(next, "history") == 0)
            {
                history(next, data, done);
            }

            // printf("%s\n", next);

            else
            {
                fg_bg(duplicate, flag, &proc_size, proc);
            }

        }
    }

    return 0;
}