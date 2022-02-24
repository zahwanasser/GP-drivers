#include "pwm.h"



void PWM0_INIT(const PWM_CONFIG* PWM_CONFIG){
  
  
/******************************************************************************
                   INITIALIZING PINS AND CHOSEN MODULE 
*******************************************************************************/

  //PWM0

  SYSCTL_RCGCPWM_R |= SYSCTL_RCGCPWM_R0; //Enabling clock to PWM0
  
  //In the next section we enable the clock to the output ports depending on the
  //Generator and output pin that we've chosen
  if(PWM_CONFIG->PWM_GEN_NUMBER == 0){ 
    //Gen 0
    
      if(PWM_CONFIG->PWM_GEN_PINA_ON == 1){
      //PINA
      SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1; //Enabling clock to PORTB
      GPIO_PORTB_AFSEL_R |= 0x40; //Enabling Alternative function on PB6
      GPIO_PORTB_PCTL_R &= ~(0x0F000000);
      GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB6_M0PWM0; //Making PB6 Output
      GPIO_PORTB_DIR_R |= 0x40; //PB6 is output;
      GPIO_PORTB_DEN_R |= 0x40; //PB6 Digital output enable;
      }
      if(PWM_CONFIG->PWM_GEN_PINB_ON == 1){
      //PINB
      SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1; //Enabling clock to PORTB
      GPIO_PORTB_AFSEL_R |= 0x80; //Enabling Alternative function on PB7
      GPIO_PORTB_PCTL_R &= ~(0xF0000000);
      GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB7_M0PWM1; //Making PB7 Output
      GPIO_PORTB_DIR_R |= 0x80; //PB7 is output;
      GPIO_PORTB_DEN_R |= 0x80; //PB7 Digital enable
      }
    
      
      //Configuring prescaler (IF PWM_PRE_MODE == 1)
      if(PWM_CONFIG->PWM_PRE_MODE == 1){ 
      PWM_PRESCALER_INIT((PWM_CONFIG ->PWM_PRESCALER_VAL)); //Calling function to initialize PWM_PRESCALER
      }
      
      //In this step we ensure that PWM0GEN0 is
      //1) Locally synchronized
      //2) Operating on Count-Down operation
      //3) Is not in "Fault" Mode
      //4) PWM Generator is not yet Enabled
      //5)PWM_COUNT register is not yet cleared and updated
      PWM0_0_CTL_R = 0; 
  
      //This ensures Output on PINA is set (Driven High) when PWM reloads, 
      //Clears when PWM Count value is matched with COMPA value
      if(PWM_CONFIG->PWM_GEN_PINA_ON == 1){
        PWM0_0_GENA_R = 0x0000008C; }
       
      //This ensures Output on PINB is set (Driven High) when PWM reloads, 
      //Clears when PWM Count value is matched with COMPA value
      if(PWM_CONFIG->PWM_GEN_PINB_ON == 1){
        PWM0_0_GENB_R = 0x0000008C; }
      
      //Loading PWMnLOAD register 
      
      PWM0_0_LOAD_R = (PWM_CONFIG->PWM_LOAD);
      
      //Loading PWMnCMPA register
      
      PWM0_0_CMPA_R = (PWM_CONFIG->PWM_COMPA);
      
      //Loading PWMnCMPB register
      PWM0_0_CMPB_R = (PWM_CONFIG->PWM_COMPB); 
      
      //Enabling PWM0 GEN0 Module
      PWM0_0_CTL_R |= 0x01; 
      
      //Enable PinA Output
      if(PWM_CONFIG->PWM_GEN_PINA_ON == 1){
        PWM0_ENABLE_R |= 0x01; }
      //Enable PinB Output 
      if(PWM_CONFIG->PWM_GEN_PINB_ON == 1){
        PWM0_ENABLE_R |= 0X02; }
      
      
  }
  else if(PWM_CONFIG->PWM_GEN_NUMBER == 1){ 
    //Gen 1
    
       if(PWM_CONFIG->PWM_GEN_PINA_ON == 1){
      //PINA
      SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1; //Enabling clock to PORTB
      GPIO_PORTB_AFSEL_R |= 0x10; //Enabling Alternative function on PB4
      GPIO_PORTB_PCTL_R &= ~(0x000F0000);
      GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB4_M0PWM2; //Making PB4 Output
      GPIO_PORTB_DIR_R |= 0x10; //PB4 is output;
      GPIO_PORTB_DEN_R |= 0x10; //PB4 digital enable
      }
      if(PWM_CONFIG->PWM_GEN_PINB_ON == 1){
      //PINB
      SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1; //Enabling clock to PORTB
      GPIO_PORTB_AFSEL_R |= 0x20; //Enabling Alternative function on PB5
      GPIO_PORTB_PCTL_R &= ~(0x000F0000);
      GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB5_M0PWM3; //Making PB5 Output
      GPIO_PORTB_DIR_R |= 0x20; //PB5 is output;
      GPIO_PORTB_DEN_R |= 0x20; //PB5 Digital enable
      }
   
      //Configuring prescaler (IF PWM_PRE_MODE == 1)
      if(PWM_CONFIG->PWM_PRE_MODE == 1){ 
    PWM_PRESCALER_INIT((PWM_CONFIG ->PWM_PRESCALER_VAL)); //Calling function to initialize PWM_PRESCALER
      }
      
      //In this step we ensure that PWM0GEN1 is
      //1) Locally synchronized
      //2) Operating on Count-Down operation
      //3) Is not in "Fault" Mode
      //4) PWM Generator is not yet Enabled
      //5)PWM_COUNT register is not yet cleared and updated
      PWM0_1_CTL_R = 0; 
  
      //This ensures Output on PINA is set (Driven High) when PWM reloads, 
      //Clears when PWM Count value is matched with COMPA value
      if(PWM_CONFIG->PWM_GEN_PINA_ON == 1){
        PWM0_1_GENA_R = 0x0000008C; }
       
      //This ensures Output on PINB is set (Driven High) when PWM reloads, 
      //Clears when PWM Count value is matched with COMPA value
      if(PWM_CONFIG->PWM_GEN_PINB_ON == 1){
        PWM0_1_GENB_R = 0x0000008C; }
      
      //Loading PWMnLOAD register 
      
      PWM0_1_LOAD_R = (PWM_CONFIG->PWM_LOAD);
      
      //Loading PWMnCMPA register
      
      PWM0_1_CMPA_R = (PWM_CONFIG->PWM_COMPA);
      
      //Loading PWMnCMPB register
      PWM0_1_CMPB_R = (PWM_CONFIG->PWM_COMPB); 
      
      //Enabling PWM0 GEN1 Module
      PWM0_1_CTL_R |= 0x01; 
      
      //Enable PinA Output
      if(PWM_CONFIG->PWM_GEN_PINA_ON == 1){
        PWM0_ENABLE_R |= 0x04; }
      //Enable PinB Output 
      if(PWM_CONFIG->PWM_GEN_PINB_ON == 1){
        PWM0_ENABLE_R |= 0X08; }
      
      
      
  }
  else if(PWM_CONFIG->PWM_GEN_NUMBER == 2){ 
    //Gen 2
    
       if(PWM_CONFIG->PWM_GEN_PINA_ON == 1){
      //PINA
      SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4; //Enabling clock to PORTE
      GPIO_PORTE_AFSEL_R |= 0x10; //Enabling Alternative function on PE4
      GPIO_PORTE_PCTL_R &= ~(0x000F0000);
      GPIO_PORTE_PCTL_R |= GPIO_PCTL_PE4_M0PWM4; //Making PE4 Output
      GPIO_PORTE_DIR_R |= 0x10; //PE4 is output;
      GPIO_PORTE_DEN_R |= 0x10; //PE4 Digital enable
      }
      if(PWM_CONFIG->PWM_GEN_PINB_ON == 1){
      //PINB
      SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4; //Enabling clock to PORTB
      GPIO_PORTE_AFSEL_R |= 0x20; //Enabling Alternative function on PE5
      GPIO_PORTE_PCTL_R &= ~(0x00F00000);
      GPIO_PORTE_PCTL_R |= GPIO_PCTL_PE5_M0PWM5; //Making PE5 Output
      GPIO_PORTE_DIR_R |= 0x20; //PE5 is output;
      GPIO_PORTE_DEN_R |= 0x20; //PE5 Digital enable
      }
      
      //Configuring prescaler (IF PWM_PRE_MODE == 1)
      if(PWM_CONFIG->PWM_PRE_MODE == 1){ 
    PWM_PRESCALER_INIT((PWM_CONFIG ->PWM_PRESCALER_VAL)); //Calling function to initialize PWM_PRESCALER
      }
      
      //In this step we ensure that PWM0GEN0 is
      //1) Locally synchronized
      //2) Operating on Count-Down operation
      //3) Is not in "Fault" Mode
      //4) PWM Generator is not yet Enabled
      //5)PWM_COUNT register is not yet cleared and updated
      PWM0_2_CTL_R = 0; 
  
      //This ensures Output on PINA is set (Driven High) when PWM reloads, 
      //Clears when PWM Count value is matched with COMPA value
      if(PWM_CONFIG->PWM_GEN_PINA_ON == 1){
        PWM0_2_GENA_R = 0x0000008C; }
       
      //This ensures Output on PINB is set (Driven High) when PWM reloads, 
      //Clears when PWM Count value is matched with COMPA value
      if(PWM_CONFIG->PWM_GEN_PINB_ON == 1){
        PWM0_2_GENB_R = 0x0000008C; }
      
      //Loading PWMnLOAD register 
      
      PWM0_2_LOAD_R = (PWM_CONFIG->PWM_LOAD);
      
      //Loading PWMnCMPA register
      
      PWM0_2_CMPA_R = (PWM_CONFIG->PWM_COMPA);
      
      //Loading PWMnCMPB register
      PWM0_2_CMPB_R = (PWM_CONFIG->PWM_COMPB); 
      
      //Enabling PWM0 GEN0 Module
      PWM0_2_CTL_R |= 0x01; 
      
      //Enable PinA Output
      if(PWM_CONFIG->PWM_GEN_PINA_ON == 1){
        PWM0_ENABLE_R |= 0x10; }
      //Enable PinB Output 
      if(PWM_CONFIG->PWM_GEN_PINB_ON == 1){
        PWM0_ENABLE_R |= 0X20; }
      
  }
  else if(PWM_CONFIG->PWM_GEN_NUMBER == 3){ 
    //Gen 3
    
       if(PWM_CONFIG->PWM_GEN_PINA_ON == 1){
       //PINA
      SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3; //Enabling clock to PORTD
      GPIO_PORTD_AFSEL_R |= 0x01; //Enabling Alternative function on PD0
      GPIO_PORTD_PCTL_R &= ~(0x0000000F);
      GPIO_PORTD_PCTL_R |= GPIO_PCTL_PD0_M0PWM6; //Making PD0 Output
      GPIO_PORTD_DIR_R |= 0x01; //PD0 is output;
      GPIO_PORTD_DEN_R |= 0x01; //PD0 Digital enable
      }
      if(PWM_CONFIG->PWM_GEN_PINB_ON == 1){
      //PINB
      SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3; //Enabling clock to PORTD
      GPIO_PORTD_AFSEL_R |= 0x02; //Enabling Alternative function on PD1
      GPIO_PORTD_PCTL_R &= ~(0x000000F0);
      GPIO_PORTD_PCTL_R |= GPIO_PCTL_PD1_M0PWM7; //Making PD1 Output
      GPIO_PORTD_DIR_R |= 0x02; //PD1 is output;
      GPIO_PORTD_DEN_R |= 0x02; //PD1 Digital enable
      }
      
      //Configuring prescaler (IF PWM_PRE_MODE == 1)
      if(PWM_CONFIG->PWM_PRE_MODE == 1){ 
      PWM_PRESCALER_INIT((PWM_CONFIG ->PWM_PRESCALER_VAL)); //Calling function to initialize PWM_PRESCALER
      }
      
      //In this step we ensure that PWM0GEN2 is
      //1) Locally synchronized
      //2) Operating on Count-Down operation
      //3) Is not in "Fault" Mode
      //4) PWM Generator is not yet Enabled
      //5)PWM_COUNT register is not yet cleared and updated
      PWM0_3_CTL_R = 0; 
  
      //This ensures Output on PINA is set (Driven High) when PWM reloads, 
      //Clears when PWM Count value is matched with COMPA value
      if(PWM_CONFIG->PWM_GEN_PINA_ON == 1){
        PWM0_3_GENA_R = 0x0000008C; }
       
      //This ensures Output on PINB is set (Driven High) when PWM reloads, 
      //Clears when PWM Count value is matched with COMPA value
      if(PWM_CONFIG->PWM_GEN_PINB_ON == 1){
        PWM0_3_GENB_R = 0x0000008C; }
      
      //Loading PWMnLOAD register 
      
      PWM0_3_LOAD_R = (PWM_CONFIG->PWM_LOAD);
      
      //Loading PWMnCMPA register
      
      PWM0_3_CMPA_R = (PWM_CONFIG->PWM_COMPA);
      
      //Loading PWMnCMPB register
      PWM0_3_CMPB_R = (PWM_CONFIG->PWM_COMPB); 
      
      //Enabling PWM0 GEN2 Module
      PWM0_3_CTL_R |= 0x01; 
      
      //Enable PinA Output
      if(PWM_CONFIG->PWM_GEN_PINA_ON == 1){
        PWM0_ENABLE_R |= 0x40; }
      //Enable PinB Output 
      if(PWM_CONFIG->PWM_GEN_PINB_ON == 1){
        PWM0_ENABLE_R |= 0X80; }
      
      
  }
  
}


