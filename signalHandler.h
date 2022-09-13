#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

static void sigHandler(int signum)
{

    if (signum == SIGKILL)
    {
        printf("Ricevuto SIGKILL\n");
        munmap(shm_addr, 4);
        // TODO: gestione errore della munmap
        shm_unlink("shmemo");
        // TODO: gestione errore della unlink
    }

}