/*
 * ADC_Normal.c
 *
 *  Created on: Feb 24, 2022
 *      Author: Mena Emiel
 */
#include "ADC_Normal.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void ADC_NormalMode(ADC_NormalModeStruct* ADC_NormalModePtr)
{
  //checking which sample sequencer we will use
  if(ADC_NormalModePtr->SSC_No ==ss0)
  {
    ADC0_ACTSS_R &= ~(ADC_ACTSS_ASEN0); //Disabling sample sequencer
    
    if(ADC_NormalModePtr->int_status == enable)  //Enabling the interrupts mask for Sample Sequencer 0
    {
      ADC0_IM_R |= ADC_IM_MASK0;
    }
    
    //Choosing the ADC Trigger Mode//
    if(ADC_NormalModePtr->Trigger == PROCESSOR)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM0_PROCESSOR; //Default trigger mode
    }
    else if(ADC_NormalModePtr->Trigger == COMP0)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM0_COMP0; //Analog comparator 0 trigger mode
    }
    else if(ADC_NormalModePtr->Trigger == COMP1)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM0_COMP1; //Analog comparator 1 trigger mode
    }
    else if(ADC_NormalModePtr->Trigger == EXTERNAL)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM0_EXTERNAL; //External GPIO trigger mode
    }
    else if(ADC_NormalModePtr->Trigger == TIMER)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM0_TIMER; //Timer trigger mode
    }
    else if(ADC_NormalModePtr->Trigger == PWM0)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM0_PWM0; //PWM 0 trigger mode
      if(ADC_NormalModePtr->PWM_module == PWM1_module)
      {
        ADC0_TSSEL_R |= ADC_TSSEL_PS0_1; //Enabling PWN module 1 for PWN gen. 0 cuz PWM module 0 is chosen by default
      }
    }
    else if(ADC_NormalModePtr->Trigger == PWM1)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM0_PWM1; //PWM 1 trigger mode
      if(ADC_NormalModePtr->PWM_module == PWM1_module)
      {
        ADC0_TSSEL_R |= ADC_TSSEL_PS1_1; //Enabling PWN module 1 for PWN gen. 1 cuz PWM module 0 is chosen by default
      }
    }
    else if(ADC_NormalModePtr->Trigger == PWM2)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM0_PWM2; //PWM 2 trigger mode
      if(ADC_NormalModePtr->PWM_module == PWM1_module)
      {
        ADC0_TSSEL_R |= ADC_TSSEL_PS2_1; //Enabling PWN module 1 for PWN gen. 2 cuz PWM module 0 is chosen by default
      }
    }
    else if(ADC_NormalModePtr->Trigger == PWM3)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM0_PWM3; //PWM 3 trigger mode
      if(ADC_NormalModePtr->PWM_module == PWM1_module)
      {
        ADC0_TSSEL_R |= ADC_TSSEL_PS3_1; //Enabling PWN module 1 for PWN gen. 3 cuz PWM module 0 is chosen by default
      }
    }
    else if(ADC_NormalModePtr->Trigger == ALWAYS)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM0_ALWAYS; //Always trigger mode
    }
    
    
    //Choosing Interrupts will be at which bit//
    if(ADC_NormalModePtr->interrupt_bit_no == bit0INT) //Interrupt happened at bit number 0
    {
      ADC0_SSCTL0_R |= ADC_SSCTL0_IE0;
    }
    else if(ADC_NormalModePtr->interrupt_bit_no == bit1INT) //Interrupt happened at bit number 1
    {
      ADC0_SSCTL0_R |= ADC_SSCTL0_IE1;
    }
    else if(ADC_NormalModePtr->interrupt_bit_no == bit2INT) //Interrupt happened at bit number 2
    {
      ADC0_SSCTL0_R |= ADC_SSCTL0_IE2;
    }
    else if(ADC_NormalModePtr->interrupt_bit_no == bit3INT) //Interrupt happened at bit number 3
    {
      ADC0_SSCTL0_R |= ADC_SSCTL0_IE3;
    }
    else if(ADC_NormalModePtr->interrupt_bit_no == bit4INT) //Interrupt happened at bit number 4
    {
      ADC0_SSCTL0_R |= ADC_SSCTL0_IE4;
    }
    else if(ADC_NormalModePtr->interrupt_bit_no == bit5INT) //Interrupt happened at bit number 5
    {
      ADC0_SSCTL0_R |= ADC_SSCTL0_IE5;
    }
    else if(ADC_NormalModePtr->interrupt_bit_no == bit6INT) //Interrupt happened at bit number 6
    {
      ADC0_SSCTL0_R |= ADC_SSCTL0_IE6;
    }
    else if(ADC_NormalModePtr->interrupt_bit_no == bit7INT) //Interrupt happened at bit number 7
    {
      ADC0_SSCTL0_R |= ADC_SSCTL0_IE7;
    }
    
    
    //Choosing End of sequence will be at which bit//
    if(ADC_NormalModePtr->EOS_bit_no == bit0EOS) //End of sequence at bit number 0
    {
      ADC0_SSCTL0_R |= ADC_SSCTL0_END0;
    }
    else if(ADC_NormalModePtr->EOS_bit_no == bit1EOS) //End of sequence at bit number 1
    {
      ADC0_SSCTL0_R |= ADC_SSCTL0_END1;
    }
    else if(ADC_NormalModePtr->EOS_bit_no == bit2EOS) //End of sequence at bit number 2
    {
      ADC0_SSCTL0_R |= ADC_SSCTL0_END2;
    }
    else if(ADC_NormalModePtr->EOS_bit_no == bit3EOS) //End of sequence at bit number 3
    {
      ADC0_SSCTL0_R |= ADC_SSCTL0_END3;
    }
    else if(ADC_NormalModePtr->EOS_bit_no == bit4EOS) //End of sequence at bit number 4
    {
      ADC0_SSCTL0_R |= ADC_SSCTL0_END4;
    }
    else if(ADC_NormalModePtr->EOS_bit_no == bit5EOS) //End of sequence at bit number 5
    {
      ADC0_SSCTL0_R |= ADC_SSCTL0_END5;
    }
    else if(ADC_NormalModePtr->EOS_bit_no == bit6EOS) //End of sequence at bit number 6
    {
      ADC0_SSCTL0_R |= ADC_SSCTL0_END6;
    }
    else if(ADC_NormalModePtr->EOS_bit_no == bit7EOS) //End of sequence at bit number 7
    {
      ADC0_SSCTL0_R |= ADC_SSCTL0_END7;
    }
  }
  
  //////////////////Sample Sequence number 1//////////////////////
  else if(ADC_NormalModePtr->SSC_No == ss1)
  {
    ADC0_ACTSS_R &= ~(ADC_ACTSS_ASEN1); //Disabling sample sequencer
    
    if(ADC_NormalModePtr->int_status == enable)  //Enabling the interrupts mask for Sample Sequencer 1
    {
      ADC0_IM_R |= ADC_IM_MASK1;
    }
    
    //Choosing the ADC Trigger Mode//
    if(ADC_NormalModePtr->Trigger == PROCESSOR)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM1_PROCESSOR; //Default trigger mode
    }
    else if(ADC_NormalModePtr->Trigger == COMP0)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM1_COMP0; //Analog comparator 0 trigger mode
    }
    else if(ADC_NormalModePtr->Trigger == COMP1)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM1_COMP1; //Analog comparator 1 trigger mode
    }
    else if(ADC_NormalModePtr->Trigger == EXTERNAL)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM1_EXTERNAL; //External GPIO trigger mode
    }
    else if(ADC_NormalModePtr->Trigger == TIMER)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM1_TIMER; //Timer trigger mode
    }
    else if(ADC_NormalModePtr->Trigger == PWM0)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM1_PWM0; //PWM 0 trigger mode
      if(ADC_NormalModePtr->PWM_module == PWM1_module)
      {
        ADC0_TSSEL_R |= ADC_TSSEL_PS0_1; //Enabling PWN module 1 for PWN gen. 0 cuz PWM module 0 is chosen by default
      }
    }
    else if(ADC_NormalModePtr->Trigger == PWM1)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM1_PWM1; //PWM 1 trigger mode
      if(ADC_NormalModePtr->PWM_module == PWM1_module)
      {
        ADC0_TSSEL_R |= ADC_TSSEL_PS1_1; //Enabling PWN module 1 for PWN gen. 1 cuz PWM module 0 is chosen by default
      }
    }
    else if(ADC_NormalModePtr->Trigger == PWM2)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM1_PWM2; //PWM 2 trigger mode
      if(ADC_NormalModePtr->PWM_module == PWM1_module)
      {
        ADC0_TSSEL_R |= ADC_TSSEL_PS2_1; //Enabling PWN module 1 for PWN gen. 2 cuz PWM module 0 is chosen by default
      }
    }
    else if(ADC_NormalModePtr->Trigger == PWM3)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM1_PWM3; //PWM 3 trigger mode
      if(ADC_NormalModePtr->PWM_module == PWM1_module)
      {
        ADC0_TSSEL_R |= ADC_TSSEL_PS3_1; //Enabling PWN module 1 for PWN gen. 3 cuz PWM module 0 is chosen by default
      }
    }
    else if(ADC_NormalModePtr->Trigger == ALWAYS)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM1_ALWAYS; //Always trigger mode
    }
    
    
    //Choosing Interrupts will be at which bit//
    if(ADC_NormalModePtr->interrupt_bit_no == bit0INT) //Interrupt happened at bit number 0
    {
      ADC0_SSCTL1_R |= ADC_SSCTL1_IE0;
    }
    else if(ADC_NormalModePtr->interrupt_bit_no == bit1INT) //Interrupt happened at bit number 1
    {
      ADC0_SSCTL1_R |= ADC_SSCTL1_IE1;
    }
    else if(ADC_NormalModePtr->interrupt_bit_no == bit2INT) //Interrupt happened at bit number 2
    {
      ADC0_SSCTL1_R |= ADC_SSCTL1_IE2;
    }
    else if(ADC_NormalModePtr->interrupt_bit_no == bit3INT) //Interrupt happened at bit number 3
    {
      ADC0_SSCTL1_R |= ADC_SSCTL1_IE3;
    }
    
    
    //Choosing End of sequence will be at which bit//
    if(ADC_NormalModePtr->EOS_bit_no == bit0EOS) //End of sequence at bit number 0
    {
      ADC0_SSCTL1_R |= ADC_SSCTL1_END0;
    }
    else if(ADC_NormalModePtr->EOS_bit_no == bit1EOS) //End of sequence at bit number 1
    {
      ADC0_SSCTL1_R |= ADC_SSCTL1_END1;
    }
    else if(ADC_NormalModePtr->EOS_bit_no == bit2EOS) //End of sequence at bit number 2
    {
      ADC0_SSCTL1_R |= ADC_SSCTL1_END2;
    }
    else if(ADC_NormalModePtr->EOS_bit_no == bit3EOS) //End of sequence at bit number 3
    {
      ADC0_SSCTL1_R |= ADC_SSCTL1_END3;
    }
  }
  
  
  //////////////////Sample Sequence number 2//////////////////////
  else if(ADC_NormalModePtr->SSC_No == ss2)
  {
    ADC0_ACTSS_R &= ~(ADC_ACTSS_ASEN2); //Disabling sample sequencer
    
    if(ADC_NormalModePtr->int_status == enable)  //Enabling the interrupts mask for Sample Sequencer 2
    {
      ADC0_IM_R |= ADC_IM_MASK2;
    }
    
    //Choosing the ADC Trigger Mode//
    if(ADC_NormalModePtr->Trigger == PROCESSOR)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM2_PROCESSOR; //Default trigger mode
    }
    else if(ADC_NormalModePtr->Trigger == COMP0)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM2_COMP0; //Analog comparator 0 trigger mode
    }
    else if(ADC_NormalModePtr->Trigger == COMP1)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM2_COMP1; //Analog comparator 1 trigger mode
    }
    else if(ADC_NormalModePtr->Trigger == EXTERNAL)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM2_EXTERNAL; //External GPIO trigger mode
    }
    else if(ADC_NormalModePtr->Trigger == TIMER)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM2_TIMER; //Timer trigger mode
    }
    else if(ADC_NormalModePtr->Trigger == PWM0)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM2_PWM0; //PWM 0 trigger mode
      if(ADC_NormalModePtr->PWM_module == PWM1_module)
      {
        ADC0_TSSEL_R |= ADC_TSSEL_PS0_1; //Enabling PWN module 1 for PWN gen. 0 cuz PWM module 0 is chosen by default
      }
    }
    else if(ADC_NormalModePtr->Trigger == PWM1)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM2_PWM1; //PWM 1 trigger mode
      if(ADC_NormalModePtr->PWM_module == PWM1_module)
      {
        ADC0_TSSEL_R |= ADC_TSSEL_PS1_1; //Enabling PWN module 1 for PWN gen. 1 cuz PWM module 0 is chosen by default
      }
    }
    else if(ADC_NormalModePtr->Trigger == PWM2)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM2_PWM2; //PWM 2 trigger mode
      if(ADC_NormalModePtr->PWM_module == PWM1_module)
      {
        ADC0_TSSEL_R |= ADC_TSSEL_PS2_1; //Enabling PWN module 1 for PWN gen. 2 cuz PWM module 0 is chosen by default
      }
    }
    else if(ADC_NormalModePtr->Trigger == PWM3)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM2_PWM3; //PWM 3 trigger mode
      if(ADC_NormalModePtr->PWM_module == PWM1_module)
      {
        ADC0_TSSEL_R |= ADC_TSSEL_PS3_1; //Enabling PWN module 1 for PWN gen. 3 cuz PWM module 0 is chosen by default
      }
    }
    else if(ADC_NormalModePtr->Trigger == ALWAYS)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM2_ALWAYS; //Always trigger mode
    }
    
    
    //Choosing Interrupts will be at which bit//
    if(ADC_NormalModePtr->interrupt_bit_no == bit0INT) //Interrupt happened at bit number 0
    {
      ADC0_SSCTL2_R |= ADC_SSCTL2_IE0;
    }
    else if(ADC_NormalModePtr->interrupt_bit_no == bit1INT) //Interrupt happened at bit number 1
    {
      ADC0_SSCTL2_R |= ADC_SSCTL2_IE1;
    }
    else if(ADC_NormalModePtr->interrupt_bit_no == bit2INT) //Interrupt happened at bit number 2
    {
      ADC0_SSCTL2_R |= ADC_SSCTL2_IE2;
    }
    else if(ADC_NormalModePtr->interrupt_bit_no == bit3INT) //Interrupt happened at bit number 3
    {
      ADC0_SSCTL2_R |= ADC_SSCTL2_IE3;
    }
    
    
    //Choosing End of sequence will be at which bit//
    if(ADC_NormalModePtr->EOS_bit_no == bit0EOS) //End of sequence at bit number 0
    {
      ADC0_SSCTL2_R |= ADC_SSCTL2_END0;
    }
    else if(ADC_NormalModePtr->EOS_bit_no == bit1EOS) //End of sequence at bit number 1
    {
      ADC0_SSCTL2_R |= ADC_SSCTL2_END1;
    }
    else if(ADC_NormalModePtr->EOS_bit_no == bit2EOS) //End of sequence at bit number 2
    {
      ADC0_SSCTL2_R |= ADC_SSCTL2_END2;
    }
    else if(ADC_NormalModePtr->EOS_bit_no == bit3EOS) //End of sequence at bit number 3
    {
      ADC0_SSCTL2_R |= ADC_SSCTL2_END3;
    }
  }
  
  
  //////////////////Sample Sequence number 3//////////////////////
  else if(ADC_NormalModePtr->SSC_No == ss3)
  {
    ADC0_ACTSS_R &= ~(ADC_ACTSS_ASEN3); //Disabling sample sequencer
    
    if(ADC_NormalModePtr->int_status == enable)  //Enabling the interrupts mask for Sample Sequencer 3
    {
      ADC0_IM_R |= ADC_IM_MASK3;
    }
    
    //Choosing the ADC Trigger Mode//
    if(ADC_NormalModePtr->Trigger == PROCESSOR)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM3_PROCESSOR; //Default trigger mode
    }
    else if(ADC_NormalModePtr->Trigger == COMP0)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM3_COMP0; //Analog comparator 0 trigger mode
    }
    else if(ADC_NormalModePtr->Trigger == COMP1)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM3_COMP1; //Analog comparator 1 trigger mode
    }
    else if(ADC_NormalModePtr->Trigger == EXTERNAL)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM3_EXTERNAL; //External GPIO trigger mode
    }
    else if(ADC_NormalModePtr->Trigger == TIMER)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM3_TIMER; //Timer trigger mode
    }
    else if(ADC_NormalModePtr->Trigger == PWM0)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM3_PWM0; //PWM 0 trigger mode
      if(ADC_NormalModePtr->PWM_module == PWM1_module)
      {
        ADC0_TSSEL_R |= ADC_TSSEL_PS0_1; //Enabling PWN module 1 for PWN gen. 0 cuz PWM module 0 is chosen by default
      }
    }
    else if(ADC_NormalModePtr->Trigger == PWM1)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM3_PWM1; //PWM 1 trigger mode
      if(ADC_NormalModePtr->PWM_module == PWM1_module)
      {
        ADC0_TSSEL_R |= ADC_TSSEL_PS1_1; //Enabling PWN module 1 for PWN gen. 1 cuz PWM module 0 is chosen by default
      }
    }
    else if(ADC_NormalModePtr->Trigger == PWM2)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM3_PWM2; //PWM 2 trigger mode
      if(ADC_NormalModePtr->PWM_module == PWM1_module)
      {
        ADC0_TSSEL_R |= ADC_TSSEL_PS2_1; //Enabling PWN module 1 for PWN gen. 2 cuz PWM module 0 is chosen by default
      }
    }
    else if(ADC_NormalModePtr->Trigger == PWM3)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM3_PWM3; //PWM 3 trigger mode
      if(ADC_NormalModePtr->PWM_module == PWM1_module)
      {
        ADC0_TSSEL_R |= ADC_TSSEL_PS3_1; //Enabling PWN module 1 for PWN gen. 3 cuz PWM module 0 is chosen by default
      }
    }
    else if(ADC_NormalModePtr->Trigger == ALWAYS)
    {
      ADC0_EMUX_R |= ADC_EMUX_EM3_ALWAYS; //Always trigger mode
    }
    
    
    //Choosing Interrupts will be at which bit//
    if(ADC_NormalModePtr->interrupt_bit_no == bit0INT) //Interrupt happened at bit number 0
    {
      ADC0_SSCTL3_R |= ADC_SSCTL3_IE0;
    }
    
    //Choosing End of sequence will be at which bit//
    if(ADC_NormalModePtr->EOS_bit_no == bit0EOS) //End of sequence at bit number 0
    {
      ADC0_SSCTL3_R |= ADC_SSCTL3_END0;
    }
  }
  
  
  //Enabling the Sample sequencer we want//
  if(ADC_NormalModePtr->SSC_No == ss0)
  {
    ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;    //Enabling sample sequencer
  }
  else if(ADC_NormalModePtr->SSC_No == ss1)
  {
    ADC0_ACTSS_R |= ADC_ACTSS_ASEN1;    //Enabling sample sequencer
  }
  else if(ADC_NormalModePtr->SSC_No == ss2)
  {
    ADC0_ACTSS_R |= ADC_ACTSS_ASEN2;    //Enabling sample sequencer
  }
  else if(ADC_NormalModePtr->SSC_No == ss3)
  {
    ADC0_ACTSS_R |= ADC_ACTSS_ASEN3;    //Enabling sample sequencer
  }
}

