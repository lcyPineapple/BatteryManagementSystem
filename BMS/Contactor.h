#ifdef __cplusplus                    // Tells compiler the file is .c
extern "C" { 
#endif 

#ifndef CONTACTOR_H_
#define CONTACTOR_H_


#include <stdlib.h>
#include <stdbool.h>
#include <Arduino.h>


#define NOT_ACTIVE      0


typedef struct contactorTaskData {  // Structure that holds contactor data
    bool* contactorStatus;          // Contactor: 1 closed, 0 open
    bool* localContactor;           // holds a local version of the contactor that no other task modifies to check if the contactor Status was update
    bool* acknowledge;              // if it was acknowledged it should flip the acknowledge flag to true, which will then be turned off by the display when
                                    //  it notices that the acknowledge flag is true;
    byte* hVoltOutofRange;          // and 2 for active acknowledged
    byte* overCurrent;              // 0 for alarm not active, 1, for active not acknowledged  
    int* contactorLED;              // Output pin number
    volatile byte* hvilAlarm;       // hvil alarm status
} contactorData;


void contactorTask (void*);         // Update contactor status


#endif

#ifdef __cplusplus 
} 
#endif 
