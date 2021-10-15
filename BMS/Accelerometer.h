#ifdef __cplusplus                    // Tells compiler the file is .c
extern "C" { 
#endif 

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_


#include <stdlib.h>
#include <stdbool.h>
#include <Arduino.h>


typedef struct accelerometerTaskData {  // Structure that holds contactor data
    float* relX;                 // Relative positon, X-axis
    float* relY;                 // Relative positon, Y-axis
    float* relZ;                 // Relative positon, Z-axis
    float* totalDist;            // Total distance traveled
    float* angleX;               // Static angle of X
    float* angleY;               // Static angle of Y
    float* angleZ;               // Static angle of Z
    byte* xPin;                  // X axis input pin
    byte* yPin;                  // Y axis input pin
    byte* zPin;                  // Z axis input pin
    float* xadj;                 // Calibration Values for x
    float* yadj;                 // Calibration Values for y
    float* zadj;                 // Calibration Value for z
} accelerometerData;


void accelerometerTask (void*);         // Update contactor status


#endif

#ifdef __cplusplus 
} 
#endif 
