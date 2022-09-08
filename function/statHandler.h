#include <ctype.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// funzione per verificare se la stringa passata sia un numero
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
    return num;
}

void getUsedMemory(struct dirent *pDsCopy, int totMem)
{

    FILE *statusPid;

    int num;

    char tmp[256];

    char path[256];

    strcpy(path, "");
    strcat(strcat(strcat(path, "/proc/"), pDsCopy->d_name), "/smaps");

    if ((statusPid = fopen(path, "r")) == NULL)
    {
        printf("Errore nell'apertura del file smaps di un Pid\n");
    }
    else
    {
        // printf("%s", path);
        // printf("\n");

        for (int i = 0; i < 4; i++)
        {
            fgets(tmp, 256, statusPid);
        }

        strcpy(tmp, "");

        fscanf(statusPid, "%s %d", tmp, &num);

        if (strcmp(tmp, "Rss:") == 0)
        {

            float ret = (((float)num / (float)totMem) * 100);

            printf("Mem usage: %f %%", ret);
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

    // salvo il valore della memoria totale (kb)
    if ((fileCpuInfo = fopen("/proc/uptime", "r")) == NULL)
    {
        printf("Errore nell'apertura del file meminfo\n");
        exit(1);
    }
    else
    {
        char str[10];
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
        //printf("%s", path);
        //printf("\n");

        fscanf(statPid, "%f", &trash);

        fscanf(statPid, "%s", stringTrash);
        //printf("%s", stringTrash);
        //printf("\n");

        strcpy(stringTrash, "");

        fscanf(statPid, "%s", stringTrash);
        //printf("%s", stringTrash);
        //printf("\n");


        for (int i = 0; i < 19; i++)
        {
            //printf("%d", i);
            //printf("\n");

            if (i==10)
            {

                fscanf(statPid, "%f", &utime);
                //printf("utime: %f", utime);
                //printf("\n");


            }
            else if (i==11)
            {

                fscanf(statPid,"%f", &stime);
                //printf("stime: %f", stime);
                //printf("\n");

            }
            else if (i==12)
            {

                fscanf(statPid,"%f", &cutime);
                //printf("cutime: %f", cutime);
                //printf("\n");

            }
            else if (i==13)
            {

                fscanf(statPid,"%f", &cstime);
                //printf("cstime: %f", cstime);
                //printf("\n");

            }
            else if (i==18)
            {

                fscanf(statPid,"%f", &starttime);
                //printf("strttime: %f", starttime);
                //printf("\n");

            }
            else{
                fscanf(statPid, "%f", &trash);
                //printf("%f", trash);
                //printf("\n");
            }

        }

        //somma tra tempo speso come user e come kernel
        totalTime = utime + stime;

        //aggiungiamo il tempo per i figli come user e kernel
        totalTime = totalTime + cutime + cstime;

        //printf("totaltime: %f", totalTime);
        //printf("\n");

        seconds = cpuTot - (starttime / hz);

        //printf("seconds: %f", seconds);
        //printf("\n");

        cpuUsage = 100 * ((totalTime / hz) / seconds);         

        fflush(statPid);
        fclose(statPid);

        //printf("Hz: %f", hz);
        //printf("\n");

        printf("Cpu usage: %f %%", cpuUsage);
        printf("\n");

    }
}

int getPidandName (struct dirent *pDsCopy){

    FILE *statPid;

    char processName[128];

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

    }

    fflush(statPid);
    fclose(statPid);

    printf("Pid: %d, Name: %s", pid, processName);
    printf("\n");
    return 0;

}

void* statManager(){
        // file per recuperare la memoria totale
    FILE *fileMemInfo;

    // file per recuperare la CPU totale
    FILE *fileCpuInfo;

    // memoria totale (kb)
    int memTot;

    // CPU totale
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

                    if(getPidandName(pDs)==-1){
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
            sleep(30);

        }
    }
}