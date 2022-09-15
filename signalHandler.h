#pragma once
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "common.h"

static void sigHandler(int signum)
{

    /*if (signum == SIGTERM)
    {
        printf("Ricevuto SIGTERM\n");
        if(munmap(shm_ptr, SHM_SIZE)<0){
            handle_error("signalHandler.h: Errore durante la unmap del figlio");
            _exit(EXIT_SUCCESS);
        }
        
        
    }*/
    printf("Segnale arrivato");

}