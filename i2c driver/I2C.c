#include "I2C.h"
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description : Function to initialize the I2c master
 * assuming speed is 100kps and clk is 20mhz
 * 	1. enable clock for the module
 * 	2. set master mode.
 * 	3. setting up the speed according to the equation
 * 	TPR = (System Clock/(2*(SCL_LP + SCL_HP)SCL_CLK))-1;
    TPR = (20MHz/(2(6+4)*100000))-1;
    TPR = 9.
 * 	4. configure the gpio registers
 * 	    enabling the clk
 * 	    selecting the pins as digital output
 * 	    selecting alternative function
 * 	    select open drain for SDA line
 * 	    choosing the i2c peripheral from the available alt functions
 * 	arguments: void
 * 	returns: void
 *
 */
// void I2C_initMaster()
// {

//         SYSCTL_RCGCI2C_R |= 0x01; /* enable clock to I2C0 */
//         I2C0_MCR_R   |= 0x10; 				/* master mode */
// 		I2C0_MTPR_R = 9; 					//setting up the speed
// 		//gpio configuration
// 		SYSCTL_RCGCGPIO_R |= 0x02; 	/* enable clock to GPIOB */
// 		GPIO_PORTB_DEN_R |= 0x0C; 				//setting the pins as digital output
// 		GPIO_PORTB_AFSEL_R |=0x0C;  			//setting the pins to alternative function
// 		GPIO_PORTB_ODR_R |= 0x08; 				//open drain for SDA
// 		GPIO_PORTB_PCTL_R &=~0X00000FF0;	//setting the pins to I2C module
// 		GPIO_PORTB_PCTL_R |= 0X00000FC0;
		
	
// }
/*
* Description : Function to send a byte, takes slave address and the byte to be send
*               and waits on the byte till it's sent to check on errors
*
  arguments: uint8
*  returns: bool
*
*/
void i2c_sendByte(uint8 slave_address, uint8 byte)
{
    while ( I2C0_MCS_R & I2C_MCS_BUSY); //while the controller is busy do nothing (the controller needs to be idle before anything)
	I2C0_MSA_R &= ~(I2C_MSA_RS); //send not receive
	I2C0_MSA_R = slave_address <<1;
	I2C0_MDR_R  = byte;
	while ( I2C0_MCS_R & I2C_MCS_BUSBSY ); //while the bus is busy do nothing
    I2C0_MCS_R = 0x07;              //to send out a single byte (not a burst)
    while (I2C0_MCS_R & I2C_MCS_BUSY); //polling as long as it's busy
    if(I2C0_MCS_R & I2C_MCS_ERROR) //there was an error
      {
		  I2C0_MIMR_R |=I2C_MIMR_IM ; //generate an interrupt
	  }
    I2C0_MCS_R &=~(I2C_MCS_RUN ); //the controller is idle
	I2C0_MCS_R|= I2C_MCS_STOP;
        
	
}
uint8_t i2c_receiveByte(uint8_t slave_address)
{
	uint8_t data;
	while ( I2C0_MCS_R & I2C_MCS_BUSY); //while the controller is busy do nothing (the controller needs to be idle before anything)
	I2C0_MSA_R |= (I2C_MSA_RS); //receive not send
	I2C0_MSA_R = slave_address <<1;
	while ( I2C0_MCS_R & I2C_MCS_BUSBSY ); //while the bus is busy do nothing
        I2C0_MCS_R = 0x0F;              //to receive a single byte (not a burst) and to send ack after the receieved byte
        
	while (I2C0_MCS_R & I2C_MCS_BUSY); //polling as long as it's busy
	if(I2C0_MCS_R & I2C_MCS_ERROR) //there was an error
      {
		  I2C0_MIMR_R |=I2C_MIMR_IM ; //generate an interrupt
		 
	  }
	  else
	  {
           data=I2C0_MDR_R;

	  }
	  
    I2C0_MCS_R &=~(I2C_MCS_RUN ); //idle
	I2C0_MCS_R|= I2C_MCS_STOP;
	return data;
}
/*
 * Description : Function to initialize the I2c slave
 *
 *  1. enable clock for the module
 *  2. set slave mode.
 *  3. setting the address of the slave
 *
 *  4. configure the gpio registers
 *      enabling the clk
 *      selecting the pins as digital output
 *      selecting alternative function
 *      select open drain for SDA line
 *      choosing the i2c peripheral from the available alt functions
 *  arguments: uint8
 *  returns: void
 *
 */
// void i2c_initSlave(i2c_initMasterTransmitMultipleDataStruct* i2c_initMasterTransmitMultipleConfig)
// {
//     uint8_t TPR; //Timer Period register that is determined by the equation down
// 	/*GPIO configuration */
// 	SYSCTL_RCGCGPIO_R |=SYSCTL_RCGCGPIO_R1;
// 	GPIO_PORTB_DEN_R |= 0x0C;               //setting the pins as digital output
// 	GPIO_PORTB_AFSEL_R |=0x0C;              //setting the pins to alternative function
// 	GPIO_PORTB_ODR_R |= 0x08;               //open drain for SDA
// 	//we won't set the PCTL register for this module because it's already default

