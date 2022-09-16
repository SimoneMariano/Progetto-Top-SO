
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "process_list.h"
#include "fifo_utils.h"
#include "utils.h"
#include <signal.h>
void  stat_manager()
{
    /*int list_fifo, manager_fifo;
    char buf[1024];
    list_fifo = open(LIST_FIFO_NAME, O_RDONLY);
    if (list_fifo == -1)
        handle_error("Cannot open list FIFO for reading");
    manager_fifo = open(MANAGER_FIFO_NAME, O_WRONLY);
    if (manager_fifo == -1)
        handle_error("Cannot open manager FIFO for writing");*/
    
    while(1){

        // variabile per gli scanf
    char input[1];

    int pid;

    printf("Inserire PID del processo da gestire o q per chiudere\n");
    scanf("%s", input);
    if (strcmp(input, "q") == 0)
    {
        /*memset(buf,0,sizeof(char));
        int msg_len = strlen(buf);
        writeMsg(manager_fifo, buf, msg_len);*/

        // TODO: gestione errore della munmap
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
}
