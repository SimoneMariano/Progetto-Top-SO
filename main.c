#include "statHandler.h"
#include "processHandler.h"

int main(int argc, char *argv[])
{

    while (1)
    {
        pthread_t thread_id[2];
        pthread_create(&thread_id[0], NULL, processManager, NULL);
        pthread_create(&thread_id[1], NULL, statManager, NULL);
        pthread_detach(thread_id[0]);
        pthread_detach(thread_id[1]);
        sleep(10);
    }

    return 0;
}