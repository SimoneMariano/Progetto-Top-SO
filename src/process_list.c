
#include <ctype.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "utils.h"
#include "fifo_utils.h"
#include "process_list.h"
void process_list()
{
    /*char read[1];
    int list_fifo, manager_fifo;
    char buf[1024];
    list_fifo = open(LIST_FIFO_NAME, O_WRONLY);
    if (list_fifo == -1)
        handle_error("Cannot open list FIFO for reading");
    manager_fifo = open(MANAGER_FIFO_NAME, O_RDONLY);
    if (manager_fifo == -1)
        handle_error("Cannot open manager FIFO for writing");*/

    // file per recuperare la memoria totale
    FILE *fileMemInfo;

    // file per recuperare la CPU totale
    FILE *fileCpuInfo;

    // memoria totale (kb)
    int memTot;

    // totale tempo CPU
    float cpuTot;

    // puntatore alla direct struct
    struct dirent *pDs;

    // entro in proc
    DIR *directory;

    while (1)
    {

        directory = opendir("/proc/");

        // se la cartella non è vuota...
        if (directory)
        {

            // returna la memoria totale del sistema
            memTot = getTotalMemory(fileMemInfo);

            // returna la CPU totale del sistema
            cpuTot = getTotalCpu(fileCpuInfo);

            // printf("Cpu used: %f", cpuTot);

            // controllo gli elementi presenti nella cartella...
            pDs = readdir(directory);

            while (pDs)
            {

                // escludo le cartelle "." e ".." e controllo che siano delle cartelle con nome un numero
                if (((strcmp(pDs->d_name, ".") == 0 || strcmp(pDs->d_name, "..") == 0)))
                {
                    // do nothing
                }
                else if ((pDs->d_type == DT_DIR) && (isNumber(pDs->d_name) == 1))
                {

                    // printf("%s\n", pDs->d_name);

                    if (getPidandName(pDs) == -1)
                    {
                        goto E;
                    }
                    getUsedMemory(pDs, memTot);
                    getUsedCpu(pDs, cpuTot);
                }

                // proseguo nello scorrere la directory
                pDs = readdir(directory);
            }

        // chiudo la directory
        E:
            closedir(directory);
            printf("-------------------------\n");
            //read_from_pipe(manager_fifo, read, sizeof(char));
             /*if (strcmp(read, "q") == 0)
            {
                exit(EXIT_SUCCESS);
            }*/
            //memset(read, 0, sizeof(char));
                sleep(3);
        }
    }
}
