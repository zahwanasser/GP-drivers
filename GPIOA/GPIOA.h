/*
 * GPIOA.h
 *
 *  Created on: Feb 18, 2022
 *      Author: D
 */

#ifndef GPIOA_H_
#define GPIOA_H_
#include "std_types.h"
#include "tm4c123gh6pm.h"
#include <stdlib.h>
#include <stdint.h>
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
    PIN0,PIN1,PIN2,PIN3,PIN4,PIN5,PIN6,PIN7
}GPIOA_pinNumber;
typedef enum{
    two,four,eight
}GPIOA_ouputDriveStrength; //i think the default is 2ma
typedef enum{
    pullup,pulldown,opendrain
}GPIOA_ouputconfiguration;
typedef struct{
    GPIOA_pinNumber pin;
    GPIOA_ouputDriveStrength currentStrength;
    GPIOA_ouputconfiguration outputConfig;
}GPIOA_outputInitStruct;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void GPIOA_enableInput(GPIOA_pinNumber pin);
uint8_t GPIOA_readInputPinValue (GPIOA_pinNumber pin);
void GPIOA_enableOutput(GPIOA_outputInitStruct* GPIOA_outputInitPtr);
void GPIOA_writeOutputPinValue (GPIOA_pinNumber pin, uint8_t value);



#endif /* GPIOA_H_ */
