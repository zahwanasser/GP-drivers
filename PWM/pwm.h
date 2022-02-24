/*
* File name: pwm.h
*
* Created on Feb 18th, 2022
* Author: Bassant Ayman
* Description: Header file for Pulse Width Modulation module. Includes the header
* files for TM4C123GH6PM as well as configuration structures for more usability.
*
*/
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "std_types.h"


/***************************************************************************
                             Types decleration
****************************************************************************/

typedef enum{
  PWM0, PWM1
}PWM_MODULE;

typedef enum{
  PWM_GEN_0, PWM_GEN_1, PWM_GEN_2, PWM_GEN_3
}PWM_GEN_NUMBER;

typedef enum{

  PWM_PRESCALER_2, //Divide clock freq by 2
  PWM_PRESCALER_4, //Divide clock freq by 4
  PWM_PRESCALER_8, //Divide clock freq by 8
  PWM_PRESCALER_16, //Divide clock freq by 16
  PWM_PRESCALER_32, //Divide clock freq by 32 
  PWM_PRESCALER_64, //Divide clock freq by 64
  PWM_PRESCALER_64_1, //Divide clock freq by 64
  PWM_PRESCALER_64_2, //Divide clock freq by 64
  
  //Options 5, 6 and 7 give the same outputs as each other. It's a redundancy in
  //TivaC for some reason.
  
}PWM_PRESCALER;

typedef enum{
 PWM_PRESCALER_OFF, //Use system clock directly
 PWM_PRESCALER_ON //Use prescaler available
}PWM_PRESCALER_MODE;

typedef enum{

  pinA_off, pinA_on
}PWM_GEN_PINA;

typedef enum{
  pinB_off, pinB_on
}PWM_GEN_PINB;


typedef struct{
  
  PWM_GEN_NUMBER PWM_GEN_NUMBER; //To select which PWM Generator is being used
  PWM_PRESCALER_MODE PWM_PRE_MODE; //To select if the prescaler is used or not
  PWM_PRESCALER PWM_PRESCALER_VAL; //If the prescaler is on, we select its value
  PWM_GEN_PINA PWM_GEN_PINA_ON; //Enable output PINA
  PWM_GEN_PINB PWM_GEN_PINB_ON; //Enable output PINB
  uint16 PWM_LOAD; //PWMnLOAD register value
  uint16 PWM_COMPA; //PWMnCMPA value
  uint16 PWM_COMPB; //PWMnCMPB value
  
}PWM_CONFIG;



/******************************************************************************
                         FUNCTION PROTOTYPES
******************************************************************************/

void PWM0_INIT(const PWM_CONFIG* PWM_CONFIG); //PWM0 Initialization function
void PWM1_INIT(const PWM_CONFIG* PWM_CONFIG); //PWM1 Initialization function
void PWM_PRESCALER_INIT(uint16 PWM_PRESCALER_VAL); //PWM Prescaler Initialization function
void PWM0_OFF(); //Disable PWM0
void PWM1_OFF(); //Disable PWM1