void PWM1_INIT(const PWM_CONFIG* PWM_CONFIG){

 //PWM1ss
  
      SYSCTL_RCGCPWM_R |= SYSCTL_RCGCPWM_R1; //Enabling clock to PWM1
      if(PWM_CONFIG->PWM_GEN_NUMBER == 0){
      
      if(PWM_CONFIG->PWM_GEN_PINA_ON == 1){
          //PINA
          SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3; //Enabling clock to PORTD
          GPIO_PORTD_AFSEL_R |= 0x01; //Enabling Alternative function on PD0
          GPIO_PORTD_PCTL_R &= ~(0x0000000F);
          GPIO_PORTD_PCTL_R |= GPIO_PCTL_PD0_M1PWM0; //Making PD0 Output
          GPIO_PORTD_DIR_R |= 0x01; //PD0 is output;
          GPIO_PORTD_DEN_R |= 0x01; //PD0 Digital enable
          }
       if(PWM_CONFIG->PWM_GEN_PINB_ON == 1){
          //PINB
          SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3; //Enabling clock to PORTD
          GPIO_PORTD_AFSEL_R |= 0x02; //Enabling Alternative function on PD1
          GPIO_PORTD_PCTL_R &= ~(0x000000F0);
          GPIO_PORTD_PCTL_R |= GPIO_PCTL_PD1_M1PWM1; //Making PD1 Output
          GPIO_PORTD_DIR_R |= 0x02; //PD1 is output;
          GPIO_PORTD_DEN_R |= 0x02; //PD1 Digital enable
          }
       //Configuring prescaler (IF PWM_PRE_MODE == 1)
      if(PWM_CONFIG->PWM_PRE_MODE == 1){ 
      PWM_PRESCALER_INIT((PWM_CONFIG ->PWM_PRESCALER_VAL)); //Calling function to initialize PWM_PRESCALER
      }
      
      //In this step we ensure that PWM0GEN0 is
      //1) Locally synchronized
      //2) Operating on Count-Down operation
      //3) Is not in "Fault" Mode
      //4) PWM Generator is not yet Enabled
      //5)PWM_COUNT register is not yet cleared and updated
      PWM1_0_CTL_R = 0; 
  
      //This ensures Output on PINA is set (Driven High) when PWM reloads, 
      //Clears when PWM Count value is matched with COMPA value
      if(PWM_CONFIG->PWM_GEN_PINA_ON == 1){
        PWM1_0_GENA_R = 0x0000008C; }
       
      //This ensures Output on PINB is set (Driven High) when PWM reloads, 
      //Clears when PWM Count value is matched with COMPA value
      if(PWM_CONFIG->PWM_GEN_PINB_ON == 1){
        PWM1_0_GENB_R = 0x0000008C; }
      
      //Loading PWMnLOAD register 
      
      PWM1_0_LOAD_R = (PWM_CONFIG->PWM_LOAD);
      
      //Loading PWMnCMPA register
      
      PWM1_0_CMPA_R = (PWM_CONFIG->PWM_COMPA);
      
      //Loading PWMnCMPB register
      PWM1_0_CMPB_R = (PWM_CONFIG->PWM_COMPB); 
      
      //Enabling PWM1 GEN0 Module
      PWM1_0_CTL_R |= 0x01; 
      
      //Enable PinA Output
      if(PWM_CONFIG->PWM_GEN_PINA_ON == 1){
        PWM1_ENABLE_R |= 0x01; }
      //Enable PinB Output 
      if(PWM_CONFIG->PWM_GEN_PINB_ON == 1){
        PWM1_ENABLE_R |= 0X02; }
      
      }
      else if(PWM_CONFIG->PWM_GEN_NUMBER == 1){ 
        //Gen 1
        
          if(PWM_CONFIG->PWM_GEN_PINA_ON == 1){
          //PINA
          SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0; //Enabling clock to PORTA
          GPIO_PORTA_AFSEL_R |= 0x40; //Enabling Alternative function on PA6
          GPIO_PORTA_PCTL_R &= ~(0x0F000000);
          GPIO_PORTA_PCTL_R |= GPIO_PCTL_PA6_M1PWM2; //Making PA6 Output
          GPIO_PORTA_DIR_R |= 0x40; //PA6 is output;
          GPIO_PORTA_DEN_R |= 0x40; //PA6 Digital enable
          }
          if(PWM_CONFIG->PWM_GEN_PINB_ON == 1){
          //PINB
          SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0; //Enabling clock to PORTA
          GPIO_PORTA_AFSEL_R |= 0x80; //Enabling Alternative function on PA7
          GPIO_PORTA_PCTL_R &= ~(0xF0000000);
          GPIO_PORTA_PCTL_R |= GPIO_PCTL_PA7_M1PWM3; //Making PA7 Output
          GPIO_PORTA_DIR_R |= 0x80; //PA7 is output;
          GPIO_PORTA_DEN_R |= 0x80; //PA7 Digital enable
          }
                 //Configuring prescaler (IF PWM_PRE_MODE == 1)
      if(PWM_CONFIG->PWM_PRE_MODE == 1){ 
      PWM_PRESCALER_INIT((PWM_CONFIG ->PWM_PRESCALER_VAL)); //Calling function to initialize PWM_PRESCALER
      }
      
      //In this step we ensure that PWM0GEN0 is
      //1) Locally synchronized
      //2) Operating on Count-Down operation
      //3) Is not in "Fault" Mode
      //4) PWM Generator is not yet Enabled
      //5)PWM_COUNT register is not yet cleared and updated
      PWM1_1_CTL_R = 0; 
  
      //This ensures Output on PINA is set (Driven High) when PWM reloads, 
      //Clears when PWM Count value is matched with COMPA value
      if(PWM_CONFIG->PWM_GEN_PINA_ON == 1){
        PWM1_1_GENA_R = 0x0000008C; }
       
      //This ensures Output on PINB is set (Driven High) when PWM reloads, 
      //Clears when PWM Count value is matched with COMPA value
      if(PWM_CONFIG->PWM_GEN_PINB_ON == 1){
        PWM1_1_GENB_R = 0x0000008C; }
      
      //Loading PWMnLOAD register 
      
      PWM1_1_LOAD_R = (PWM_CONFIG->PWM_LOAD);
      
      //Loading PWMnCMPA register
      
      PWM1_1_CMPA_R = (PWM_CONFIG->PWM_COMPA);
      
      //Loading PWMnCMPB register
      PWM1_1_CMPB_R = (PWM_CONFIG->PWM_COMPB); 
      
      //Enabling PWM1 GEN1 Module
      PWM1_1_CTL_R |= 0x01; 
      
      //Enable PinA Output
      if(PWM_CONFIG->PWM_GEN_PINA_ON == 1){
        PWM1_ENABLE_R |= 0x04; }
      //Enable PinB Output 
      if(PWM_CONFIG->PWM_GEN_PINB_ON == 1){
        PWM1_ENABLE_R |= 0X08; }
      }
      else if(PWM_CONFIG->PWM_GEN_NUMBER == 2){ 
        //Gen 2
        
           if(PWM_CONFIG->PWM_GEN_PINA_ON == 1){
          //PINA
          SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5; //Enabling clock to PORTF
          GPIO_PORTF_AFSEL_R |= 0x01; //Enabling Alternative function on PF0
          GPIO_PORTF_PCTL_R &= ~(0x0000000F);
          GPIO_PORTF_PCTL_R |= GPIO_PCTL_PF0_M1PWM4; //Making PF0 Output
          GPIO_PORTF_DIR_R |= 0x01; //PF0 is output;
          GPIO_PORTF_DEN_R |= 0x01; //PF0 Digital enable
          }
          if(PWM_CONFIG->PWM_GEN_PINB_ON == 1){
          //PINB
          SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5; //Enabling clock to PORTF
          GPIO_PORTF_AFSEL_R |= 0x02; //Enabling Alternative function on PF1
          GPIO_PORTF_PCTL_R &= ~(0x000000F0);
          GPIO_PORTF_PCTL_R |= GPIO_PCTL_PF1_M1PWM5; //Making PF1 Output
          GPIO_PORTF_DIR_R |= 0x02; //PF1 is output;
          GPIO_PORTF_DEN_R |= 0x02; //PF1 Digital enable
          }
                 //Configuring prescaler (IF PWM_PRE_MODE == 1)
      if(PWM_CONFIG->PWM_PRE_MODE == 1){ 
      PWM_PRESCALER_INIT((PWM_CONFIG ->PWM_PRESCALER_VAL)); //Calling function to initialize PWM_PRESCALER
      }
      
      //In this step we ensure that PWM0GEN0 is
      //1) Locally synchronized
      //2) Operating on Count-Down operation
      //3) Is not in "Fault" Mode
      //4) PWM Generator is not yet Enabled
      //5)PWM_COUNT register is not yet cleared and updated
      PWM1_2_CTL_R = 0; 
  
      //This ensures Output on PINA is set (Driven High) when PWM reloads, 
      //Clears when PWM Count value is matched with COMPA value
      if(PWM_CONFIG->PWM_GEN_PINA_ON == 1){
        PWM1_2_GENA_R = 0x0000008C; }
       
      //This ensures Output on PINB is set (Driven High) when PWM reloads, 
      //Clears when PWM Count value is matched with COMPA value
      if(PWM_CONFIG->PWM_GEN_PINB_ON == 1){
        PWM1_2_GENB_R = 0x0000008C; }
      
      //Loading PWMnLOAD register 
      
      PWM1_2_LOAD_R = (PWM_CONFIG->PWM_LOAD);
      
      //Loading PWMnCMPA register
      
      PWM1_2_CMPA_R = (PWM_CONFIG->PWM_COMPA);
      
      //Loading PWMnCMPB register
      PWM1_2_CMPB_R = (PWM_CONFIG->PWM_COMPB); 
      
      //Enabling PWM1 GEN2 Module
      PWM1_2_CTL_R |= 0x01; 
      
      //Enable PinA Output
      if(PWM_CONFIG->PWM_GEN_PINA_ON == 1){
        PWM1_ENABLE_R |= 0x10; }
      //Enable PinB Output 
      if(PWM_CONFIG->PWM_GEN_PINB_ON == 1){
        PWM1_ENABLE_R |= 0X20; }
      }
      else if(PWM_CONFIG->PWM_GEN_NUMBER == 3){ 
        //Gen 3
        
           if(PWM_CONFIG->PWM_GEN_PINA_ON == 1){
           //PINA ENABLE
          SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5; //Enabling clock to PORTF
          GPIO_PORTF_AFSEL_R |= 0x04; //Enabling Alternative function on PF2
          GPIO_PORTF_PCTL_R &= ~(0x00000F00);
          GPIO_PORTF_PCTL_R |= GPIO_PCTL_PF2_M1PWM6; //Making PF2 Output
          GPIO_PORTF_DIR_R |= 0x04; //PF2 is output;
          GPIO_PORTF_DEN_R |= 0x04; //PF2 Digital enable
          }
          if(PWM_CONFIG->PWM_GEN_PINB_ON == 1){
          //PINB ENABLE
          SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5; //Enabling clock to PORTF
          GPIO_PORTF_AFSEL_R |= 0x08; //Enabling Alternative function on PF3
          GPIO_PORTF_PCTL_R &= ~(0x0000F000);
          GPIO_PORTF_PCTL_R |= GPIO_PCTL_PF3_M1PWM7; //Making PF3 Output
          GPIO_PORTF_DIR_R |= 0x08; //PF3 is output;
          GPIO_PORTF_DEN_R |= 0x08; //PF3 Digital enable
          
          }
          
                 //Configuring prescaler (IF PWM_PRE_MODE == 1)
      if(PWM_CONFIG->PWM_PRE_MODE == 1){ 
      PWM_PRESCALER_INIT((PWM_CONFIG ->PWM_PRESCALER_VAL)); //Calling function to initialize PWM_PRESCALER
      }
      
      //In this step we ensure that PWM0GEN0 is
      //1) Locally synchronized
      //2) Operating on Count-Down operation
      //3) Is not in "Fault" Mode
      //4) PWM Generator is not yet Enabled
      //5)PWM_COUNT register is not yet cleared and updated
      PWM1_3_CTL_R = 0; 
  
      //This ensures Output on PINA is set (Driven High) when PWM reloads, 
      //Clears when PWM Count value is matched with COMPA value
      if(PWM_CONFIG->PWM_GEN_PINA_ON == 1){
        PWM1_3_GENA_R = 0x0000008C; }
       
      //This ensures Output on PINB is set (Driven High) when PWM reloads, 
      //Clears when PWM Count value is matched with COMPA value
      if(PWM_CONFIG->PWM_GEN_PINB_ON == 1){
        PWM1_3_GENB_R = 0x0000008C; }
      
      //Loading PWMnLOAD register 
      
      PWM1_3_LOAD_R = (PWM_CONFIG->PWM_LOAD);
      
      //Loading PWMnCMPA register
      
      PWM1_3_CMPA_R = (PWM_CONFIG->PWM_COMPA);
      
      //Loading PWMnCMPB register
      PWM1_3_CMPB_R = (PWM_CONFIG->PWM_COMPB); 
      
      //Enabling PWM1 GEN3 Module
      PWM1_3_CTL_R |= 0x01; 
      
      //Enable PinA Output
      if(PWM_CONFIG->PWM_GEN_PINA_ON == 1){
        PWM1_ENABLE_R |= 0x40; }
      //Enable PinB Output 
      if(PWM_CONFIG->PWM_GEN_PINB_ON == 1){
        PWM1_ENABLE_R |= 0X80;}
          
      }


}






