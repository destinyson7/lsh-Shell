#include "def.h"

int check(char *cur)
{
    if(strcmp(cur, "quit") == 0)
    {
        return 0;
    }

    else if(strcmp(cur, "cd") == 0)
    {
        return 0;
    }

    else if(strcmp(cur, "kjob") == 0)
    {
        return 0;
    }

    else if(strcmp(cur, "overkill") == 0)
    {
        return 0;
    }

    else if(strcmp(cur, "bg") == 0)
    {
        return 0;
    }

    else if(strcmp(cur, "fg") == 0)
    {
        return 0;
    }

     if(strcmp(cur, "pwd") == 0)
    {
        return 1;
    }

    else if(strcmp(cur, "echo") == 0)
    {
        return 1;
    }

    else if(strcmp(cur, "ls") == 0)
    {
        return 1;
    }

    else if(strcmp(cur, "pinfo") == 0)
    {
        return 1;
    }

    else if(strcmp(cur, "history") == 0)
    {
        return 1;
    }

    else if(strcmp(cur, "nightswatch") == 0)
    {
        return 1;
    }

    else if(strcmp(cur, "jobs") == 0)
    {
        return 1;
    }

    else if(strcmp(cur, "setenv") == 0)
    {
        return 0;
    }

    else if(strcmp(cur, "unsetenv") == 0)
    {
        return 0;
    }

    return 0;
    
}