// 	SYSCTL_RCGCI2C_R |= SYSCTL_RCGCI2C_R0; //enabling the clk for the module

// 	I2C0_MCR_R &=~(I2C_MCR_MFE); //receive function enable
// 	if (i2c_initMasterTransmitMultipleConfig -> i2c_speed ==0) //standard mode 100khz
// 	{
// 		TPR = (i2c_initMasterTransmitMultipleConfig -> clk_speed /(2*(6 + 4)*100000))-1;
// 	}
// 	else if(i2c_initMasterTransmitMultipleConfig -> i2c_speed ==1) //fast mode 400khz
// 	{
// 		TPR = (i2c_initMasterTransmitMultipleConfig -> clk_speed /(2*(6 + 4)*400000))-1;
// 	}
// 	else if(i2c_initMasterTransmitMultipleConfig -> i2c_speed ==2) //fast mode plus 1Mhz
// 	{
// 		 TPR = (i2c_initMasterTransmitMultipleConfig -> clk_speed /(2*(6 + 4)*1000000))-1;
// 	}
// 	I2C0_MTPR_R = TPR;


	

// }

/*
 * Description : Function to initialize the I2c master
 * 	1. enable clock for the module
 * 	2. set master mode.
 * 	3. setting up the speed according to the equation
 * 	TPR = (System Clock/(2*(SCL_LP + SCL_HP)SCL_CLK))-1;
    TPR = (20MHz/(2(6+4)*100000))-1; (range of 1 to 127).
    TPR = 9.
 * 	4. configure the gpio registers (for module 0 pin 2 and 3 of portb)
 * 	    enabling the clk
 * 	    selecting the pins as digital output
 * 	    selecting alternative function
 * 	    select open drain for SDA line (pin 3)
 * 	    choosing the i2c peripheral from the available alt functions
 * 	arguments: struct containing the mode of operation of the i2c, the clk speed and master or slave operation
 * 	returns: void
 *
 */
void i2c_init(i2c_initStruct* i2c_initConfig)
{
	uint8_t TPR; //Timer Period register that is determined by the equation down
	/*GPIO configuration */
	SYSCTL_RCGCGPIO_R |=SYSCTL_RCGCGPIO_R1;
	GPIO_PORTB_DEN_R |= 0x0C;               //setting the pins as digital output
	GPIO_PORTB_AFSEL_R |=0x0C;              //setting the pins to alternative function
	GPIO_PORTB_ODR_R |= 0x08;               //open drain for SDA
	//we won't set the PCTL register for this module because it's already default

	SYSCTL_RCGCI2C_R |= SYSCTL_RCGCI2C_R0; //enabling the clk for the module
	//choosing master or slave
	if(i2c_initConfig -> mode==0)
	{
		I2C0_MCR_R |=I2C_MCR_MFE; //receive function enable
	}
	else if (i2c_initConfig -> mode==1)
	{
		I2C0_MCR_R &=~(I2C_MCR_MFE); //master function enable
	}
	//choosing the speed of the module
	if (i2c_initConfig -> i2c_speed ==0) //standard mode 100khz
	{
		TPR = (i2c_initConfig -> clk_speed /(2*(6 + 4)*100000))-1;
	}
	else if(i2c_initConfig -> i2c_speed ==1) //fast mode 400khz
	{
		TPR = (i2c_initConfig -> clk_speed /(2*(6 + 4)*400000))-1;
	}
	else if(i2c_initConfig -> i2c_speed ==2) //fast mode plus 1Mhz
	{
		 TPR = (i2c_initConfig -> clk_speed /(2*(6 + 4)*1000000))-1;
	}
	I2C0_MTPR_R = TPR;

}
/*
 * Description : Function to send multiple bytes by the master
 * 
 * 	arguments: slave address and since that the data is made up of 1 byte each time then we have the data as an array of characters
 * 	returns: void

 */
