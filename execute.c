#include "def.h"

void execute(char *next, char home[], char data[20][MAX_SIZE])
{
    if(strcmp(next, "cd") == 0)
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

    else if(strcmp(next, "bg") == 0)
    {
        bg(next, proc);
    }

    else if(strcmp(next, "fg") == 0)
    {
        fg(next, proc, &proc_size);
    }

    // printf("%s\n", next);

    else
    {
        // printf("here fg_bg\n");
        fg_bg(duplicate, flag, &proc_size, proc);
    }

}