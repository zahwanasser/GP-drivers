#include "ADC.h"

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



/*void ADC_SS_CONFIG(const SS_CONFIG* SS_CONFIG){

  if((SS_CONFIG->SS0_ON)){
    ADC0_ACTSS_R &= ~(SS_CONFIG->SS0_ON); //Disabling SS0 for configuration
    
    //Configuring trigger event for Sample sequencer
    
    if((SS_CONFIG->SS_TRIG_SRC) == 0){
    //Processor Triggered
      ADC0_PSSI_R |= (SS_CONFIG->SS0_ON); //Enabling SS0 
    }
    if((SS_CONFIG->SS_TRIG_SRC) == 1){
    //Analog Comparator 0
    
    }
  }
}*/