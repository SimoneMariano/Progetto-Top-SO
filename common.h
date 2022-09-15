#pragma once
#define handle_error(msg) {perror(msg); exit(EXIT_FAILURE);}
#define SHM_NAME "memo"
#define SHM_SIZE sizeof(int)



