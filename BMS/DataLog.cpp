#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <pin_magic.h>
#include <registers.h>
#include <Arduino.h>
#include <EEPROM.h>
#include "DataLog.h"

/********************************************************************
  * Function name: eepromReset
  * Function inputs: void
  * Function outputs:void
  * Function description: Set EEPROM values to default. Voltage to -1,
  *                       current to 0, and temperature to 0.
  *                       voltage from location 
  * Author(s): Leika Yamada
  *******************************************************************/
void eepromReset () {
    //EEPROM.write(0, i);           // EEPROM write, address, int(0-255)
                                    // Sign: 0 is positive 1 is negative
    /*Temperature*/
    EEPROM.write(0, 0);             // MinTemp = 0: byte1 : sign, byte2: Whole part, byte3: fractional part (2 digits)
    EEPROM.write(1, 0);
    EEPROM.write(2, 0);
   /*Temperature*/
    EEPROM.write(3, 0);             // MaxTemp = 0: byte1 : sign, byte2: Whole part, byte3: fractional part (2 digits)
    EEPROM.write(4, 0);
    EEPROM.write(5, 0);
    /*Current*/
    EEPROM.write(6, 0);             // Min Current = 0: byte1 : sign, byte2: Whole part, byte3: fractional part (2 digits)
    EEPROM.write(7, 0);
    EEPROM.write(8, 0);
   /*Current*/
    EEPROM.write(9, 0);             // Max Current = 0: byte1 : sign, byte2: Whole part, byte3: fractional part (2 digits)
    EEPROM.write(10, 0);
    EEPROM.write(11, 0);
    /*Voltage*/
    EEPROM.write(12, 1);             // Min voltage = 0: byte1 : sign, byte2: Whole part(0 - 250), byte3:  Whole part(0 - 250), byte 4: fractional part (2 digits)
    EEPROM.write(13, 1);
    EEPROM.write(14, 0);
    EEPROM.write(15, 0);
    /*Voltage*/
    EEPROM.write(16, 1);             // Max voltage = 0: byte1 : sign, byte2: Whole part(0 - 250), byte3:  Whole part(0 - 250), byte 4: fractional part (2 digits)
    EEPROM.write(17, 1);
    EEPROM.write(18, 0);
    EEPROM.write(19, 0);
    
}
/********************************************************************
  * Function name: eepromCurrResetMin
  * Function inputs: minCurr
  * Function outputs:void
  * Function description: Set minimum current EEPROM values.
  * Author(s): Leika Yamada
  *******************************************************************/
void eepromCurrResetMin ( float* minCurr ) {
    //EEPROM.write(0, i);           // EEPROM write, address, int(0-255)
    int myCurr = (int) *minCurr * 100;
    int sign = 0;
    if(*minCurr < 0){
        sign = 1;
    }
    myCurr = abs(myCurr);
    int whole = myCurr / 100;
    int frac = myCurr % 100;
    
    /*Temperature*/
    EEPROM.write(6, sign);             // MinTemp = 0: byte1 : sign, byte2: Whole part, byte3: fractional part (2 digits)
    EEPROM.write(7, whole);
    EEPROM.write(8, frac);
}
/********************************************************************
  * Function name: eepromCurrResetMax
  * Function inputs: minCurr
  * Function outputs:void
  * Function description: Set maximum current EEPROM values.
  * Author(s): Leika Yamada
  *******************************************************************/
void eepromCurrResetMax ( float* maxCurr ) {
    //EEPROM.write(0, i);           // EEPROM write, address, int(0-255)
    int myCurr = (int) *maxCurr * 100;
    int sign = 0;
    if(*maxCurr < 0){
        sign = 1;
    }
    myCurr = abs(myCurr);
    int whole = myCurr / 100;
    int frac = myCurr % 100;
    
    /*Temperature*/
    EEPROM.write(9, sign);             // MinTemp = 0: byte1 : sign, byte2: Whole part, byte3: fractional part (2 digits)
    EEPROM.write(10, whole);
    EEPROM.write(11, frac);
}
/********************************************************************
  * Function name: eepromVoltResetMin
  * Function inputs: minVolt
  * Function outputs:void
  * Function description: Set minimum voltage EEPROM value. Using 4
  *                       bytes.
  * Author(s): Leika Yamada
  *******************************************************************/
