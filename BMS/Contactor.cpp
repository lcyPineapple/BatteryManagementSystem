#include <stdlib.h>
#include <stdbool.h>
#include <Arduino.h>
#include "Contactor.h"

/******************************************************************
  * Function name: updateContactor
  * Function inputs: bool* contactorStatus, int* contactorLED,
  *                  volatile byte* hvilAlarm
  * Function outputs: void
  * Function description: updates the conctactor LED's value
  *                       based upon the contactor status (changes
  *                       the contactor signal into an output) 
  *                       Function is not preemptable. If the hvil is
  *                       open the contactor does not turn on. 
  * Author(s): Leika Yamada
  *****************************************************************/
void updateContactor ( bool* contactorStatus, bool* local, bool* ack, int* contactorLED, volatile byte* hvilAlarm, byte* voltAlarm, byte* currentAlarm) {
    // Need to acknowledge change if it was changed
    noInterrupts();                                                                                                     // Disable interrupts
    if(*ack == 1 && *hvilAlarm == NOT_ACTIVE){                                                                          // If the alarm has if off, set contactor to 1
          *contactorStatus = 1;
      }
    if( *contactorStatus != *local ){                                                                                   // update the local contactor state
        *local = *contactorStatus;
        //*ack = true; 
    }
    if( *contactorStatus == 1 && *hvilAlarm == NOT_ACTIVE && *voltAlarm == NOT_ACTIVE && *currentAlarm == NOT_ACTIVE ){                                                            // turn on the contactor if the hvil is not active
        
        digitalWrite(*contactorLED, HIGH);
    }
    else{                                                                                                               // in all other cases turn off the contactor
        digitalWrite(*contactorLED, LOW);
    }
    interrupts();                                                                                                       // enable interrupts
    return;
}

/*************************************************************************
  * Function name: contactorTask
  * Function inputs: void* contactData
  * Function outputs: void
  * Function description: Makes the contactorTask update all of it's data
  * Author(s): Leika Yamada
  ************************************************************************/
void contactorTask ( void* contactData ) {
  
    contactorData* data = (contactorData*) contactData;
    
    updateContactor(data->contactorStatus, data->localContactor, data->acknowledge, data->contactorLED, data->hvilAlarm, data->hVoltOutofRange, data->overCurrent);   // Update all sensors
    
    return;
}
