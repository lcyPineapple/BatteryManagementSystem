#ifdef __cplusplus  
extern "C" { 
#endif 

#ifndef DATALOG_H_
#define DATALOG_H_


#include <stdlib.h>
#include <stdbool.h>
#include <Arduino.h>



typedef struct dataTaskData {      // Contains Terminal Data
    float* minTemp;
    float* maxTemp;
    float* minCurrent;
    float* maxCurrent;
    float* minVolt;
    float* maxVolt;
    bool* EEPROMReset;
    bool* tempChangemin;        // Flag to check if the min or max temperature has changed
    bool* voltChangemin;        // Flag to check if the min or max voltage has changed
    bool* currChangemin;        // Flag to check if the min or max current has changed
    bool* tempChangemax;        // Flag to check if the max temperature has changed
    bool* voltChangemax;        // Flag to check if the max voltage has changed
    bool* currChangemax;        // Flag to check if the max current has changed
    bool* recover;              // Recover values after shutdown
} logData;


void dataLogTask (void*);


#endif

#ifdef __cplusplus 
} 
#endif 