void PWM_PRESCALER_INIT(uint16 PWM_PRESCALER_VAL){
    SYSCTL_RCC_R |= SYSCTL_RCC_USEPWMDIV; //Enable PRESCALER
        
        //PRESCALER VALUE
        if(PWM_PRESCALER_VAL == 0){
        SYSCTL_RCC_R |= SYSCTL_RCC_PWMDIV_2; //Divide system clock by 2
        }
        else if(PWM_PRESCALER_VAL == 1){
        SYSCTL_RCC_R |= SYSCTL_RCC_PWMDIV_4; //Divide system clock by 4
        }
        else if(PWM_PRESCALER_VAL == 2){
        SYSCTL_RCC_R |= SYSCTL_RCC_PWMDIV_8; //Divide system clock by 8
        }
        else if(PWM_PRESCALER_VAL == 3){
        SYSCTL_RCC_R |= SYSCTL_RCC_PWMDIV_16; //Divide system clock by 16
        }
        else if(PWM_PRESCALER_VAL == 4){
        SYSCTL_RCC_R |= SYSCTL_RCC_PWMDIV_32; //Divide system clock by 32
        }
        else if( (PWM_PRESCALER_VAL == 5) || (PWM_PRESCALER_VAL == 6) || (PWM_PRESCALER_VAL == 7) ){
        SYSCTL_RCC_R |= SYSCTL_RCC_PWMDIV_64; //Divide system clock by 64
        }
};


void PWM0_OFF(){

SYSCTL_RCGCPWM_R &= ~(SYSCTL_RCGCPWM_R0); //Disabling PWM0 Clock
}


void PWM1_OFF(){
  
SYSCTL_RCGCPWM_R &= ~(SYSCTL_RCGCPWM_R1); //Disabling PWM1 Clock

}