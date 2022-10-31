#pragma once
#include <stdio.h>
#include <dirent.h>
#include "linked_list.h"

int isNumber(char *str);
int getTotalMemory(FILE *fileMemInfo);
void getUsedMemory(struct dirent *pDsCopy, int totMem, struct_process* s_process);
float getTotalCpu(FILE *fileCpuInfo);
void getUsedCpu(struct dirent *pDsCopy, int cpuTot, struct_process* s_process);
int getPidandName(struct dirent *pDsCopy, struct_process* s_process);
void handle_error(char* msg);
int string_to_int(char* dest, int src);
