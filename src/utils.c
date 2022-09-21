#include <stdlib.h>
#include "utils.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

int isNumber(char *str)
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

// funzione per recuperare la memoria totale del sistema da meminfo di proc
int getTotalMemory(FILE *fileMemInfo)
{

    int num;

    // salvo il valore della memoria totale (kb)
    if ((fileMemInfo = fopen("/proc/meminfo", "r")) == NULL)
    {
        printf("Errore nell'apertura del file meminfo\n");
        exit(1);
    }
    else
    {
        char str[10];
        fscanf(fileMemInfo, "%s %d", str, &num);
        // printf("%d", num);
        // printf("\n");
        fflush(fileMemInfo);
        fclose(fileMemInfo);
    }
    return num / 1.024;
}

void getUsedMemory(struct dirent *pDsCopy, int totMem)
{

    FILE *statusPid;

    int rss_value;

    char rss[256];

    char path[256];

    strcpy(path, "");
    strcat(strcat(strcat(path, "/proc/"), pDsCopy->d_name), "/smaps_rollup");

    if ((statusPid = fopen(path, "r")) == NULL)
    {
        printf("Errore nell'apertura del file smaps di un Pid\n");
    }
    else
    {
        // printf("%s", path);
        // printf("\n");

        fgets(rss, 256, statusPid);

        strcpy(rss, "");

        fscanf(statusPid, "%s %d", rss, &rss_value);

        if ((strcmp(rss, "Rss:") == 0))
        {

            float ret = ((((float)rss_value / (float)totMem) / 1.024) * 100);

            printf("Memo usage: %f %%", ret);
            printf("\n");
        }
        else
        {

            printf("Mem usage: 0.000000 %%");
            printf("\n");
        }

        strcpy(path, "");
        fflush(statusPid);
        fclose(statusPid);
    }
}

float getTotalCpu(FILE *fileCpuInfo)
{

    float uptime;

    if ((fileCpuInfo = fopen("/proc/uptime", "r")) == NULL)
    {
        printf("Errore nell'apertura del file uptime\n");
        exit(1);
    }
    else
    {

        fscanf(fileCpuInfo, "%f", &uptime);
        // printf("%d", uptime);
        // printf("\n");
        fflush(fileCpuInfo);
        fclose(fileCpuInfo);
    }
    return uptime;
}

void getUsedCpu(struct dirent *pDsCopy, int cpuTot)
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
        printf("Errore nell'apertura del file stat di un Pid\n");
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

        // printf("totaltime: %f", totalTime);
        // printf("\n");

        seconds = cpuTot - (starttime / hz);

        // printf("seconds: %f", seconds);
        // printf("\n");

        cpuUsage = 100 * ((totalTime / hz) / seconds);

        fflush(statPid);
        fclose(statPid);

        // printf("Hz: %f", hz);
        // printf("\n");

        printf("Cpu usage: %f %%", cpuUsage);
        printf("\n");
    }
}

int getPidandName(struct dirent *pDsCopy)
{

    FILE *statPid;

    char processName[128];
    char processName2[128];
    char processState[2];

    int pid;

    char path[256];
    strcpy(path, "");
    strcat(strcat(strcat(path, "/proc/"), pDsCopy->d_name), "/stat");

    if ((statPid = fopen(path, "r")) == NULL)
    {
        printf("Errore nell'apertura del file stat di un Pid \n");
        return -1;
    }
    else
    {
        fscanf(statPid, "%d", &pid);

        fscanf(statPid, "%s", processName);

        fscanf(statPid, "%s", processName2);

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

    fflush(statPid);
    fclose(statPid);

    printf("Pid: %d, Name: %s, State: %s", pid, processName, processState);
    printf("\n");
    return 0;
}

void handle_error(char* msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int string_to_int(char* dest, int src){
int ret_value;
    ret_value = sprintf(dest,"%d",src);
    return ret_value;

}