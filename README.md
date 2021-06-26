# lsh (manish's Shell)

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
    * nightswatch.c - nightswatch command
    * cronjob.c     - cronjob command
    * execute.c     - helper file which executes the commands
    * bg.c          - bg command
    * fg.c          - fg command
    * env.c         - setenv and unsetenv commands
    * jobs.c        - jobs command
    * redirection.c - helper file for executing input and output redirection
    * upArrow.c     - up arrow functionality

### Functioning
    * cd <directory path>                       - Changes directory to the given path. Changes to shell home if no directory is provided
    * pwd                                       - Shows the absolute path of the current working directory 
    * echo                                      - Prints the message to the terminal. Handled single and double quotes.
    * ls [al] <directory path>                  - Handles all variations of ls with a and l flags and directory path
    * pinfo [pid]                               - Prints process related info (pid, Process Status {R, S, S+, Z}, memory and Executable Path) about given pid. Prints process related info of shell program if no pid is provided
    * exit                                      - Exits the shell
    * quit                                      - Similar to exit
    * history [n]                               - Prints history of n (max 20) commands. Prints history of maximum 10 commands if n is not provided
    * nightswatch -n [time] <type>              - Repeats command of type <type> every <time> seconds until 'q' is pressed.
    * setenv var [value]                        - sets the value of the environment variable specified by var (create if it does not exist) to [value].
    * unsetenv var                              - destroys the environment variable specified by var
    * jobs                                      - prints list of all currently running background jobs along with their pid and their current state
    * kjob <jobNumber> <signalNumber>           - takes the job id of a running job and sends a signal value to that process
    * fg <jobNumber>                            - brings a running or a stopped background job with a given job number to background
    * bg <jobNumber>                            - changes a stopped background job to a running background job
    * overkill                                  - kills all background process at once
    * CTRL-Z                                    - changes the status of currently running job to stop, and pushes it in background process
    * CTRL-C                                    - cause a SIGINT signal to be sent to the current foreground job of this shell.
    * 'UP' arrow key                            - kth previous command gets executed on pressing the 'UP' arrow key k times
    * cronjob                                   - executes a particular command in fixed time interval for a certain period
    * input-output redirection functionality    - replicates (almost) what bash does
    * piping functionality                      - replicates (almost) what bash does
    * All other commands are implemented using execvp. 
    * Background Processing (can be run with '&') is handled for commands executed through execvp
