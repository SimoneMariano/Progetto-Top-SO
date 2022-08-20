#include "function/statHandler.h"
#include "function/processHandler.h"

int main(int argc, char *argv[])
{

    char* array[128] = {"sh -c ./ciao.c"};   /*.|function|processLauncher", NULL};*/

    pid_t pid;

    pid = fork();

    if (pid == -1)
    {
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        // processo figlio

        //execvp("/bin/sh", array);
        
        system("gnome-terminal reset --tab -- /bin/bash -c './function/processLauncher; exec /bin/bash -i'");
        //printf("Muoio");
        
        

    }
    else
    {
        while(1){
            processManager();
        }

    }
}