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
void ADC_INIT(const ADC_CONFIG* ADC_CONFIG){

  //Enabling clock to ADC Module 
  
  SYSCTL_RCGCADC_R |= 0x01; //Enabling clock to ADC0
  
  
  if(ADC_CONFIG->ADC_INPUT == 0){
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4; //Enabling clock to PortE;
    GPIO_PORTE_AFSEL_R |= 0x08; //Enabling AFSEL for PE3
    GPIO_PORTE_DEN_R &= ~(0x08); //Disabling Digital function for PE3
    GPIO_PORTE_AMSEL_R |= (0x08); //Disable the analog isolation circuit for PE3
  }
  
  
    if(ADC_CONFIG->ADC_INPUT == 1){
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4; //Enabling clock to PortE;
    GPIO_PORTE_AFSEL_R |= 0x04; //Enabling AFSEL for PE2
    GPIO_PORTE_DEN_R &= ~(0x04); //Disabling Digital function for PE2
    GPIO_PORTE_AMSEL_R |= (0x04); //Disable the analog isolation circuit for PE2
  }
  
    if(ADC_CONFIG->ADC_INPUT == 2){
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4; //Enabling clock to PortE;
    GPIO_PORTE_AFSEL_R |= 0x02; //Enabling AFSEL for PE1
    GPIO_PORTE_DEN_R &= ~(0x02); //Disabling Digital function for PE1
    GPIO_PORTE_AMSEL_R |= (0x02); //Disable the analog isolation circuit for PE1
  }
  
    if(ADC_CONFIG->ADC_INPUT == 3){
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4; //Enabling clock to PortE;
    GPIO_PORTE_AFSEL_R |= 0x01; //Enabling AFSEL for PE0
    GPIO_PORTE_DEN_R &= ~(0x01); //Disabling Digital function for PE0
    GPIO_PORTE_AMSEL_R |= (0x01); //Disable the analog isolation circuit for PE0
  }
  
    if(ADC_CONFIG->ADC_INPUT == 4){
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3; //Enabling clock to PortD;
    GPIO_PORTD_AFSEL_R |= 0x08; //Enabling AFSEL for PD3
    GPIO_PORTD_DEN_R &= ~(0x08); //Disabling Digital function for PD3
    GPIO_PORTD_AMSEL_R |= (0x08); //Disable the analog isolation circuit for PD3
  }
   
  if(ADC_CONFIG->ADC_INPUT == 5){
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3; //Enabling clock to PortD;
    GPIO_PORTD_AFSEL_R |= 0x04; //Enabling AFSEL for PD2
    GPIO_PORTD_DEN_R &= ~(0x04); //Disabling Digital function for PD2
    GPIO_PORTD_AMSEL_R |= (0x04); //Disable the analog isolation circuit for PD2
  }  
   if(ADC_CONFIG->ADC_INPUT == 6){
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3; //Enabling clock to PortD;
    GPIO_PORTD_AFSEL_R |= 0x02; //Enabling AFSEL for PD1
    GPIO_PORTD_DEN_R &= ~(0x02); //Disabling Digital function for PD1
    GPIO_PORTD_AMSEL_R |= (0x02); //Disable the analog isolation circuit for PD1
  }  
  
   if(ADC_CONFIG->ADC_INPUT == 7){
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3; //Enabling clock to PortD;
    GPIO_PORTD_AFSEL_R |= 0x01; //Enabling AFSEL for PD0
    GPIO_PORTD_DEN_R &= ~(0x01); //Disabling Digital function for PD0
    GPIO_PORTD_AMSEL_R |= (0x01); //Disable the analog isolation circuit for PD0
  }  
   if(ADC_CONFIG->ADC_INPUT == 8){
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4; //Enabling clock to PortE;
    GPIO_PORTE_AFSEL_R |= 0x20; //Enabling AFSEL for PE5
    GPIO_PORTE_DEN_R &= ~(0x20); //Disabling Digital function for PE5
    GPIO_PORTE_AMSEL_R |= (0x20); //Disable the analog isolation circuit for PE5
  }  
  if(ADC_CONFIG->ADC_INPUT == 9){
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4; //Enabling clock to PortE;
    GPIO_PORTE_AFSEL_R |= 0x10; //Enabling AFSEL for PE4
    GPIO_PORTE_DEN_R &= ~(0x10); //Disabling Digital function for PE4
    GPIO_PORTE_AMSEL_R |= (0x10); //Disable the analog isolation circuit for PE4
  } 
  
   if(ADC_CONFIG->ADC_INPUT == 10){
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1; //Enabling clock to PortB;
    GPIO_PORTB_AFSEL_R |= 0x10; //Enabling AFSEL for PB4
    GPIO_PORTB_DEN_R &= ~(0x10); //Disabling Digital function for PB4
    GPIO_PORTB_AMSEL_R |= (0x10); //Disable the analog isolation circuit for PB4
  }  
  
  if(ADC_CONFIG->ADC_INPUT == 11){
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1; //Enabling clock to PortB;
    GPIO_PORTB_AFSEL_R |= 0x20; //Enabling AFSEL for PB5
    GPIO_PORTB_DEN_R &= ~(0x20); //Disabling Digital function for PB5
    GPIO_PORTB_AMSEL_R |= (0x20); //Disable the analog isolation circuit for PB5
  }  
  
  
      //SETTING PRIORITIES OF SAMPLE SEQUENCER   
  ADC0_SSPRI_R |= (ADC_CONFIG->SSPRI_0); //Setting priority of SS0
  ADC0_SSPRI_R |= (ADC_CONFIG->SSPRI_1)<<4; //Setting priority of SS1
  ADC0_SSPRI_R |= (ADC_CONFIG->SSPRI_2)<<8; //Setting priority of SS2
  ADC0_SSPRI_R |= (ADC_CONFIG->SSPRI_3)<<12; //Setting priority of SS0
   
}


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

