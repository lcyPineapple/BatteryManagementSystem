#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <pin_magic.h>
#include <registers.h>
#include <Arduino.h>
#include "RemoteTerminal.h"

/********************************************************************
  * Function name: terminalPrompt
  * Function inputs: void
  * Function outputs: int The users choice (1 - 4)
  * Function description: Prompts user to choose between 4 options the 
  *                       chosen option is returned by the funciton.
  * Author(s): Leonard Shin; Leika Yamada
  *******************************************************************/
int terminalPrompt () {
    int choice = 0;                                         // variable to save user input in
    Serial.println("[1] Reset EEPROM");                     // Display Prompt
    Serial.println("[2] HV Current Range [Hi, Lo]");
    Serial.println("[3] HV Voltage Range [Hi, Lo]");
    Serial.println("[4] Temperature Range [Hi, Lo]");
    Serial.println("Enter your menu choice [1-4]:");
    Serial.println();
    //while (Serial.available() == 0) {                       // Wait for user input
        // Wait for User to Input Data
    //}
    Serial.setTimeout(20);     
    choice = Serial.parseInt();                             // Collect serial input
    if(choice > 4 || choice < 1){
        choice = 0;
        Serial.println("Invalid Input");
        Serial.println();  
    }
    return choice; 
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
  *  Author(s): Leonard Shin; Leika Yamada
  *********************************************************************/
void terminalTask ( void* tData ) {
  
    terminalData* data = ( terminalData* ) tData;

    int userChoice = terminalPrompt();
    if ( 1 == userChoice ){
        *(data->EEPROMReset) = true;
        Serial.println("EEPROM has been reset");
        Serial.println();
    }else if ( 2 == userChoice ){
        Serial.print("Max Current is ");
        Serial.println(*(data->maxCurrent));
        Serial.print("Min Current is ");
        Serial.println(*(data->minCurrent));
        Serial.println();
    }else if ( 3 == userChoice ){
        Serial.print("Max Voltage is ");
        Serial.println(*(data->maxVolt));
        Serial.print("Min Voltage is ");
        Serial.println(*(data->minVolt));
        Serial.println();
    }else if( 4 == userChoice ){
        Serial.print("Max Temperature is ");
        Serial.println(*(data->maxTemp));
        Serial.print("Min Temperature is ");
        Serial.println(*(data->minTemp));
        Serial.println();
    }
    
    return;
}
