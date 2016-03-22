
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "cpu_usage.h"


unsigned long long cpu_usage::lastTotalUser = 0;
unsigned long long cpu_usage::lastTotalUserLow = 0;
unsigned long long cpu_usage::lastTotalSys = 0;
unsigned long long cpu_usage::lastTotalIdle = 0;

void cpu_usage::init(){
    FILE* file = fopen("/proc/stat", "r");
    fscanf(file, "cpu %llu %llu %llu %llu",
           &cpu_usage::lastTotalUser,
           &cpu_usage::lastTotalUserLow,
           &cpu_usage::lastTotalSys,
           &cpu_usage::lastTotalIdle);
    fclose(file);
}

double cpu_usage::getCurrentValue(){
    double percent;
    FILE* file;
    unsigned long long totalUser, totalUserLow, totalSys, totalIdle, total;


    file = fopen("/proc/stat", "r");
    fscanf(file, "cpu %llu %llu %llu %llu", &totalUser, &totalUserLow,&totalSys, &totalIdle);
    fclose(file);

    if (totalUser < cpu_usage::lastTotalUser || totalUserLow < cpu_usage::lastTotalUserLow ||
            totalSys < cpu_usage::lastTotalSys || totalIdle < cpu_usage::lastTotalIdle){
        percent = -1.0;
    }else{
        total = (totalUser - cpu_usage::lastTotalUser) + (totalUserLow - cpu_usage::lastTotalUserLow) +(totalSys - cpu_usage::lastTotalSys);
        percent = total;
        total += (totalIdle - cpu_usage::lastTotalIdle);
        percent /= total;
        percent *= 100;
    }

    cpu_usage::lastTotalUser = totalUser;
    cpu_usage::lastTotalUserLow = totalUserLow;
    cpu_usage::lastTotalSys = totalSys;
    cpu_usage::lastTotalIdle = totalIdle;
    return percent;
}
