#include "function/statHandler.h"
#include "function/processHandler.h"ù
#include "signalHandler.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{

    char *array[128] = {"sh -c ./ciao.c"}; /*.|function|processLauncher", NULL};*/

    pid_t pid;

    pid = fork();

    if (pid == -1)
    {
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {

        // processo figlio

        if (signal(SIGKILL, sigHandler) == SIG_ERR){
            printf("Errore sulla sigkill\n");
        }

        int shm_fd = shm_open("shmemo", O_RDWR | O_CREAT, 0660);
        // TODO: controllo dell'errore affinato
        if (shm_fd < 0)
        {
            exit(EXIT_FAILURE);
        }

        int shm_err = ftruncate(shm_fd, 4);
        if (shm_err < 0)
        {
            exit(EXIT_FAILURE);
        }

        int* shm_addr = mmap (0, 4, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

        *shm_addr = getpid();

        // printf("%d\n",*shm_addr);
        // printf("%d\n", getpid());

        system("gnome-terminal reset --tab -- /bin/bash -c './function/processLauncher; exec /bin/bash -i'");
        // printf("Muoio");
    }
    else
    {
        while (1)
        {
            processManager();
        }
    }
}