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
#include "string.h"
#include <semaphore.h>

int main(int argc, char *argv[])
{
    // Pulizia semafori in caso di arresto imprevisto in esecuzioni precedenti
    sem_unlink(SHM1_SEM);
    sem_unlink(SHM2_SEM);

    // Apertura semafori
    sem_t *shm1_sem = sem_open(SHM1_SEM, O_CREAT, 0600, 1);

    if (shm1_sem == SEM_FAILED)
    {
        handle_error("sem_open filled");
    }
    sem_t *shm2_sem = sem_open(SHM2_SEM, O_CREAT, 0600, 1);

    if (shm2_sem == SEM_FAILED)
    {
        handle_error("sem_open filled");
    }

    // Pulizia shared memory in caso di arresto imprevisto in esecuzioni precedenti
    shm_unlink(SHM_NAME);

    // Apertura shared mamory
    int shm_fd = shm_open(SHM_NAME, O_RDWR | O_CREAT, 0660);
    if (shm_fd < 0)
    {
        exit(EXIT_FAILURE);
    }

    if (ftruncate(shm_fd, 2 * SHM_SIZE) == -1)
    {
        handle_error("main.c: Errore nella ftruncate");
    }

    int *shm_ptr;

    // Fork
    pid_t pid;

    pid = fork();

    if (pid == -1)
    {
        handle_error("main.c: Errore nella fork");
    }

    if (pid == 0) //Nel figlio avvio il monitor dei processi
    {

        system("gnome-terminal reset --tab -- /bin/bash -c './function/processLauncher; exec /bin/bash -i'");
        _exit(EXIT_SUCCESS);
    }
    else //Nel padre avvio la gestione dei segnali, poi, una volta terminato stat_manager(), procedo a chiudere simultaneamente il monitor
    {
        stat_manager();

        //chiusura simultanea monitor
        if ((shm_ptr = (int *)mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0)) == MAP_FAILED)
        {
            handle_error("process_list.c: errore nella mmap ");
        }
    
        if (sem_wait(shm2_sem) < 0)
        {
            handle_error("stat_manager.c: Errore nella wait");
        }
        if (sem_post(shm2_sem) < 0)
        {
            handle_error("stat_manager.c: Errore nella post");
        }
        kill(shm_ptr[1], SIGKILL); //invio SIGKILL al monitor

        // Cleanup di shared memory e semafori
        if (shm_unlink(SHM_NAME) < 0)
        {
            handle_error("main.c_ Errore nella shm_unlink");
        }

        if (close(shm_fd) < 0)
        {

            handle_error("main.c: Errore nella close della shared memory");
        }
        if (sem_close(shm1_sem) < 0)
        {
            handle_error("process_list.c: Errore nella close di shm1_sem");
        }
        if (sem_close(shm2_sem) < 0)
        {
            handle_error("process_list.c: Errore nella close di shm2_sem");
        }

        if (sem_unlink(SHM1_SEM) < 0)
        {
            handle_error("main.c: Errore nella sem_unlink di SHM1_SEM");
        }
        if (sem_unlink(SHM2_SEM) < 0)
        {
            handle_error("main.c: Errore nella sem_unlink di SHM2_SEM");
        }
    }
    return 0;
}