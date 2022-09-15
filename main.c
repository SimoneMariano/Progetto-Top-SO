
#include "function/statHandler.h"
#include "function/processHandler.h"
#include "signalHandler.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "common.h"
#include <errno.h>

int shm_fd;
int* shm_ptr;

int main(int argc, char *argv[])
{
    

    int shm_fd = shm_open(SHM_NAME, O_RDWR | O_CREAT, 0660);
    // TODO: controllo dell'errore affinato
    if (shm_fd < 0)
    {
        exit(EXIT_FAILURE);
    }

    if (ftruncate(shm_fd, SHM_SIZE) == -1)
    {
        handle_error("main.c: Errore nella ftruncate del figlio")
    }

    pid_t pid;

    pid = fork();

    if (pid == -1)
    {
        handle_error("main.c: Errore nella fork");
    }

    if (pid == 0)
    {
        if ((shm_ptr = (int *)mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0)) == MAP_FAILED)
        {
            handle_error("main.c: errore nella mmap del figlio");
        }
        *shm_ptr = getpid();
        printf("%d\n",*shm_ptr);
        // processo figlio

        /*struct sigaction act = {0};
        act.sa_handler = &sigHandler; 
        if(sigaction(SIGTERM,&act,NULL)==-1){
            handle_error("main.c: Errore nella sigaction del figlio ");
        }*/

        // printf("%d\n",*shm_addr);
        // printf("%d\n", getpid());

        system("gnome-terminal reset --tab -- /bin/bash -c './function/processLauncher; exec /bin/bash -i'");
        
        printf("Muoio");
    }
    else
    {
        if ((shm_ptr = (int *)mmap(0, SHM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0)) == MAP_FAILED)
        {
            handle_error("main.c: errore nella mmap del padre");
        }
        while (1)
        {
            processManager(shm_ptr);
        }
    }
        if(close(shm_fd)==-1){
            handle_error("main.c: errore nella chiusura di shm_fd")
        }
        if(shm_unlink(SHM_NAME)<0){
            handle_error("main.c: errore nella shm_unlink in uscita del main");
        }

}