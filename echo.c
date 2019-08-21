#include "def.h"

void echo(char *cur)
{
    cur = strtok(NULL, " \t");

    while(cur != NULL)
    {
        printf("%s ", cur);

        cur = strtok(NULL, " \t");
    }
    printf("\n");
}