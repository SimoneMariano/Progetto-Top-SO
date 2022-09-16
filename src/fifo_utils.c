#include <errno.h>
#include "fifo_utils.h"
#include <stdio.h>
#include "utils.h"
#include <unistd.h>

int read_from_pipe(int fd, void *data, size_t data_len) {

    int read_bytes = 0, ret;
    while (read_bytes < data_len) {
        ret = read(fd, data + read_bytes, data_len - read_bytes);
        if (ret == -1 && errno == EINTR) continue;
        if (ret == -1) handle_error("error reading from pipe");
        if (ret ==  0) handle_error("unexpected close of the pipe");
        read_bytes += ret;
    }
    return read_bytes;
}

void writeMsg(int fd, char* buf, int size) {

    int ret;
    
    int bytes_sent = 0;
    while (bytes_sent < size) {
        ret = write(fd, buf + bytes_sent, size - bytes_sent);
        if (ret == -1 && errno == EINTR) continue;
        if (ret == -1) handle_error("Cannot write to FIFO");
        bytes_sent += ret;
    }
    printf("Sent %d bytes\n",bytes_sent);
    fflush(stdout);
}