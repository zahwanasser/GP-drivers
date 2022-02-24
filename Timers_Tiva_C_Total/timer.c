/*
 * timer.c
 *
 *  Created on: Feb 10, 2022
 *      Author: Zahwa Nasser
 */
#include "timer.h"

/* Global variable to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

/* in case of Timeout interrupt */
ISR(Timer_Timeout_int)
{
	if(g_callBackPtr != NULL_PTR)
		{
			(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}

/* in case of matching interrupt */
ISR(Timer_Matching_int)
{
	if(g_callBackPtr != NULL_PTR)
		{
			(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description : Function to initialize and configure the 16 bit timer module
 *  first we need to enable the timer module
 *  1. Ensure the timer is disabled (the TnEN bit in the GPTMCTL register is cleared) before making
    any changes.
    2. Write the GPTM Configuration Register (GPTMCFG) with a value of the mode we want
    3. Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR):
        a. Write a value of 0x1 for One-Shot mode.
        b. Write a value of 0x2 for Periodic mode.
    4. Optionally configure the TnSNAPS (for snapshot mode) , TnWOT(trigger for timer in daisy chain but must be 0 for module 0 timerA), TnMTE(i think this one is for generating an interrupt on matching), and TnCDIR (for counting up or down) bits in the GPTMTnMR register
        to select whether to capture the value of the free-running timer at time-out, use an external
        trigger to start counting, configure an additional trigger or interrupt, and count up or down.
    5. Load the start value into the GPTM Timer n Interval Load Register (GPTMTnILR).
    6. load the prescalar value
    7. if using matching thing configure it
    8. If interrupts are required, set the appropriate bits in the GPTM Interrupt Mask Register
    (GPTMIMR).
    9. Set the TnEN bit in the GPTMCTL register to enable the timer and start counting.
    10. **Poll the GPTMRIS register or wait for the interrupt to be generated (if enabled). In both cases,
    the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear
    Register (GPTMICR).**

 **—> also there is the error flag in case of the wide timer**
 *
 *  Arguments: pointer to structure holding the required info
 *  Returns: void
 */
void timer16_config(timer16_configStruct * timer16_configPtr)
{   //turning on the module
//    if(timer16_config->module==0)
//    {
//        RCGCTIMER |= 1<<;
//    }
//    else if (timer16_config->module==1)
//    {
//
//    }
//    else if (timer16_config->module==2)
//    {
//
//    }
//    else if (timer16_config->module==3)
//    {
//
//    }
//    else if (timer16_config->module==4)
//    {
//
//    }
//    else if (timer16_config->module==5)
//    {
//
//    }
    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R0;	//Make Timer0 (16/32 bits) in the run mode.
    if(timer16_configPtr->timer==0) //timerA
    {
        if(timer16_configPtr->mode == 0) //periodic
        {
            TIMER0_CTL_R &= (~(TIMER_CTL_TAEN)); //make sure that it's disabled before anything
            TIMER0_CFG_R = 0x4; // to enable 16bit mode
            TIMER0_TAMR_R = 0x2; //periodic mode
            TIMER0_TAMR_R &= (~(TIMER_TAMR_TACDIR )); //count down
            TIMER0_TAMR_R |= TIMER_TAMR_TAMIE; // an interrupt is generated in case of matching
            TIMER0_TAMR_R &=(~(TIMER_TAMR_TAWOT)); //trigger in daisy chain?? but must be zero for module 0 timerA
            TIMER0_TAMR_R |= TIMER_TAMR_TAILD ; //update the upper value the next timeout
            TIMER0_TAMR_R |= TIMER_TAMR_TAMRSU ; //update the matching value the next timeout
            TIMER0_TAPR_R = timer16_configPtr-> prescalar;
            TIMER0_TAILR_R = timer16_configPtr->timer_startValue; //the start value of the timer
            TIMER0_IMR_R  |=TIMER_IMR_TATOIM; //timeout interrupt
            //matching mode
            if(timer16_configPtr->mode==2)
            {
                TIMER0_TAMATCHR_R =timer16_configPtr ->timer_matchingValue;
                TIMER0_IMR_R  |= TIMER_IMR_TAMIM; //matching interrupt
            }


            //enable the timer to start counting
            TIMER0_CTL_R  |=TIMER_CTL_TAEN;

        }
        else if (timer16_configPtr ->mode ==1) //one shot
        {
        	TIMER0_CFG_R = 0x4;  //Selects the 16 bits mode.
        	TIMER0_PP_R &= (~(TIMER_PP_SIZE_16));	//16 bits counter with 8 bits prescalar.
        	TIMER0_CTL_R &= (~(TIMER_CTL_TAEN));  //Disable Timer A
        	TIMER0_TAMR_R = 0x1;   //Selects the one-shot mode.
        	TIMER0_TAMR_R &= (~(TIMER_TAMR_TACDIR )); //Sets the timer to count down.
        	TIMER0_SYNC_R |= TIMER_SYNC_SYNCT0_TA;  //Activate Time-Out event for Timer A
        	TIMER0_TAMR_R |= TIMER_TAMR_TAMIE; 	  //Activate Match interrupt Mask for Timer A
        	TIMER0_IMR_R  |= TIMER_IMR_TATOIM;   //Activate Time-Out interrupt Mask for Timer A
        	TIMER0_TAILR_R = timer16_configPtr->timer_startValue; //Loads the start value for Timer A
        	TIMER0_TAPR_R = timer16_configPtr->prescalar;	//sets the prescalar value for Timer A

        	if(timer16_configPtr->mode == 3)	//check if we use Wait on trigger mode or not
        	{
        		TIMER0_TAMR_R |= TIMER_TAMR_TAWOT;
        	}
        	else if(timer16_configPtr->mode != 3)
        	{
        		TIMER0_TAMR_R &= (~(TIMER_TAMR_TAWOT));
        	}

        	if(timer16_configPtr->mode == 2)	//check if we use Match interrupt mode or not
        	{
        		TIMER0_IMR_R  |= TIMER_IMR_TAMIM;
        		TIMER0_TAMATCHR_R = timer16_configPtr->timer_matchingValue; //Putting the match value in the match register for Timer A
        	}
        	else if(timer16_configPtr->mode != 2)
        	{
        		TIMER0_IMR_R &= (~(TIMER_IMR_TAMIM));
        	}

        	TIMER0_CTL_R  |= TIMER_CTL_TAEN;	//Activate Timer A
        }
    }

    else //timerB
    {
        if(timer16_configPtr->mode == 0) //periodic
        {
            TIMER0_CTL_R &= (~(TIMER_CTL_TBEN)); //make sure that it's disabled before anything
            TIMER0_CFG_R = 0x4; // to enable 16bit mode
            TIMER0_TBMR_R |= 0x002; //periodic mode
            TIMER0_TBMR_R = (~(TIMER_TBMR_TBCDIR )); //count down
            TIMER0_TBMR_R |= TIMER_TBMR_TBMIE    ; // an interrupt is generated in case of matching
            TIMER0_TBMR_R &=(~(TIMER_TBMR_TBWOT  )); //trigger in daisy chain?? but must be zero for module 0 timerA
            TIMER0_TBMR_R |= TIMER_TBMR_TBILD ; //update the upper value the next timeout
            TIMER0_TBMR_R |= TIMER_TBMR_TBMRSU ; //update the matching value the next timeout
            TIMER0_TBPR_R = timer16_configPtr -> prescalar;
            TIMER0_TBILR_R = timer16_configPtr->timer_startValue; //the start value of the timer
            TIMER0_IMR_R  |=TIMER_IMR_TBTOIM  ; //timeout interrupt
            //matching mode
            if(timer16_configPtr->mode==2)
            {
                TIMER0_TBMATCHR_R =timer16_configPtr ->timer_matchingValue;
                TIMER0_IMR_R |= TIMER_IMR_TBMIM ; //matching interrupt
            }


            //enable the timer to start counting
            TIMER0_CTL_R  |=TIMER_CTL_TAEN;
            if (timer16_configPtr->mode == 3) //wait for trigger mode
            {
                TIMER0_TBMR_R |= TIMER_TBMR_TBWOT;
            }

        }
        else if (timer16_configPtr ->mode == 1) //one shot
        {
        	TIMER0_CFG_R = 0x4;  //Selects the 16 bits mode.
        	TIMER0_PP_R &= (~(TIMER_PP_SIZE_16));	//16 bits counter with 8 bits prescalar.
        	TIMER0_CTL_R &= (~(TIMER_CTL_TBEN));  //Disable Timer B
        	TIMER0_TBMR_R = 0x1;   //Selects the one-shot mode.
        	TIMER0_TBMR_R &= (~(TIMER_TBMR_TBCDIR )); //Sets the timer to count down.
        	TIMER0_SYNC_R |= TIMER_SYNC_SYNCT0_TB;  //Activate Time-Out event for Timer B
        	TIMER0_TBMR_R |= TIMER_TBMR_TBMIE; 	  //Activate Match interrupt Mask for Timer B
        	TIMER0_IMR_R  |= TIMER_IMR_TBTOIM;   //Activate Time-Out interrupt Mask for Timer A
        	TIMER0_TBILR_R = timer16_configPtr->timer_startValue; //Loads the start value for Timer B
        	TIMER0_TBPR_R = timer16_configPtr->prescalar;	//sets the prescalar value for Timer B

        	if(timer16_configPtr->mode == 3)	//check if we use Wait on trigger mode or not
        	{
        		 TIMER0_TBMR_R |= TIMER_TBMR_TBWOT;
        	}
        	else if(timer16_configPtr->mode != 3)
        	{
        		 TIMER0_TBMR_R &= (~(TIMER_TBMR_TBWOT));
        	}

        	if(timer16_configPtr->mode == 2)	//check if we use Match interrupt mode or not
        	{
        	     TIMER0_IMR_R  |= TIMER_IMR_TBMIM;
        	     TIMER0_TBMATCHR_R = timer16_configPtr->timer_matchingValue; //Putting the match value in the match register for Timer B
        	}
        	else if(timer16_configPtr->mode != 2)
        	{
        	   	 TIMER0_IMR_R &= (~(TIMER_IMR_TBMIM));
        	}

        	TIMER0_CTL_R  |= TIMER_CTL_TBEN;	//Activate Timer B
        }
    }
}

void timer32_config(const timer32_configStruct* timer32_config)
{   //turning on the module
//    if(timer16_configPtr->module==0)
//    {
//        RCGCTIMER |= 1<<;
//    }
//    else if (timer16_configPtr->module==1)
//    {
//
//    }
//    else if (timer16_configPtr->module==2)
//    {
//
//    }
//    else if (timer16_configPtr->module==3)
//    {
//
//    }
//    else if (timer16_configPtr->module==4)
//    {
//
//    }
//    else if (timer16_configPtr->module==5)
//    {
//
//    }
    SYSCTL_RCGCWTIMER_R |= SYSCTL_RCGCWTIMER_R0;
    if(timer32_config->timer==0) //timerA
    {
        if(timer32_config->mode == 0) //periodic
        {
            WTIMER0_CTL_R &= (~(TIMER_CTL_TAEN)); //make sure that it's disabled before anything
            WTIMER0_CFG_R = 0x4; // to enable 32bit mode
            WTIMER0_TAMR_R |= 0x002; //periodic mode
            WTIMER0_TAMR_R = (~(TIMER_TAMR_TACDIR )); //count down
            WTIMER0_TAMR_R |= TIMER_TAMR_TAMIE    ; // an interrupt is generated in case of matching
            WTIMER0_TAMR_R &=(~(TIMER_TAMR_TAWOT  )); //trigger in daisy chain?? but must be zero for module 0 timerA
            WTIMER0_TAMR_R |= TIMER_TAMR_TAILD ; //update the upper value the next timeout
            WTIMER0_TAMR_R |= TIMER_TAMR_TAMRSU ; //update the matching value the next timeout
            WTIMER0_TAPR_R = timer32_config -> prescalar;
            WTIMER0_TAILR_R = timer32_config->timer_startValue; //the start value of the timer
            WTIMER0_IMR_R  |=TIMER_IMR_TATOIM  ; //timeout interrupt
            //matching mode
            if(timer32_config->mode==2)
            {
                WTIMER0_TAMATCHR_R = timer32_config ->timer_matchingValue;
                WTIMER0_IMR_R  |= TIMER_IMR_TAMIM ; //matching interrupt
            }


            //enable the timer to start counting
            WTIMER0_CTL_R  |=TIMER_CTL_TAEN;

        }
        else if (timer32_config->mode ==1) //one shot
        {
        	WTIMER0_CFG_R = 0x4;  //Selects the 32 bits mode.
        	WTIMER0_PP_R &= (~(TIMER_PP_SIZE_16));	//32 bits counter with 16 bits prescalar.
        	WTIMER0_CTL_R &= (~(TIMER_CTL_TAEN));  //Disable Timer A
        	WTIMER0_TAMR_R = 0x1;   //Selects the one-shot mode.
        	WTIMER0_TAMR_R &= (~(TIMER_TAMR_TACDIR )); //Sets the timer to count down.
        	WTIMER0_SYNC_R |= TIMER_SYNC_SYNCT0_TA;  //Activate Time-Out event for Timer A
        	WTIMER0_TAMR_R |= TIMER_TAMR_TAMIE; 	  //Activate Match interrupt Mask for Timer A
        	WTIMER0_IMR_R  |= TIMER_IMR_TATOIM;   //Activate Time-Out interrupt Mask for Timer A
        	WTIMER0_TAILR_R = timer32_config->timer_startValue; //Loads the start value for Timer A
        	WTIMER0_TAPR_R = timer32_config->prescalar;	//sets the prescalar value for Timer A

        	if(timer32_config->mode == 3)	//check if we use Wait on trigger mode or not
        	{
        	    WTIMER0_TAMR_R |= TIMER_TAMR_TAWOT;
        	}
        	else if(timer32_config->mode != 3)
        	{
        		WTIMER0_TAMR_R &= (~(TIMER_TAMR_TAWOT));
        	}

        	if(timer32_config->mode == 2)	//check if we use Match interrupt mode or not
        	{
        	    WTIMER0_IMR_R  |= TIMER_IMR_TAMIM;
        	    WTIMER0_TAMATCHR_R = timer32_config->timer_matchingValue; //Putting the match value in the match register for Timer A
        	}
        	else if(timer32_config->mode != 2)
        	{
        		WTIMER0_IMR_R &= (~(TIMER_IMR_TAMIM));
        	}

        	WTIMER0_CTL_R  |= TIMER_CTL_TAEN;	//Activate Timer A
        }

    }
    else //timerB
    {
        if(timer32_config->mode == 0) //periodic
        {
            WTIMER0_CTL_R &= (~(TIMER_CTL_TBEN)); //make sure that it's disabled before anything
            WTIMER0_CFG_R = 0x4; // to enable 32bit mode
            WTIMER0_TBMR_R |= 0x002; //periodic mode
            WTIMER0_TBMR_R = (~(TIMER_TBMR_TBCDIR )); //count down
            WTIMER0_TBMR_R |= TIMER_TBMR_TBMIE    ; // an interrupt is generated in case of matching
            WTIMER0_TBMR_R &=(~(TIMER_TBMR_TBWOT  )); //trigger in daisy chain?? but must be zero for module 0 timerA
            WTIMER0_TBMR_R |= TIMER_TBMR_TBILD ; //update the upper value the next timeout
            WTIMER0_TBMR_R |= TIMER_TBMR_TBMRSU ; //update the matching value the next timeout
            WTIMER0_TBPR_R = timer32_config -> prescalar;
            WTIMER0_TBILR_R = timer32_config->timer_startValue; //the start value of the timer
            WTIMER0_IMR_R  |=TIMER_IMR_TBTOIM  ; //timeout interrupt
            //matching mode
            if(timer32_config->mode==2)
            {
                WTIMER0_TAMATCHR_R =timer32_config ->timer_matchingValue;
                WTIMER0_IMR_R  |= TIMER_IMR_TBMIM ; //matching interrupt
            }


            //enable the timer to start counting
            WTIMER0_CTL_R  |=TIMER_CTL_TAEN;
            if (timer32_config->mode == 3) //wait for trigger mode
            {
                WTIMER0_TBMR_R |= TIMER_TBMR_TBWOT;
            }

        }
        else if (timer32_config ->mode ==1) //one shot
        {
        	WTIMER0_CFG_R = 0x4;  //Selects the 32 bits mode.
        	WTIMER0_PP_R &= (~(TIMER_PP_SIZE_16));	//32 bits counter with 16 bits prescalar.
        	WTIMER0_CTL_R &= (~(TIMER_CTL_TBEN));  //Disable Timer B
        	WTIMER0_TBMR_R = 0x1;   //Selects the one-shot mode.
        	WTIMER0_TBMR_R &= (~(TIMER_TBMR_TBCDIR )); //Sets the timer to count down.
        	WTIMER0_SYNC_R |= TIMER_SYNC_SYNCT0_TB;  //Activate Time-Out event for Timer B
        	WTIMER0_TBMR_R |= TIMER_TBMR_TBMIE; 	  //Activate Match interrupt Mask for Timer B
        	WTIMER0_IMR_R  |= TIMER_IMR_TBTOIM;   //Activate Time-Out interrupt Mask for Timer A
        	WTIMER0_TBILR_R = timer32_config->timer_startValue; //Loads the start value for Timer B
        	WTIMER0_TBPR_R = timer32_config->prescalar;	//sets the prescalar value for Timer B

        	if(timer32_config->mode == 3)	//check if we use Wait on trigger mode or not
        	{
        	 	 WTIMER0_TBMR_R |= TIMER_TBMR_TBWOT;
        	}
        	else if(timer32_config->mode != 3)
        	{
        	     WTIMER0_TBMR_R &= (~(TIMER_TBMR_TBWOT));
        	}

        	if(timer32_config->mode == 2)	//check if we use Match interrupt mode or not
        	{
        		 WTIMER0_IMR_R  |= TIMER_IMR_TBMIM;
        	     WTIMER0_TBMATCHR_R = timer32_config->timer_matchingValue; //Putting the match value in the match register for Timer B
        	}
        	else if(timer32_config->mode != 2)
        	{
        	     WTIMER0_IMR_R &= (~(TIMER_IMR_TBMIM));
        	}

        	WTIMER0_CTL_R  |= TIMER_CTL_TBEN;	//Activate Timer B
        }
    }
}
void timer64_config(const timer64_configStruct* timer64_config)
{   //turning on the module
//    if(timer16_configPtr->module==0)
//    {
//        RCGCTIMER |= 1<<;
//    }
//    else if (timer16_configPtr->module==1)
//    {
//
//    }
//    else if (timer16_config->module==2)
//    {
//
//    }
//    else if (timer16_config->module==3)
//    {
//
//    }
//    else if (timer16_config->module==4)
//    {
//
//    }
//    else if (timer16_config->module==5)
//    {
//
//    }
    SYSCTL_RCGCWTIMER_R |= SYSCTL_RCGCWTIMER_R0 ;

        if(timer64_config->mode == 0) //periodic
        {
            WTIMER0_CTL_R &= (~(TIMER_CTL_TAEN)); //make sure that it's disabled before anything
            WTIMER0_CFG_R = 0; // to enable 64bit mode
            WTIMER0_TAMR_R |= 0x002; //periodic mode
            WTIMER0_TAMR_R = (~(TIMER_TAMR_TACDIR )); //count down
            WTIMER0_TAMR_R |= TIMER_TAMR_TAMIE    ; // an interrupt is generated in case of matching
            WTIMER0_TAMR_R &= (~(TIMER_TAMR_TAWOT  )); //trigger in daisy chain?? but must be zero for module 0 timerA
            WTIMER0_TAMR_R |= TIMER_TAMR_TAILD ; //update the upper value the next timeout
            WTIMER0_TAMR_R |= TIMER_TAMR_TAMRSU ; //update the matching value the next timeout
            WTIMER0_TAPR_R = timer64_config -> prescalar;
            WTIMER0_TBILR_R = (timer64_config->timer_startValue) & 0xFFFF0000; //the start value of the timer for the concatenated mode we access
                                                                           // the most signficant bits first
            WTIMER0_TAILR_R = (timer64_config->timer_startValue) & 0x0000FFFF;
            WTIMER0_IMR_R  |=TIMER_IMR_TATOIM; //timeout interrupt
            WTIMER0_IMR_R  |=TIMER_IMR_WUEIM;


            //matching mode
            if(timer64_config->mode==2)
            {
                WTIMER0_TBMATCHR_R =(timer64_config ->timer_matchingValue) & 0xFFFF0000;
                WTIMER0_TAMATCHR_R =(timer64_config ->timer_matchingValue) & 0x0000FFFF;
                WTIMER0_IMR_R  |= TIMER_IMR_TAMIM ; //matching interrupt
            }

            //enable the timer to start counting
            WTIMER0_CTL_R  |=TIMER_CTL_TAEN;

        }
        else if (timer64_config ->mode ==1) //one shot
        {
        	WTIMER0_CFG_R = 0;  //Selects the 32 bits mode.
        	WTIMER0_PP_R &= (~(TIMER_PP_SIZE_16));	//32 bits counter with 16 bits prescalar.
        	WTIMER0_CTL_R &= (~(TIMER_CTL_TAEN));  //Disable Timer A
        	WTIMER0_TAMR_R = 0x1;   //Selects the one-shot mode.
        	WTIMER0_TAMR_R &= (~(TIMER_TAMR_TACDIR )); //Sets the timer to count down.
        	WTIMER0_SYNC_R |= TIMER_SYNC_SYNCT0_TA;  //Activate Time-Out event for Timer A
        	WTIMER0_TAMR_R |= TIMER_TAMR_TAMIE; 	  //Activate Match interrupt Mask for Timer A
        	WTIMER0_IMR_R  |= TIMER_IMR_TATOIM;   //Activate Time-Out interrupt Mask for Timer A
        	WTIMER0_IMR_R  |=TIMER_IMR_WUEIM;
        	WTIMER0_TAILR_R = (timer64_config->timer_startValue) & 0xFFFF0000; //Loads the start value for Timer A
        	WTIMER0_TAILR_R = (timer64_config->timer_startValue) & 0x0000FFFF;
        	WTIMER0_TAPR_R = timer64_config->prescalar;	//sets the prescalar value for Timer A

        	if(timer64_config->mode == 3)	//check if we use Wait on trigger mode or not
        	{
        	    WTIMER0_TAMR_R |= TIMER_TAMR_TAWOT;
        	}
        	else if(timer64_config->mode != 3)
        	{
        		WTIMER0_TAMR_R &= (~(TIMER_TAMR_TAWOT));
        	}

        	if(timer64_config->mode == 2)	//check if we use Match interrupt mode or not
        	{
        	    WTIMER0_TBMATCHR_R =(timer64_config ->timer_matchingValue) & 0xFFFF0000;
        	    WTIMER0_TAMATCHR_R =(timer64_config ->timer_matchingValue) & 0x0000FFFF; //Putting the match value in the match register for Timer A
        	    WTIMER0_IMR_R  |= TIMER_IMR_TAMIM;
        	}
        	else if(timer64_config->mode != 2)
        	{
        		WTIMER0_IMR_R &= (~(TIMER_IMR_TAMIM));
        	}

        	WTIMER0_CTL_R  |= TIMER_CTL_TAEN;	//Activate Timer A

        }

}
/*
 * Description : Function to disable the timers by clearing the TAEN bit

 *  Arguments: pointer to structure holding the required info
 *  Returns: void
 */
void timer_disable(const timer_disableStruct* timer_disable)
{
  //first we choose the size of the running timer then we diable it
    if (timer_disable->timer == 0 && (timer_disable->size ==0 || timer_disable->size ==1)) //if it's timer A and it's 16 bit or 32 bit
    {
        TIMER0_CTL_R &= (~(TIMER_CTL_TAEN));
    }
    else if (timer_disable->timer == 1 && (timer_disable->size ==0 || timer_disable->size ==1)) //if it's timer B and it's 16 bit or 32 bit
    {
        TIMER0_CTL_R &= (~(TIMER_CTL_TBEN));
    }
    else if (timer_disable->size ==2) //if it's 64 bit
    {
        TIMER0_CTL_R &= (~(TIMER_CTL_TAEN));
    }
}

/*
 * Description: Function to set the Call Back function address.
 */
void timer_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}

//void timer16_synchronize (timer16_syncEnum* timer16_sync)
//{
//    //enable module0
//    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R0;
//    TIMER0_SYNC_R |= timer16_sync;
//}
//
