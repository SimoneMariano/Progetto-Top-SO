#pragma once
#define LIST_FIFO_NAME  "fifo_client"
#define MANAGER_FIFO_NAME  "fifo_echo"
#include <errno.h>
#include <sys/types.h> // mkfifo()
#include <sys/stat.h>  // mkfifo()
//Sistemi di calcolo 2
int read_from_pipe(int fd, void* data, size_t data_len);
void writeMsg(int fd, char* buf, int size);

