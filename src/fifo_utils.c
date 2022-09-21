#include <errno.h>
#include "fifo_utils.h"
#include <stdio.h>
#include "utils.h"
#include <unistd.h>

int read_from_pipe(int fd, void *data, size_t data_len)
{

    int read_bytes = 0, ret;
    while (read_bytes < data_len)
    {
        ret = read(fd, data + read_bytes, data_len - read_bytes);
        if (ret == -1 && errno == EINTR)
            continue;
        if (ret == -1)
            handle_error("error reading from pipe");
        if (ret == 0)
            handle_error("unexpected close of the pipe");
        read_bytes += ret;
    }
    return read_bytes;
}

void writeMsg(int fd, char *buf, int size)
{

    int ret;

    int bytes_sent = 0;
    while (bytes_sent < size)
    {
        ret = write(fd, buf + bytes_sent, size - bytes_sent);
        if (ret == -1 && errno == EINTR)
            continue;
        if (ret == -1)
            handle_error("Cannot write to FIFO");
        bytes_sent += ret;
    }
    printf("Sent %d bytes\n", bytes_sent);
    fflush(stdout);
    
}
int readOneByOne(int fd, char *buf, char separator)
{

    int ret;

    /** [SOLUTION] READ THE MESSAGE THROUGH THE FIFO DESCRIPTOR
     *
     * Suggestions:
     * - you can read from a FIFO as from a regular file descriptor
     * - since you don't know the length of the message, just
     *   read one byte at a time from the socket
     * - leave the cycle when 'separator' ('\n') is encountered
     * - repeat the read() when interrupted before reading any data
     * - return the number of bytes read
     * - reading 0 bytes means that the other process has closed
     *   the FIFO unexpectedly: this is an error that should be
     *   dealt with!
     **/
    int bytes_read = 0;
    do
    {
        ret = read(fd, buf + bytes_read, 1);
        if (ret == -1 && errno == EINTR)
            continue;
        if (ret == -1)
            handle_error("Cannot read from FIFO");
        if (ret == 0)
        {
            printf("%s\n", buf);
            fflush(stdout);
            handle_error("Process has closed the FIFO unexpectedly! Exiting...");
        }
        // we use post-increment on bytes_read so that we first read the
        // byte that has just been written, then we do the increment
        printf("Read %s \n", buf);

    } while (buf[bytes_read++] != separator);
    printf("Read %d bytes\n", bytes_read);
    fflush(stdout);
    return bytes_read;
}