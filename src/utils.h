#pragma once
#include <stdio.h>
#include <dirent.h>
#include "process_list.h"

typedef struct{
	ListItem list;
	char name[256];
	int pid;
    int cpu_usage;
	int memory_usage;
    char state[256];
}struct_process;

int isNumber(char *str);
int getTotalMemory(FILE *fileMemInfo);
void getUsedMemory(struct dirent *pDsCopy, int totMem);
float getTotalCpu(FILE *fileCpuInfo);
void getUsedCpu(struct dirent *pDsCopy, int cpuTot);
int getPidandName(struct dirent *pDsCopy, struct_process* s_process);
void handle_error(char* msg);
int string_to_int(char* dest, int src);