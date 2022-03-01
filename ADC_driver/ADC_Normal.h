/*
 * ADC_Normal.h
 *
 *  Created on: Feb 24, 2022
 *      Author: Mena Emiel
 */

#ifndef ADC_Normal_H_
#define ADC_Normal_H_
#include "std_types.h"
#include "tm4c123gh6pm.h"
#include <stdlib.h>
#include <stdint.h>

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
  ss0, ss1, ss2, ss3
}SampleSequencer_Number;

typedef enum{
  PROCESSOR=0, COMP0=1, COMP1=2, EXTERNAL=4, TIMER=5, PWM0=6, PWM1=7, PWM2=8, PWM3=9, ALWAYS=10
}Trigger_Mode;

typedef enum{
  PWM0_module, PWM1_module
}PWM_module_number;

typedef enum{
  disable, enable
}ADC_interrupts;

typedef enum{
  bit0INT, bit1INT, bit2INT, bit3INT, bit4INT, bit5INT, bit6INT, bit7INT
}Interrupt_bit_number;

typedef enum{
  bit0EOS, bit1EOS, bit2EOS, bit3EOS, bit4EOS, bit5EOS, bit6EOS, bit7EOS
}EndOfSequence_bit_number;

typedef enum{

AIN0, AIN1, AIN2, AIN3, AIN4, AIN5, AIN6, AIN7, AIN8, AIN9, AIN10, AIN11
}input;

typedef enum{

 PRI_0, PRI_1, PRI_2, PRI_3
}PRI;

typedef struct{
    SampleSequencer_Number SSC_No;
    Trigger_Mode Trigger;
    PWM_module_number PWM_module;
    ADC_interrupts int_status;
    Interrupt_bit_number interrupt_bit_no;
    EndOfSequence_bit_number EOS_bit_no;
}ADC_NormalModeStruct;

typedef struct{

  input ADC_INPUT;
  PRI SSPRI_0; //Priority of Sample Sequencer 0
  PRI SSPRI_1; //Priority of Sample Sequencer 1
  PRI SSPRI_2; //Priority of Sample Sequencer 2
  PRI SSPRI_3; //Priority of Sample Sequencer 3
 
}ADC_CONFIG;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void ADC_NormalMode(ADC_NormalModeStruct* ADC_NormalModePtr);
void ADC_INIT(const ADC_CONFIG* ADC_CONFIG); //ADC Initialization function


#endif /* ADC_Normal_H_ */
