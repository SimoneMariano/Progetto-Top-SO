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
#include "string.h"
#include <semaphore.h>


int main(int argc, char *argv[])
{

    sem_unlink(SHM1_SEM);
    sem_unlink(SHM2_SEM);

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

    shm_unlink(SHM_NAME);
    int shm_fd = shm_open(SHM_NAME, O_RDWR | O_CREAT, 0660);
    int *shm_ptr;
    if (shm_fd < 0)
    {
        exit(EXIT_FAILURE);
    }

    if (ftruncate(shm_fd, 2 * SHM_SIZE) == -1)
    {
        handle_error("main.c: Errore nella ftruncate");
    }

    pid_t pid;

    pid = fork();

    if (pid == -1)
    {
        handle_error("main.c: Errore nella fork");
    }

    if (pid == 0)
    {

        //printf("Fork Child %d\n", getpid());
        system("gnome-terminal reset --tab -- /bin/bash -c './function/processLauncher; exec /bin/bash -i'");
        if ((shm_ptr = (int *)mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0)) == MAP_FAILED)
        {
            exit(EXIT_FAILURE);
            handle_error("process_list.c: errore nella mmap ");
        }

        //printf("Fork Child2 %d\n", getpid());

        _exit(EXIT_SUCCESS);
    }
    else
    {
        //printf("Fork Father %d\n", getpid());
        stat_manager();

        if ((shm_ptr = (int *)mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0)) == MAP_FAILED)
        {
            exit(EXIT_FAILURE);
            handle_error("process_list.c: errore nella mmap ");
        }
        //printf("Entro in cs ");
        if (sem_wait(shm2_sem) < 0)
        {
            handle_error("stat_manager.c: Errore nella post");
        }
        //printf("%d\n", shm_ptr[2]);
        kill(shm_ptr[1], SIGKILL);
        //TODO: HANDLER E CONTROLLO ERRORI 

        if(shm_unlink(SHM_NAME)<0){
            handle_error("main.c_ Errore nella shm_unlink");
        }

        if(close(shm_fd)<0){

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
        
        if(sem_unlink(SHM1_SEM)<0){
            handle_error("main.c: Errore nella sem_unlink di SHM1_SEM");
        }
        if(sem_unlink(SHM2_SEM)<0){
            handle_error("main.c: Errore nella sem_unlink di SHM2_SEM");
        }
    }
    return 0;
}