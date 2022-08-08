#include "base.h"

int main(int argc, char *argv[]){

    //file per recuperare la memoria totale
    FILE* fileMemInfo;

    //memoria totale (kb)
    int memTot; 

    //puntatore alla direct struct
    struct dirent *pDs;

    //entro in proc
    DIR *directory; 
    directory = opendir("/proc/");

    //se la cartella non è vuota...
    if (directory){     

        //returna la memoria totale del sistema
        memTot = getTotalMemory(fileMemInfo);

        //controllo gli elementi presenti nella cartella...      
        pDs = readdir(directory);
        while (pDs){

            //escludo le cartelle "." e ".." e controllo che siano delle cartelle con nome un numero
            if(((strcmp(pDs->d_name,".")==0 || strcmp(pDs->d_name,"..")==0))) {
                //do nothing
            } else if ((pDs->d_type == DT_DIR) && (isNumber(pDs->d_name)==1)) {

                //printf("%s\n", pDs->d_name);

                funzioneBase( pDs, memTot );

            }

            //proseguo nello scorrere la directory
            pDs = readdir(directory);

        }
        
        //chiudo la directory
        closedir(directory);

    }
    return 0;
}