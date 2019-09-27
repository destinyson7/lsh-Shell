#include "def.h"

int countUpArrows(char *s)
{
    int upArrows = 0;
    int slen = strlen(s);
    for(int i = 0; i < slen-2; i++)
    {
        // printf("%d ", (int)s[i]);
        if((int)s[i] == 27 && (int)s[i+1] == 91 && (int)s[i+2] == 65)
        {
            upArrows++;
            i+=2;
        }
    }

    // printf("%d **\n", upArrows);

    // printf("******\n\n");
    // for(int i = 19; i >= 0; i--)
    // {
    //     if(data[i] == NULL)
    //     {
    //         printf("***********\n");
    //         break;
    //     }
    //     printf("%s ***\n", data[i]);
    // }
    // printf("******\n\n");

    // printf("\n");

    // printf("%s", s);


    return upArrows;
}