#pragma once
#include <stdio.h>
#include <dirent.h>

int isNumber(char *str);
int getTotalMemory(FILE *fileMemInfo);
void getUsedMemory(struct dirent *pDsCopy, int totMem);
float getTotalCpu(FILE *fileCpuInfo);
void getUsedCpu(struct dirent *pDsCopy, int cpuTot);
int getPidandName(struct dirent *pDsCopy);
void handle_error(char* msg);
int string_to_int(char* dest, int src);