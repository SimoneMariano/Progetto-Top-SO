#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "src/process_list.h"
#include "src/utils.h"
#include "src/stat_manager.h"
#include "src/fifo_utils.h"



int pipe_fd[2];

int main(int argc, char *argv[])
{
    /*int ret;
    ret = mkfifo(LIST_FIFO_NAME, 0666);
    if(ret) handle_error("Cannot create Echo FIFO");
    ret = mkfifo(MANAGER_FIFO_NAME, 0666);
    if(ret) handle_error("Cannot create Client FIFO");*/
    

    pid_t pid;

    pid = fork();

    if (pid == -1)
    {
        handle_error("main.c: Errore nella fork");
    }

    if (pid == 0)
    {

        system("gnome-terminal reset --tab -- /bin/bash -c './function/processLauncher; exec /bin/bash -i'");
        // BUG?
        _exit(EXIT_SUCCESS);
    }
    else
    {
        
        
        
           stat_manager();
        
    }
}