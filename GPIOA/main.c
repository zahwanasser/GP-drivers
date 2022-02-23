/*
 * main.c
 *
 *  Created on: Feb 18, 2022
 *      Author: D
 */


#include "GPIOA.h"
int  main (void)
{
  GPIOA_enableInput(PIN5);
  GPIOA_readInputPinValue(PIN5); 
  GPIOA_outputInitStruct GPIOA_outputInitPtr= { PIN0, two, pullup};
  GPIOA_enableOutput(&GPIOA_outputInitPtr);
  GPIOA_writeOutputPinValue(PIN0, 1);
  return 0;
}
