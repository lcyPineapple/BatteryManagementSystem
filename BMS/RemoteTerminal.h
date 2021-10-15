#ifdef __cplusplus  
extern "C" { 
#endif 

#ifndef REMOTETERMINAL_H_
#define REMOTETERMINAL_H_


#include <stdlib.h>
#include <stdbool.h>
#include <Arduino.h>


typedef struct terminalTaskData {      // Contains Terminal Data
    float* minTemp;
    float* maxTemp;
    float* minCurrent;
    float* maxCurrent;
    float* minVolt;
    float* maxVolt;
    bool* EEPROMReset;
} terminalData;


void terminalTask (void*);


#endif

#ifdef __cplusplus 
} 
#endif 
