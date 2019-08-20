#include "def.h"

void prompt(char *home)
{
    char s[MAX_SIZE], *t, curPath[MAX_SIZE];

    t = getenv("LOGNAME");
    gethostname(s, MAX_SIZE);

    getcwd(curPath, MAX_SIZE);

    int n1 = strlen(home);
    int n2 = strlen(curPath);

    // printf("%s %s %d %d\n", curPath, home, n1, n2);

    if(n2 >= n1)
    {
        curPath[0] = '~';

        for(int i=n1; i<n2; i++)
        {
            // printf("%c ", curPath[i]);
            curPath[i-n1+1] = curPath[i];
        }
        curPath[n2-n1+1] = '\0';
    }

    printf("<%s@%s:%s> ", t, s, curPath);

    return;
}