void eepromVoltResetMin (float* minVolt) {
    //EEPROM.write(0, i);           // EEPROM write, address, int(0-255)
    int myVolt = (int) *minVolt * 100;
    int sign = 0;
    int whole = myVolt / 100;
    int whole2 = 0;
    if ( whole > 250 ){
        whole2 = whole - 250;
        whole = 250;
    }
    int frac = myVolt % 100;

    /*Voltage*/
    EEPROM.write(12, sign);             // Min voltage = 0: byte1 : sign, byte2: Whole part(0 - 250), byte3:  Whole part(0 - 250), byte 4: fractional part (2 digits)
    EEPROM.write(13, whole);
    EEPROM.write(14, whole2);
    EEPROM.write(15, frac);
    
}
/********************************************************************
  * Function name: eepromVoltResetMax
  * Function inputs: maxVolt
  * Function outputs:void
  * Function description: Set maximum voltage EEPROM value. Using 4
  *                       bytes.
  * Author(s): Leika Yamada
  *******************************************************************/
void eepromVoltResetMax (float* maxVolt) {
    //EEPROM.write(0, i);           // EEPROM write, address, int(0-255)
    int myVolt = (int) *maxVolt * 100;
    int sign = 0;
    int whole = myVolt / 100;
    int whole2 = 0;
    if ( whole > 250 ){
        whole2 = whole - 250;
        whole = 250;
    }
    int frac = myVolt % 100;

    /*Voltage*/
    EEPROM.write(16, sign);             // Min voltage = 0: byte1 : sign, byte2: Whole part(0 - 250), byte3:  Whole part(0 - 250), byte 4: fractional part (2 digits)
    EEPROM.write(17, whole);
    EEPROM.write(18, whole2);
    EEPROM.write(19, frac);
    
}
/********************************************************************
  * Function name: eepromTempResetMin
  * Function inputs: minTemp
  * Function outputs:void
  * Function description: Set minimum EEPROM temperature value. 
  * Author(s): Leika Yamada
  *******************************************************************/
void eepromTempResetMin ( float* minTemp) {
  
    int myTemp = (int) *minTemp * 100;
    int sign = 0;
    if(*minTemp < 0){
        sign = 1;
    }
    myTemp = abs(myTemp);
    int whole = myTemp / 100;
    int frac = myTemp % 100;
    
    /*Temperature*/
    EEPROM.write(0, sign);             // MinTemp = 0: byte1 : sign, byte2: Whole part, byte3: fractional part (2 digits)
    EEPROM.write(1, whole);
    EEPROM.write(2, frac);
}
/********************************************************************
  * Function name: eepromTempResetMax
  * Function inputs: void
  * Function outputs:void
  * Function description: Set max EEPROM temperature value. 
  * Author(s): Leika Yamada
  *******************************************************************/
void eepromTempResetMax ( float* maxTemp) {
  
    int myTemp = (int) *maxTemp * 100;
    int sign = 0;
    if(*maxTemp < 0){
        sign = 1;
    }
    myTemp = abs(myTemp);
    int whole = myTemp / 100;
    int frac = myTemp % 100;
    
    /*Temperature*/
    EEPROM.write(3, sign);             // MinTemp = 0: byte1 : sign, byte2: Whole part, byte3: fractional part (2 digits)
    EEPROM.write(4, whole);
    EEPROM.write(5, frac);
}
/********************************************************************
  * Function name: recoverMinMax
  * Function inputs: 
  * Function outputs:void
  * Function description: Set max EEPROM temperature value. 
  * Author(s): Leika Yamada
  *******************************************************************/
