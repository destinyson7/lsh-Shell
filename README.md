# Computer Systems Engineering-1 
## Assignment 2

**Tanish Lad**
**2018114005**

## lsh (laaaad's Shell)

### Pre-requisites
You need to install **ncurses.h** library to make this work. You can install it by using
- `sudo apt-get install libncurses5-dev libncursesw5-dev`

### Usage
1. make
2. ./lsh

To delete all .o files, run `make clean`.



### Files
    * main.c        - contains the main functioning of the shell
    * def.h         - contains all the required headers and functions
    * prompt.c      - to display the prompt to user
    * cd.c          - cd command
    * pinfo.c       - pinfo command
    * echo.c        - echo command
    * pwd.c         - pwd command
    * ls.c          - ls command
    * fg_bg.c       - handling background and foreground processes for commands which are executed through execvp
    * history.c     - history command
    * nightswatch.c - executes until the key q is pressed

### Functioning
    * cd <directory path>           - Changes directory to the given path. Changes to shell home if no directory is provided
    * pwd                           - Shows the absolute path of the current working directory 
    * echo                          - Prints the message to the terminal. Handled single and double quotes.
    * ls [al] <directory path>      - Handles all variations of ls with a and l flags and directory path
    * pinfo [pid]                   - Prints process related info (pid, Process Status {R, S, S+, Z}, memory and Executable Path) about given pid. Prints process related info of shell program if no pid is provided
    * exit                          - Exits the shell
    * quit                          - Similar to exit
    * history [n]                   - Prints history of n (max 20) commands. Prints history of maximum 10 commands if n is not provided
    * nightswatch -n [time] <type>  - Repeats command of type <type> every <time> seconds until 'q' is pressed.
    * All other commands are implemented using execvp. 
    * Background Processing (can be run with '&') is handled for commands executed through execvp
