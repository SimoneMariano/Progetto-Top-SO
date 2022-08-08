#include <ctype.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//funzione per verificare se la stringa passata sia un numero
int isNumber (char* str) {

    if (isdigit(*str)) { return 1; } else { return 0; }

}

//funzione per recuperare la memoria totale del sistema da meminfo di proc
int getTotalMemory (FILE* fileMemInfo) {

    int num;

    //salvo il valore della memoria totale (kb)
    if ((fileMemInfo = fopen ("/proc/meminfo", "r")) == NULL) {
        printf("Errore nell'apertura del file meminfo\n");
        exit(1);
    } else {
        char str[10];
        fscanf(fileMemInfo, "%s %d", str, &num);
        printf("%d", num);
        printf("\n");
        fflush(fileMemInfo);
        fclose(fileMemInfo);
    }
    return num;
}

void funzioneBase (struct dirent *pDsCopy, int totMem){

    FILE* statusPid;

    int num;

    char tmp[256];

    char path[256];
    strcpy (path, "");
    strcat(strcat(strcat(path, "/proc/"), pDsCopy->d_name), "/status");

    if ((statusPid = fopen (path, "r")) == NULL) {
        printf("Errore nell'apertura del file status di un Pid\n");
        exit(1);
    } else {
        printf("%s", path);
        printf("\n");

        for (int i = 0; i < 21; i++) {
            fgets(tmp, 256, statusPid);
        }

        strcpy (tmp, "");

        fscanf(statusPid, "%s %d", tmp, &num);

        if ( strcmp(tmp, "VmRSS:") == 0 ){

            float ret = ((float) num / (float) totMem)*100;
            
            printf("%s %f %%", tmp, ret);
            printf("\n");

        } else {

            printf("VmRSS: 0.000000 %%");
            printf("\n");

        }

        strcpy (path, "");
        fflush(statusPid);
        fclose(statusPid);

    }
}