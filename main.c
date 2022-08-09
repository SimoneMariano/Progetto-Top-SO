#include "function/statHandler.h"
#include "function/processHandler.h"

int main(int argc, char *argv[])
{

    char* array[128] = {"./function/processLauncher", NULL};

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
        system("gnome-terminal -- ./function/processLauncher");

    }
    else
    {
        // processo Padre
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, processManager, NULL);

    }
}