void i2c_sendMultipleBytes(i2c_masterMultipleBytesStruct* i2c_masterMultipleBytesConfig )
{	
	while ( I2C0_MCS_R & I2C_MCS_BUSY); //while the controller is busy do nothing (the controller needs to be idle before anything)
	I2C0_MSA_R &= ~(I2C_MSA_RS); //send not receive
	I2C0_MSA_R = i2c_masterMultipleBytesConfig->slave_address <<1;
	I2C0_MDR_R  = i2c_masterMultipleBytesConfig->data[0];
	while ( I2C0_MCS_R & I2C_MCS_BUSBSY ); //while the bus is busy do nothing
	I2C0_MCS_R = 0x03; //send multiple bytes (burst)  
	while ( I2C0_MCS_R & I2C_MCS_BUSY); //while the controller is busy do nothing (the controller is sending)
		uint8_t i=1;
	 while(!(I2C0_MCS_R & I2C_MCS_ERROR) ) //there was no error 
       {   I2C0_MDR_R  =i2c_masterMultipleBytesConfig->data[i];
		   if(i < numberOfBytes)
			{ 
				I2C0_MCS_R = 0x01; //send the byte
				i++;
				if(!(I2C0_MCS_R & I2C_MCS_ARBLST) ) //if arbitration was not lost
					{
				I2C0_MCS_R = 0x04; //stop sending anything 
					}
				I2C0_MIMR_R |=I2C_MIMR_IM ; //generate an interrupt
				I2C0_MCS_R &=~(I2C_MCS_RUN ); //the controller is idle
			}
			else
			{	
				if(i2c_masterMultipleBytesConfig->repeatedStart == 1) //repeated start is off
				{
					I2C0_MCS_R = 0x05; //send this byte and generate the stop condition
					if(I2C0_MCS_R & I2C_MCS_ERROR) //there's an error in the last byte
					{
					I2C0_MIMR_R |=I2C_MIMR_IM ; //generate an interrupt
					I2C0_MCS_R &=~(I2C_MCS_RUN );
					I2C0_MCS_R|= I2C_MCS_STOP; //the controller is idle
					break;
					}
				else //there was no error in the last byte
				{
					I2C0_MCS_R &=~(I2C_MCS_RUN );
					I2C0_MCS_R|= I2C_MCS_STOP; //the controller is idle
					break;
				}
			}
			else if (i2c_masterMultipleBytesConfig->repeatedStart == 0) //repeated start is on
			{
				I2C0_MCS_R = 0x01; //send the last byte but don't generate a stop condition
				I2C0_MCR_R |=I2C_MCR_MFE; //receive function enable
				
				I2C_recieveMultipleBytes(i2c_masterMultipleBytesConfig->slave_addressRepeatedStart, i2c_masterMultipleBytesConfig->repeatedStart=repeatedStartOff);
			}
			}
			   

	   }	

}

uint8* I2C_recieveMultipleBytes(uint8 slave_address){
  uint8 index = 0; //index of the data to be received
  uint8 RECEIVED_BITS[numberOfBytes];
  I2C0_MSA_R &= ~0XFE;        //clearing the register
  I2C0_MSA_R |= slave_address<<1;     //Placing slave address
  I2C0_MSA_R |= 0x01; //Receiving from slave in this register
  
  
  //Loop to receive all bytes in the Burst being sent
  
  for(index = 0; index<numberOfBytes; index++){
    
  //CHECKING STATE OF BUS
  
  while(I2C0_MCS_R & I2C_MCS_BUSBSY); //Waiting for I2C bus to be not busy
  
  //Once Bus is not busy 
  
  /*In the I2CMCS Register:
  * Bit0 = 1: Master enable
  * Bit1 = 1: Controller generates START
  * Bit3 = 1: Data ACK Enabled
*/
  I2C0_MCS_R = 0b01011;
  
  //READING STARTED
  //CHECKING STATE OF THE BUS 
  
  while(I2C0_MCS_R & I2C_MCS_BUSBSY); //Waiting for I2C bus to be not busy
  
  if(I2C0_MCS_R & I2C_MCS_ERROR){
  //IF AN ERROR OCCURED DURING READING
    if(!(I2C0_MCR_R & I2C_MCS_ARBLST)){
      I2C0_MCS_R |= I2C_MCS_STOP; //Stop receiving
      I2C2_MCS_R &= ~(I2C_MCS_RUN); //Master disable
      I2C0_MCS_R &= ~(I2C_MCS_START); // Controller does not generate START
      I2C0_MCS_R &= ~(I2C_MCS_HS); //Master operates in standard mode
    }
    
    //********************************************ERROR HANDLING SECTION
   I2C0_MIMR_R |= I2C_MIMR_IM; //Interrupt enabled
    
    
  } 
  else if(!(I2C0_MCS_R & I2C_MCS_ERROR)){
  //NO ERROR OCCURED DURING READING
    
    
    if(index == (numberOfBytes - 1)){
    //We reached the max size
      RECEIVED_BITS[index] |= I2C0_MDR_R; //Reading data from I2CMDR Register
      //Bit2 = 1: Generate stop condition
      //Bit3 = 0; Received data is not recognized by master anymore
      
      I2C0_MCS_R = 0b00101;
      
      while(I2C0_MCS_R & I2C_MCS_BUSY); //Waiting till master is not busy
      
      if(I2C0_MCS_R & I2C_MCS_ERROR){
      //Error has occured
        //********************************************ERROR HANDLING SECTION
        
        //Interrupt enable
        I2C0_MIMR_R |= I2C_MIMR_IM; //Interrupt enabled
        
        
      }
      else{
      //No error has occured
      return RECEIVED_BITS;
      }
      
    }
    
    else{
    //A byte in the middle of the burst
    //Index != RECEIVE_SIZE - 1;
      RECEIVED_BITS[index] |= I2C0_MDR_R; //Reading data from I2CMDR Register
      
      //Bit3 = 1; ACK is automatically generated by Master
      I2C0_MCS_R = 0b01001;
    }
    
  }
  
  }
  
  return RECEIVED_BITS;
}
