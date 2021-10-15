#ifdef __cplusplus  
extern "C" { 
#endif 

#ifndef STATEOFCHARGE_H_
#define STATEOFCHARGE_H_


#include <stdlib.h>
#include <stdbool.h>
#include <Arduino.h>


typedef struct stateOfChargeTaskData {      // Defines a data struct to hold the SOC
  
    float* vTerminal;
    float* iTerminal;
    float* temp;
    float* soc;
    
} stateOfChargeData;


void stateOfChargeTask (void*);


#endif

#ifdef __cplusplus 
} 
#endif 
