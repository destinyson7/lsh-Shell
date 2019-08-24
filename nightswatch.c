#include "def.h"

void dirty(int n)
{
    FILE *fp;

    initscr();
    nodelay(stdscr, TRUE);

    int line = 0;

    while(1)
    {
        char path[MAX_SIZE] = "/proc/meminfo";
        fp = fopen(path, "r");

        char *store = NULL;
        size_t len = 0;

        for(int i = 0; i < 17; i++)
        {
            getline(&store, &len, fp);
        }

        fclose(fp);

        int ind = 0;
        while(store[ind] != ' ' && store[ind] != '\t')
        {
            ind++;
        }

        while(store[ind] == ' ' || store[ind] == '\t')
        {
            ind++;
        }

        // printf("here 1\n");

        char toPrint[MAX_SIZE];

        for(int i = ind; store[i] != '\0' && store[i] != '\n'; i++)
        {
            toPrint[i-ind] = store[i];

            if(store[i+1] == '\0' || store[i+1] == '\n')
            {
                toPrint[i-ind+1] = '\0';
                break;
            }
        }

        mvprintw(line++, 0, toPrint);

        clock_t var = clock();

        while(((clock() - var)/CLOCKS_PER_SEC) < n)
        {
            nodelay(stdscr, TRUE);

            char quit = getch();

            if(quit == 'q')
            {
                endwin();
                return;
            }   
        }
    }
}

void interrupt(int n)
{
    FILE *fp;

    initscr();
    nodelay(stdscr, TRUE);

    int noOfThreads = 8;
    int spaces = 0;
    int line = 0;

    for(int i = 0; i < noOfThreads; i++)
    {
        char temp[MAX_SIZE];
        sprintf(temp, "CPU%d", i);
        mvprintw(line, spaces, temp);
        spaces += 15;
    }

    line = 1;

    while(1)
    {
        char path[MAX_SIZE] = "/proc/interrupts";
        fp = fopen(path, "r");

        char *store = NULL;
        size_t len = 0;

        for(int i = 0; i < 3; i++)
        {
            getline(&store, &len, fp);
        }

        char commands[10][MAX_SIZE];

        char *next = strtok(store, " \t\n");
        int current = 0;

        while(next != NULL)
        {
            // commands[current] = next;
            strcpy(commands[current], next);
            current++;
            next = strtok(NULL, " \t\n");
        }

        // printf("here 3\n");

        spaces = 0;

        for(int i = 1; i <= 8; i++)
        {
            mvprintw(line, spaces, commands[i]);
            spaces += 15;
        }
        line++;

        clock_t var = clock();

        while(((clock() - var)/CLOCKS_PER_SEC) < n)
        {
            nodelay(stdscr, TRUE);

            char quit = getch();

            if(quit == 'q')
            {
                endwin();
                return;
            }   
        }

        fclose(fp);
    }
}

void nightswatch(char *token)
{
    char commands[5][MAX_SIZE];
    
    token = strtok(NULL, " \t\n");

    int cur = 0;

    while(token != NULL)
    {
        strcpy(commands[cur], token);
        cur++;

        token = strtok(NULL, " \t\n");
    }   

    if(cur != 3)
    {
        perror("Invalid number of arguments");
        return;
        // exit(0);
    }

    if(strcmp(commands[0], "-n") != 0 && strcmp(commands[1], "-n") != 0)
    {
        perror("Invalid set of arguments");
        // exit(0);
        return;
    }


    char num[MAX_SIZE];
    char type[MAX_SIZE];

    if(commands[0][0] == '-')
    {
        strcpy(num, commands[1]);
        strcpy(type, commands[2]);
    }

    else
    {
        strcpy(num, commands[2]);
        strcpy(type, commands[0]);
    }

    int n = 0;    
    int len = strlen(num);
    int mul = 1;

    for(int i = len - 1; i >= 0; i--)
    {
        n+=(mul*(num[i]-48));
        mul*=10;
    }

    // printf("%d %s\n", n, type);

    if(strcmp(type, "interrupt") == 0)
    {
        clear();
        interrupt(n);
    }

    else if(strcmp(type, "dirty") == 0)
    {
        clear();
        dirty(n);
    }
}