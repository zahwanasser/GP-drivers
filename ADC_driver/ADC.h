#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "std_types.h"


/**************************************CONFIG STRUCT**************************
****************************************************************************/

typedef enum{

AIN0, AIN1, AIN2, AIN3, AIN4, AIN5, AIN6, AIN7, AIN8, AIN9, AIN10, AIN11
}input;

typedef enum{

 PRI_0, PRI_1, PRI_2, PRI_3
}PRI;

/*typedef enum{
  ON, OFF
}MODULE_STATE;*/

/*typedef enum{

  PROCESSOR, //0x00->Default
  ANALOG_COMP_0, //0x01 Analog comparator 0
  ANALOG_COMP_1, //0x02 Analog comparator 1
  RESERVED_0, //0x03 Reserved, gives error
  EXTERNAL_GPIO, //0x04 External GPIO as configured in ADC_INIT
  TIMER, //0x05 Timer
  PWM_0, //0x06 PWM0
  PWM_1, //0x07 PWM1
  PWM_2, //0x08 PWM2
  PWM_3, //0x09 PWM3
  RESERVED_1, //0x0A Reserved
  RESERVED_2, //0x0B Reserved 
  RESERVED_3, //0x0C Reserved
  RESERVED_4, //0x0D Reserved
  RESERVED_5, //0x0E Reserved
  ALWAYS, //0X0F Always (Continously Sampled)
}TRIG_SRC;*/

/*typedef enum{
INVERSION_0FF, INVERSION_ON,
}INVERSION;*/

/*typedef enum{
  LOW, HIGH
}MODULE_LEVEL;*/

/*typedef enum{

LEVEL_SENSE, FALLING_EDGE, RISING_EDGE, EITHER_EDGE,
}SEN;*/


typedef struct{

  input ADC_INPUT;
  PRI SSPRI_0; //Priority of Sample Sequencer 0
  PRI SSPRI_1; //Priority of Sample Sequencer 1
  PRI SSPRI_2; //Priority of Sample Sequencer 2
  PRI SSPRI_3; //Priority of Sample Sequencer 3
 
}ADC_CONFIG;

/*typedef struct{

  MODULE_STATE SS0_ON; //Using SS0;
  MODULE_STATE SS1_ON; //Using SS1;
  MODULE_STATE SS2_ON; //Using SS2;
  MODULE_STATE SS3_ON; //Using SS3;
  TRIG_SRC SS_TRIG_SRC; //Sample Sequencer Trigger source
  MODULE_STATE SS_INVERSION; //Comparator Output Invert (ACCTL)
  SEN SS_ISEN; //Interrupt Sense (ACCTL)
  SEN SS_TSEN; //Trigger Sense (ACCTL)
  MODULE_STATE ISLVAL; //Interrupt Sense Level Value(ACCTL)
  
  
  
}SS_CONFIG*/


/****************************FUNCTION PROTOTYPES*******************************
******************************************************************************/


void ADC_INIT(const ADC_CONFIG* ADC_CONFIG); //ADC Initialization function
//void ADC_SS_CONFIG(const SS_CONFIG* SS_CONFIG); //Sample Sequencer Configuration function


