#include <stdlib.h>
#include <stdbool.h>
#include "StateOfCharge.h"
#include "Arduino.h"

int volt_length = 5;
int voltages_soc[] = {200, 250, 300, 350, 400};   // columns
int temp_length = 4;
int temperatures_soc[] = {-10, 0, 25, 45};        // rows
int percent_soc[4][5] = {
                   {  0,  0,  35, 100, 100},
                   {  0,  0,  20,  80, 100},
                   {  0,  0,  10,  60, 100},
                   {  0,  0,   0,  50, 100}
                  };

/********************************************************************
  * Function name: computeSoc
  * Function inputs: float pointers to the voltage, currrent, and measured temp
  * Function outputs: the state of charge
  * Function description: Interpolates using the percent_soc table 
  *                       to project what the current soc is given the 
  *                       temp, current, and voltage
  * Author(s): Leonard Shin
  *******************************************************************/
float computeSoc(float* volt, float* current, float* temp)
{
    float resistance = 0.5;
    float open_cVolt = *volt + resistance * *current; 
    int left_v = -1; //hold the index of the largest v less than volt
    int right_v = -1; //hold the index of the smallest v larger than volt
    int lower_temp = -1; //hold the index of the smallest t larger than temp
    int upper_temp = -1; //hold the index of the largest t smaller than temp

    for(int i = 0; i < volt_length; i++)
    {
        if(open_cVolt < voltages_soc[i])
        {
            if (i == 0)
            {
                return 0;
            }
            else if(right_v == -1)
            {
                right_v = i;
            }
        }
        if(open_cVolt > voltages_soc[i])
        {
            if (i == volt_length - 1)
            {
                return 100;
            }
            else
            {
                left_v = i;
            }
        }
    }

    for(int i = 0; i < temp_length; i++)
    {
        if(*temp < temperatures_soc[i])
        {
            if (i == 0)
            {
                return -1; //temp is below -10
            }
            else if(upper_temp == -1)
            {
                upper_temp = i;
            }
        }
        else if(*temp > temperatures_soc[i])
        {
            if (i == temp_length - 1)
            {
                return -2;   //temp is above 45
            }
            else
            {
                lower_temp = i;
            }
        }
    }
    //interpolation at upper temp w respect to voltage
    float voltage_ratio = (open_cVolt - voltages_soc[left_v])/(voltages_soc[right_v]-voltages_soc[left_v]);
    float inter_upper = voltage_ratio *
                        (percent_soc[lower_temp][right_v] - percent_soc[lower_temp][left_v])
                         + percent_soc[lower_temp][left_v];
    //interpolation at lower temp w respect to voltage
    float inter_lower = voltage_ratio *
                        (percent_soc[upper_temp][right_v] - percent_soc[upper_temp][left_v]) 
                         + percent_soc[upper_temp][left_v];
    
    //interpolate with respect to temperature
    float temp_ratio = (*temp - temperatures_soc[lower_temp])/(temperatures_soc[upper_temp] - temperatures_soc[lower_temp]);
    float soc = inter_upper - temp_ratio*(inter_upper - inter_lower);
    return soc;
}
/************************************************************************
  * Function name: stateOfChargeTask
  * Function inputs: generic pointer to the updated state of charge data
  * Function outputs: ~
  * Function description: update state of charge using bi-linear interpolation
  * Author(s): Leonard Shin, Leika Yamada
  **********************************************************************/
void stateOfChargeTask ( void* socData ) {
  
    stateOfChargeData* data = (stateOfChargeData*) socData;
    *data->soc = computeSoc(data->vTerminal, data->iTerminal, data->temp);
  return;
}
