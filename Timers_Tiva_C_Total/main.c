

/**
 * main.c
 */
#include "timer.h"
#include "std_types.h"
#include "tm4c123gh6pm.h"
int main(void)
{
	
        timer16_configStruct timer16_configPtr={ timerA, periodic,100,0,0};
        timer16_config (&timer16_configPtr);
}
