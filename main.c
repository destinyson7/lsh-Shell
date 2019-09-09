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

    // For history commmand
    FILE *fp;

    char data[20][MAX_SIZE];

    int done = 0;

    char newPath[MAX_SIZE];
    strcpy(newPath, home);
    strcat(newPath, "/");
    strcat(newPath, "data.txt");
    fp = fopen(newPath, "rb");
    
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
            if(strcmp(data[i], "\0"))
            {
                done++;
            }
        }
        
        fclose(fp);
    }

    while(1)
    {
        prompt(home);

        // Disabling Ctrl + C and Ctrl + Z signals.
        signal(SIGINT, checkSignal);
        signal(SIGTSTP, checkSignal);

        // For background process status printing
        int status;
        int get = waitpid(-1, &status, WNOHANG);

        if(get > 0)
        {
            if(!WIFEXITED(status))
            {
                char print[MAX_SIZE] = "";
                for(int i = 0; i < MAX_SIZE; i++)
                {
                    if(proc[i].pid == get)
                    {
                        proc[i].pid = -1;

                        for(int j = 0; proc[i].name[j] != '\0'; j++)
                        {
                            if(proc[i].name[j] == ' ')
                            {
                                print[j] = '\0';
                                break;
                            }

                            print[j] = proc[i].name[j];
                        }

                        // strcpy(print, proc[i].name);
                    }
                }

                if(strcmp(print, "") == 0)
                {
                    strcpy(print, "Process");
                }

                char exitPrint[MAX_SIZE];
                sprintf(exitPrint, "%s with pid %d exited with exit status: %d\n", print, get, WEXITSTATUS(status));
                write(2, exitPrint, strlen(exitPrint));
            }
        }

        for(int i = 0; i < MAX_SIZE; i++)
        {
            if(kill(proc[i].pid, 0) == -1)
            {
                char print[MAX_SIZE] = "";
                for(int j = 0; proc[i].name[j] != '\0'; j++)
                {
                    if(proc[i].name[j] == ' ')
                    {
                        print[j] = '\0';
                        break;
                    }

                    print[j] = proc[i].name[j];
                }

                if(strcmp(print, "") == 0)
                {
                    strcpy(print, "Process");
                }
                
                // strcpy(print, proc[i].name);
                
                char exitPrint[2*MAX_SIZE];
                sprintf(exitPrint, "%s with pid %d exited normally\n", print, proc[i].pid);
                write(2, exitPrint, strlen(exitPrint));
                // fflush(stdout);

                // prompt(home);
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
            // Checking if '&' is present or not
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

            // To ensure that null string does not get added in history command
            if(strcmp(command[i], "\0") == 0)
            {
                continue;
            }

            // printf("%s cur\n", command[i]);
            char duplicate[MAX_SIZE];
            strcpy(duplicate, command[i]);

            char *next = strtok(command[i], " \t\n");

            if(next == NULL)
            {
                continue;
            }

            if(duplicate[0] != ' ')
            {
                done = storeHistory(done, data, duplicate);
            }
            // printf("%d done\n", done);

            // for(int i = 0; i < 20; i++)
            // {
            //     printf("%s\n", data[i]);
            // }

            if(strcmp(next, "quit") == 0)
            {
                char newPath2[MAX_SIZE];
                strcpy(newPath2, home);
                strcat(newPath2, "/");
                strcat(newPath2, "data.txt");
                fp = fopen(newPath2, "wb");
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
                exEcho(next);
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

            else if(strcmp(next, "nightswatch") == 0)
            {
                nightswatch(next);
            }

            else if(strcmp(next, "setenv") == 0)
            {
                setEnv(next);
            }

            else if(strcmp(next, "unsetenv") == 0)
            {
                unsetEnv(next);
            }

            else if(strcmp(next, "jobs") == 0)
            {
                jobs(proc);
            }

            else if(strcmp(next, "kjob") == 0)
            {
                kjob(next, proc);
            }

            else if(strcmp(next, "overkill") == 0)
            {
                overkill(proc);
            }

            // printf("%s\n", next);

            else
            {
                // printf("here fg_bg\n");
                fg_bg(duplicate, flag, &proc_size, proc);
            }

        }
    }

    return 0;
}