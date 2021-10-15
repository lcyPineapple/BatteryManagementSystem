#include <stdlib.h>
#include <stdbool.h>
#include <Arduino.h>
#include "Accelerometer.h"

float inVolt = 5;
float analogHigh = 1023;
float oneG = 1.65;              // According to Accelerometer spec sheet a voltage of 1.65 is read at 1g.
float sensitivity = 0.800;      // According to spec sheet typical sensitivity = 0.800V/g
float avgXAcc;                  // Avg. accerlation on x axis
float avgYAcc;                  // Avg. accerlation on y axis
float avgZAcc;                  // Avg. accerlation on z axis
float interval = 0.1;           // Time interval over which to integrate
float g = 9.81;                 // Acceleration due to gravity
float toCM = 100;               // Meters to cm conversion
  

/*************************************************************************
  * Function name: displacement
  * Function inputs: float* acceleration
  * Function outputs: float disp
  * Function description: Calculates position from accerlation via definite
  *                       double integral with respect to time. In this case
  *                       we use the global time base preset interval from 
  *                       0 - .5s so the integral is reduced to below.
  * Author(s): Leonard Shin, Leika Yamada
  ************************************************************************/
float displacement(float* accel){
    
    float disp = *accel * g * (toCM) * (pow(interval, 2));                           // Calculate displacement from accerlation via reduced double integral
    return disp;
}
/*************************************************************************
  * Function name: distance
  * Function inputs: float* dx, float* dt
  * Function outputs: float dist
  * Function description: Calculates the euclidean distance from 2d axis 
  *                       displacement.
  * Author(s): Leonard Shin, Leika Yamada
  ************************************************************************/
float distance(float* dx, float* dy){
    
    float dist = sqrt(pow(*dx, 2) + pow(*dy, 2));                                   // Calculate euclidean distance
    return dist;
}
/*************************************************************************
  * Function name: acceleration
  * Function inputs: byte* pin, float* adjust
  * Function outputs: float accel
  * Function description: Calculates the accerlation using the accelerometer
  *                       measurement.
  * Author(s): Leonard Shin, Leika Yamada
  ************************************************************************/
float acceleration(byte* pin, float* adjust){
     float myVolt = (((float)analogRead(*pin) * inVolt)/analogHigh)+ *adjust;       // Calculate the voltage input from analog input
     float accel = (myVolt - oneG)/sensitivity;                                     // Calculate acceleration from change in voltage and sensitivity
     return accel;
}
/*************************************************************************
  * Function name: angle
  * Function inputs: float* target
  * Function outputs: void
  * Function description: Calculates static angle of the target axis.
  * Author(s): Leonard Shin, Leika Yamada
  ************************************************************************/
float angle(float* target){
    double accMag = sqrt(pow(avgXAcc,2) + pow(avgYAcc,2) + pow(avgZAcc,2));         // Calculate the magnatude of the acceleration
    float targetVal = *target; 
    double myAngle = acos(((targetVal)/accMag))* 180.0/PI;                          // Calculate static angle from axis acceleration vector, and acceleration magnatude
    return (float) myAngle;
}
/*************************************************************************
  * Function name: accelerometerTask
  * Function inputs: void* accelerometerData
  * Function outputs: void
  * Function description: Calculates static angle, total distance traveled
  *                       and relative position.
  * Author(s): Leonard Shin, Leika Yamada
  ************************************************************************/
void accelerometerTask ( void* accelData ) {  

    accelerometerData* data = (accelerometerData*) accelData;
  
    float xArr[200];                                              // Initialize buffer for x axis
    float yArr[200];                                              // Initialize buffer for y axis
    float zArr[200];                                              // Initialize buffer for z axis
    for(int i = 0; i < 200; i++){
      xArr[i] = acceleration(data->xPin, data->xadj);                  // Take 200 samples to calculate static angle
      yArr[i] = acceleration(data->yPin, data->yadj);
      zArr[i] = acceleration(data->zPin, data->zadj);  
    }
    avgXAcc = 0;
    avgYAcc = 0;
    avgZAcc = 0;
    
    for(int i = 0; i < 200; i++){                                 // Find average accerations
      avgXAcc = xArr[i] + avgXAcc;
      avgYAcc = yArr[i] + avgYAcc;
      avgZAcc = zArr[i] + avgZAcc;
    }
    avgXAcc = avgXAcc/200;
    avgYAcc = avgYAcc/200;
    avgZAcc = avgZAcc/200;
    
    *data->angleX = angle(&avgXAcc);                               // Calculate static angle and store in global var
    *data->angleY = angle(&avgYAcc);
    *data->angleZ = angle(&avgZAcc);

    float myX = displacement(&avgXAcc);                 // Relative positon, X-axis
    float myY = displacement(&avgYAcc);                 // Relative positon, Y-axis
    float myZ = displacement(&avgZAcc);                 // Relative positon, Z-axis

    *data->totalDist = *data->totalDist + distance(&myX, &myY);
    
    *data->relX = *data->relX + myX;                 // Relative positon, X-axis
    *data->relY = *data->relY + myY;                 // Relative positon, Y-axis
    *data->relZ = *data->relZ + myZ;                 // Relative positon, Z-axis
    return;
}
