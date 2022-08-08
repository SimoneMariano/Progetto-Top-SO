#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <signal.h>

void* processManager()
{
    // variabile per gli scanf
    char input[128];

    int pid;

    printf("Inserire PID del processo da gestire o q per chiudere\n");
    scanf("%s", input);
    if (strcmp(input, "q") == 0)
    {
        exit(EXIT_SUCCESS);
    }
    else
    {
        pid = atoi(input);
        printf("k to kill, t to terminate, s to suspend, r to resume\n");
        scanf("%s", input);
        if (strcmp(input, "k") == 0)
        {
            kill(pid, SIGKILL);
        }
        else if (strcmp(input, "t") == 0)
        {
            kill(pid, SIGTERM);
        }
        else if (strcmp(input, "s") == 0)
        {
            kill(pid, SIGSTOP);
        }
        else if (strcmp(input, "r") == 0)
        {
            kill(pid, SIGCONT);
        }
    }
}