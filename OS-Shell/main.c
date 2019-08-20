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

        // printf("%s", s);

        char command[MAX_SIZE];

        int cur = 0;
        while(s[cur] != ' ' && s[cur] != '\0')
        {
            command[cur] = s[cur];
            cur++;  
        }
        command[cur] = '\0';

        // printf("command: %s", command);
    
        if(strcmp("cd", command) == 0)
        {
            // cd();
        }

        else if(strcmp("pwd\n", command) == 0)
        {
            pwd();
        }


    }

    return 0;
}