
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "process_list.h"
#include "fifo_utils.h"
#include "utils.h"
#include <signal.h>
#include <semaphore.h>
void stat_manager()
{

    sem_t *shm1_sem = sem_open(SHM1_SEM, O_CREAT, 0600);

    if (shm1_sem == SEM_FAILED)
    {
        handle_error("sem_open filled");
    }
    int shm_fd = shm_open(SHM_NAME, O_RDWR | O_CREAT, 0660);
    if (shm_fd < 0)
    {
        handle_error("process_list.c: Errore nella shm_open");
    }
    int *shm_ptr;
    if ((shm_ptr = (int *)mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0)) == MAP_FAILED)
    {
        exit(EXIT_FAILURE);
        handle_error("process_list.c: errore nella mmap ");
    }
    memset(shm_ptr, 0, SHM_SIZE);

    while (1)
    {

        // variabile per gli scanf
        char input[1];

        int pid;

        printf("Inserire PID del processo da gestire o q per chiudere\n");
        scanf("%s", input);
        if (strcmp(input, "q") == 0)
        {
            if (sem_wait(shm1_sem) < 0)
            {
                handle_error("stat_manager.c: Errore nella wait");
            }
            shm_ptr[0] = 999;
            if (sem_post(shm1_sem) < 0)
            {
                handle_error("stat_manager.c: Errore nella post");
            }
            if (munmap(shm_ptr, SHM_SIZE) == -1)
            {
                handle_error("stat_manager.c: errore nella munmap");
            }
            if (sem_close(shm1_sem) < 0)
            {
                handle_error("process_list.c: Errore nella close di shm1_sem");
            }
            
            
            return;
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