void  recoverMinMax(float* maxTemp, float* minTemp, float* minCurrent, float* maxCurrent, float* minVolt, float* maxVolt) {
    int sign = 0;
    int whole = 0;
    int whole2 = 0;
    int frac = 0;
    /*Temperature*/
    sign = (int) EEPROM.read(0);             // MinTemp = 0: byte1 : sign, byte2: Whole part, byte3: fractional part (2 digits)
    whole = (int) EEPROM.read(1);
    frac = (int) EEPROM.read(2);
    if (sign == 1){
    *minTemp = sign*(-1)*((whole*100 + frac)/100.0);
    } else{
    *minTemp = ((whole*100 + frac)/100.0);
    }
   /*Temperature*/
    sign = (int) EEPROM.read(3);             // MaxTemp = 0: byte1 : sign, byte2: Whole part, byte3: fractional part (2 digits)
    whole = (int) EEPROM.read(4);
    frac = (int) EEPROM.read(5);

    if (sign == 1){
    *maxTemp = sign*(-1)*((whole*100 + frac)/100.0);
    } else{
    *maxTemp = ((whole*100 + frac)/100.0);
    }
    /*Current*/
    sign = (int) EEPROM.read(6);             // MinCurr = 0: byte1 : sign, byte2: Whole part, byte3: fractional part (2 digits)
    whole = (int) EEPROM.read(7);
    frac = (int) EEPROM.read(8);

    if (sign == 1){
    *minCurrent = sign*(-1)*((whole*100 + frac)/100.0);
    } else{
    *minCurrent = ((whole*100 + frac)/100.0);
    }
   /*Current*/
    sign = (int) EEPROM.read(9);             // MinCurr = 0: byte1 : sign, byte2: Whole part, byte3: fractional part (2 digits)
    whole = (int) EEPROM.read(10);
    frac = (int) EEPROM.read(11);

    if (sign == 1){
    *maxCurrent = sign*(-1)*((whole*100 + frac)/100.0);
    } else{
    *maxCurrent = ((whole*100 + frac)/100.0);
    }
    /*Voltage*/
    sign = (int) EEPROM.read(12);             // Min voltage = 0: byte1 : sign, byte2: Whole part(0 - 250), byte3:  Whole part(0 - 250), byte 4: fractional part (2 digits)
    if (sign == 1){
        *minVolt = -1;
    }
    else{
    whole = (int) EEPROM.read(13);
    whole2 = (int) EEPROM.read(14);
    frac = (int) EEPROM.read(15);
    *minVolt = (((whole+whole2)*100 + frac)/100.0);
    }
    /*Voltage*/
    sign = (int) EEPROM.read(16);             // Max voltage = 0: byte1 : sign, byte2: Whole part(0 - 250), byte3:  Whole part(0 - 250), byte 4: fractional part (2 digits)
    if (sign == 1){
        *maxVolt = -1;
    }
    else{
    whole = (int) EEPROM.read(17);
    whole2 = (int) EEPROM.read(18);
    frac = (int) EEPROM.read(19);
    *maxVolt = (((whole+whole2)*100 + frac)/100.0);
    }
}
/**********************************************************************
  *  Function name: terminalTask
  *  Function inputs: void* tData
  *  Function outputs: void
  *  Function description: Prompts user to choose between 4 options, 
  *                        if option 1 is selected the EEPROM reset 
  *                        flag is raised. If option 2 is selected 
  *                        the historical min/max current is displayed, 
  *                        if 3 is slected min/max voltage, if 4 is 
  *                        selected min/max temperature.
  *  Author(s): Leika Yamada
  *********************************************************************/
void dataLogTask ( void* dData ) {
     logData* data = ( logData* ) dData;
      if(*(data->recover) == true){                      
          *(data->recover) = false;
          recoverMinMax(data->maxTemp, data->minTemp, data->minCurrent, data->maxCurrent, data->minVolt, data->maxVolt);
      }
     if(*(data->EEPROMReset) == true){                      
          *(data->EEPROMReset) = false;
          eepromReset();
      }else{
          if (*(data->tempChangemin) == true){
              *(data->tempChangemin) = false;
                eepromTempResetMin(data->minTemp);
            }
          if (*(data->tempChangemax) == true){
              *(data->tempChangemax) = false;
                eepromTempResetMax(data->maxTemp);
            }
          if (*(data->voltChangemin) == true){
              *(data->voltChangemin) = false;
                eepromVoltResetMin(data->minVolt);
            }
          if (*(data->voltChangemax) == true){
              *(data->voltChangemax) = false;
                eepromVoltResetMax(data->maxVolt);
            }
          if (*(data->currChangemin) == true){
              *(data->currChangemin) = false;
                eepromCurrResetMin(data->minCurrent);
            }
          if (*(data->currChangemax) == true){
              *(data->currChangemax) = false;
                eepromCurrResetMax(data->maxCurrent);
            }   
      }
    return;
}
