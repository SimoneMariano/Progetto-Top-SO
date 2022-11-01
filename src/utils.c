#include <stdlib.h>
#include "utils.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

//Simone Mariano
int isNumber(char *str) // Funzione per verificare se una stringa è un numero
{

    if (isdigit(*str))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//Iannone Bruno
int getTotalMemory(FILE *fileMemInfo) // funzione per recuperare la memoria totale del sistema da meminfo di proc

{
    int totalMemory;

    // salvo il valore della memoria totale (kb)
    if ((fileMemInfo = fopen("/proc/meminfo", "r")) == NULL)
    {
        // printf("Errore nell'apertura del file meminfo\n");
        exit(1);
    }
    else
    {
        char str[10]; //scarto stringa identificativa nel file
        fscanf(fileMemInfo, "%s %d", str, &totalMemory);
        //cleanup
        if(fflush(fileMemInfo)!= 0){
            handle_error("Utils.c: Errore nella fclose");
        }
        if(fclose(fileMemInfo)!= 0){
            handle_error("utils.c: Errore nella fclose");
        }
    }
    return totalMemory / 1.024;
}
//Simone Mariano
void getUsedMemory(struct dirent *pDsCopy, int totMem, struct_process *s_process) // %memory usage di un processo
{

    FILE *statusPid;

    int rss_value;

    char rss[256];

    char path[256];

    strcpy(path, "");
    strcat(strcat(strcat(path, "/proc/"), pDsCopy->d_name), "/smaps_rollup"); //Costruzione path

    if ((statusPid = fopen(path, "r")) != NULL)
    {

        fgets(rss, 256, statusPid);

        strcpy(rss, "");

        fscanf(statusPid, "%s %d", rss, &rss_value);

        if ((strcmp(rss, "Rss:") == 0)) //Individuo il valore di memory usage
        {

            float ret = ((((float)rss_value / (float)totMem) / 1.024) * 100);
            s_process->memory_usage = ret;
        }
        else
        {
            s_process->memory_usage = 0.0;
        }

        strcpy(path, "");
        //cleanup
        if(fflush(statusPid)!= 0){
            handle_error("Utils.c: Errore nella fclose");
        }
        if(fclose(statusPid)!= 0){
            handle_error("utils.c: Errore nella fclose");
        }
    }
}
//Simone Mariano
float getTotalCpu(FILE *fileCpuInfo) // Funzione per il calcolo della cpu totale utilizzata
{

    float uptime;

    if ((fileCpuInfo = fopen("/proc/uptime", "r")) == NULL)
    {
        exit(1);
    }
    else
    {
        //cleanup
        fscanf(fileCpuInfo, "%f", &uptime);
        if(fflush(fileCpuInfo)!= 0){
            handle_error("utils.c: Errore nella fclose");
        }
        if(fclose(fileCpuInfo)!= 0){
            handle_error("utils.c: Errore nella fclose");
        }
    }
    return uptime;
}
//Iannone Bruno
void getUsedCpu(struct dirent *pDsCopy, int cpuTot, struct struct_process *s_process) // % Cpu Utilizzata da un processo
{
    FILE *statPid;

    float utime, stime, cutime, cstime, starttime, hz = sysconf(_SC_CLK_TCK), totalTime, seconds, cpuUsage, trash;

    char stringTrash[128];

    char tmp[256];

    char path[256];
    strcpy(path, "");
    strcat(strcat(strcat(path, "/proc/"), pDsCopy->d_name), "/stat");

    if ((statPid = fopen(path, "r")) == NULL)
    {
        // printf("Errore nell'apertura del file stat di un Pid\n");
        exit(1);
    }
    else
    {
        // printf("%s", path);
        // printf("\n");

        fscanf(statPid, "%f", &trash);

        fscanf(statPid, "%s", stringTrash);
        strcpy(stringTrash, "");

        fscanf(statPid, "%s", stringTrash);

        while (strlen(stringTrash) != 1)
        {

            // printf("%s", stringTrash);
            // printf("\n");

            strcpy(stringTrash, "");
            fscanf(statPid, "%s", stringTrash);

            // printf("%s", stringTrash);
            // printf("\n");
        }
        // printf("%s", stringTrash);
        // printf("\n");

        for (int i = 0; i < 19; i++)
        {
            // printf("%d", i);
            // printf("\n");

            if (i == 10)
            {

                fscanf(statPid, "%f", &utime);
                // printf("utime: %f", utime);
                // printf("\n");
            }
            else if (i == 11)
            {

                fscanf(statPid, "%f", &stime);
                // printf("stime: %f", stime);
                // printf("\n");
            }
            else if (i == 12)
            {

                fscanf(statPid, "%f", &cutime);
                // printf("cutime: %f", cutime);
                // printf("\n");
            }
            else if (i == 13)
            {

                fscanf(statPid, "%f", &cstime);
                // printf("cstime: %f", cstime);
                // printf("\n");
            }
            else if (i == 18)
            {

                fscanf(statPid, "%f", &starttime);
                // printf("strttime: %f", starttime);
                // printf("\n");
            }
            else
            {
                fscanf(statPid, "%f", &trash);
                // printf("%f", trash);
                // printf("\n");
            }
        }

        // somma tra tempo speso come user e come kernel
        totalTime = utime + stime;

        // aggiungiamo il tempo per i figli come user e kernel
        totalTime = totalTime + cutime + cstime;

        seconds = cpuTot - (starttime / hz); //secondi di utilizzo

        // printf("seconds: %f", seconds);
        // printf("\n");

        cpuUsage = 100 * ((totalTime / hz) / seconds); //%di utilizzo

        s_process->cpu_usage = cpuUsage;

        //cleanup
        if(fflush(statPid)!= 0){
            handle_error("utils.c: Errore nella fclose");
        }
        
        if(fclose(statPid)!= 0){
            handle_error("utils.c: Errore nella fclose");
        }

    }
}

//SIMONE MARIANO
int getPidandName(struct dirent *pDsCopy, struct_process *s_process) //Funzione per ottenere PID e NOME di un processo (simultaneamente per mantenere una consistenza)
{

    FILE *statPid;

    char processName[128];
    char processName2[128]; //array di appoggio per costruzione del nome
    char processState[2];

    int pid;

    char path[256];
    strcpy(path, "");
    strcat(strcat(strcat(path, "/proc/"), pDsCopy->d_name), "/stat");

    if ((statPid = fopen(path, "r")) == NULL)
    {
        // printf("Errore nell'apertura del file stat di un Pid \n");
        return -1;
    }
    else
    {
        fscanf(statPid, "%d", &pid);

        fscanf(statPid, "%s", processName);

        fscanf(statPid, "%s", processName2);

        s_process->pid = pid;

        while (strlen(processName2) != 1)
        {

            // printf("%s", stringTrash);
            // printf("\n");

            strcat(processName, " ");
            strcat(processName, processName2);

            strcpy(processName2, "");
            fscanf(statPid, "%s", processName2);

            // printf("%s", stringTrash);
            // printf("\n");
        }

        strcpy(processState, processName2);
    }

    strcat(s_process->name, processName);
    strcat(s_process->state, processState);
    //cleanup
    if(fflush(statPid)!= 0){
            handle_error("utils.c: Errore nella fclose");
        }
    if(fclose(statPid)!= 0){
            handle_error("utils.c: Errore nella fclose");
        }
    

    return 0;
}
//Fondamenti II
void handle_error(char *msg) //Funzione per la gestione degli errori
{
    perror(msg);
    exit(EXIT_FAILURE);
}
//Iannone Bruno
int string_to_int(char *dest, int src) //Funzione per la conversione da stringa a intero
{
    int ret_value;
    ret_value = sprintf(dest, "%d", src);
    return ret_value;
}