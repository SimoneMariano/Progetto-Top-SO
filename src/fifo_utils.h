#pragma once
#define SHM_NAME  "SHM"
#define SHM_SIZE  sizeof(int)
#define SHM1_SEM "SEM1"
#define SHM2_SEM "SEM2"

#include <errno.h>
#include <sys/types.h> // mkfifo()
#include <sys/stat.h>  // mkfifo()
//Sistemi di calcolo 2
int read_from_pipe(int fd, void* data, size_t data_len);
void writeMsg(int fd, char* buf, int size);
int readOneByOne(int fd, char* buf, char separator);

