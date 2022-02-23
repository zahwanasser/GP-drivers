/*
 * GPIOA.c
 *
 *  Created on: Feb 18, 2022
 *      Author: D
 */
#include "GPIOA.h"
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 */
/*
 * Description : Function to enable a pin as input in portA

 *  Arguments: pin number
 *  Returns: void
 *  steps:
 *  1- enable the clk for the port
 *  2- for pins 0:5 clear the AFSEL and PCTL bits
 *  3- set as digital pin
 *  4- set direction
 */

void GPIOA_enableInput(GPIOA_pinNumber pin)
{
    SYSCTL_RCGCGPIO_R |=SYSCTL_RCGCGPIO_R0; //enabling clk for the port
    if (pin <= 5)   //clearing the default values for these pins
    {
        GPIO_PORTA_AFSEL_R &= ~(pin);
        GPIO_PORTA_PCTL_R  &= ~(pin);
    }
    GPIO_PORTA_DEN_R |= 1<<pin; //setting the pin as digital input
    GPIO_PORTA_DIR_R &= ~(1<<pin); // clearing the bit indicates input


}
/*
 * Description : Function to read the value on a pin

 *  Arguments: pin number
 *  Returns: value on pin
 *
 */
uint8_t GPIOA_readInputPinValue (GPIOA_pinNumber pin)
{
    return (GPIO_PORTA_DATA_R & (1<<pin)); //return the value on the pin

}
/*
 */
/*
 * Description : Function to enable a pin as output in portA

 *  Arguments: pin number
 *  Returns: void
 *  steps:
 *  1- enable the clk for the port
 *  2- for pins 0:5 clear the AFSEL and PCTL bits
 *  3- set as digital pin
 *  4- set direction
 *  5- choose the output current strength
 *  6- choose the
 */
void GPIOA_enableOutput(GPIOA_outputInitStruct* GPIOA_outputInitPtr)
{
    SYSCTL_RCGCGPIO_R |=SYSCTL_RCGCGPIO_R0; //enabling clk for the port
        if (GPIOA_outputInitPtr->pin <= 5)   //clearing the default values for these pins
        {
            GPIO_PORTA_AFSEL_R &= ~(GPIOA_outputInitPtr->pin);
            GPIO_PORTA_PCTL_R  &= ~(GPIOA_outputInitPtr->pin);
        }
        GPIO_PORTA_DEN_R |= 1<<(GPIOA_outputInitPtr->pin); //setting the pin as digital input
        GPIO_PORTA_DIR_R |= (1<<(GPIOA_outputInitPtr->pin)); // setting the bit indicates input
        if (GPIOA_outputInitPtr->currentStrength == 0)
        {
            GPIO_PORTA_DR2R_R |=1<<(GPIOA_outputInitPtr->pin);
        }
        else if (GPIOA_outputInitPtr->currentStrength == 1)
        {
            GPIO_PORTA_DR4R_R |=1<<(GPIOA_outputInitPtr->pin);
        }
        else if (GPIOA_outputInitPtr->currentStrength == 2)
        {
            GPIO_PORTA_DR8R_R |=1<<(GPIOA_outputInitPtr->pin);
        }
        if (GPIOA_outputInitPtr->outputConfig ==0)
        {
            GPIO_PORTA_PUR_R  |= 1<<(GPIOA_outputInitPtr->pin);
        }
        else if (GPIOA_outputInitPtr->outputConfig ==1)
        {
            GPIO_PORTA_PDR_R  |= 1<<(GPIOA_outputInitPtr->pin);
        }
        else if (GPIOA_outputInitPtr->outputConfig ==2)
        {
            GPIO_PORTA_ODR_R  |= 1<<(GPIOA_outputInitPtr->pin);
        }

}
void GPIOA_writeOutputPinValue (GPIOA_pinNumber pin, uint8_t value)
{
    GPIO_PORTA_DATA_R |= value<<pin;
}

