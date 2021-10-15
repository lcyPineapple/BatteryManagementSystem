#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "Alarm.h"
#include "Arduino.h"

/*****************************************************************
  * Function name: updateHVoltInterlockAlrm
  * Function inputs: byte* hVoltInterlock
  * Function outputs: void
  * Function description: changes the HVInterlock pointer's value
  *                       depending on the hvil status changed by
  *                       the interrupt. If the dipswitch is closed
  *                       switches to not active.
  * Author(s): Leonard Shin; Leika Yamada
  *****************************************************************/
void updateHVoltInterlockAlarm ( volatile byte* hVoltInterlock, bool* acknowledgeFlag, bool* hVIL ) {
    if( *hVIL == 0 && *hVoltInterlock == ACTIVE_ACK ){                                                                                       // If the switch is clsoed set alarm to not active
        *hVoltInterlock = NOT_ACTIVE;
    }
    
    if(*acknowledgeFlag == 1 && *hVoltInterlock == ACTIVE_NO_ACK ){                                         // If switch is open and the alarm is not acknowledged
          *hVoltInterlock = ACTIVE_ACK;                                                                     // Acknowledge the alarm and reset the flag
          *acknowledgeFlag = 0;
    }
    return;
    
}

/**********************************************************************
  * Function name: updateHVoltInterlockAlrm
  * Function inputs: byte* OverCurrent
  * Function outputs: void
  * Function description: changes the OverCurrent's pointer's value
  *                       to change state based on if the current is 
  *                       in a dangerous range. Range values are compared
  *                       against the potentiometer.
  * Author(s): Leonard Shin; Leika Yamada
  *********************************************************************/
void updateOverCurrent (float* curr, byte* overCurrent, bool* acknowledgeFlag ) {

    float curr_limit_l = -5;                                                          // Set the limits for the current alarm
    float curr_limit_r = 20;
    if(*acknowledgeFlag == 1 && (*overCurrent == ACTIVE_NO_ACK)){                     // If the alarm is acknowledged, acknowledge it
        *overCurrent = ACTIVE_ACK;
    }
    else if((*curr < curr_limit_l || *curr > curr_limit_r))                           // Activate the alarm if the potentiometer is inside the danger range
    {
        if(*overCurrent == ACTIVE_ACK)
        {
            *overCurrent = ACTIVE_ACK;
        }
        else
        {
            *overCurrent = ACTIVE_NO_ACK;
        }
    }
    else                                                                              // If the current is not in a dangerous range deactivate the alarm
    {
        *overCurrent = NOT_ACTIVE;
    }
    return;
    
}

/************************************************************************
  * Function name: updateHVoltOutofRange
  * Function inputs: byte* HVoltOutofRange
  * Function outputs: void
  * Function description: Changes the HVoltOutofRange pointer's value
  *                       to change state based on if the voltage is 
  *                       in a dangerous range. Range values are compared
  *                       against the potentiometer.
  * Author(s): Leonard Shin; Leika Yamada
  **********************************************************************/
void updateHVoltOutofRange (float* volt, byte* hVoltOutofRange, bool* acknowledgeFlag ) {
    
    float volt_limit_l = 280;                                                               // Set the range of dangerous voltage values
    float volt_limit_r = 405;
    if(*acknowledgeFlag == 1 && (*hVoltOutofRange == ACTIVE_NO_ACK)){                       // If an alarm has not been acknowledged, acknowledge it
        *hVoltOutofRange = ACTIVE_ACK;
    }
    else if((*volt < volt_limit_l || *volt > volt_limit_r))                                 // If the voltage is in dangerous range set the alarm
    {
        if(*hVoltOutofRange == ACTIVE_ACK)
        {
            *hVoltOutofRange = ACTIVE_ACK;
        }
        else
        {
            *hVoltOutofRange = ACTIVE_NO_ACK;
        }
    }
    else                                                                                    // If the voltage is in a safe range, deactivate alarm
    {
        *hVoltOutofRange = NOT_ACTIVE;
    }
    return;
    
}

/*****************************************************************
  * Function name: alarmTask
  * Function inputs: void* mData
  * Function outputs: void
  * Function description: Modifies mData to represent
  *                       the Alarm data at the current time point
  * Author(s): Leonard Shin; Leika Yamada
  ****************************************************************/
void alarmTask ( void* mData ) {
    
    alarmData* data = (alarmData*) mData;
    
    /* Update all sensors */
    updateHVoltInterlockAlarm(data->hVoltInterlock, data->acknowledgeFlag, data->hVIL);
    updateOverCurrent(data->current, data->overCurrent, data->acknowledgeFlag);
    updateHVoltOutofRange(data->voltage, data->hVoltOutofRange, data->acknowledgeFlag);
    
    return;
}
