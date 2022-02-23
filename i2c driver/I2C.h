#ifndef ICU_H_
#define ICU_H_

#include <stdlib.h>
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "std_types.h"
#define numberOfBytes 2

/*******************************************************************************
 *                      Type Definitions                                  *
 *******************************************************************************/
// typedef enum{
//     module0, module1, module2, module3
// } i2c_module;
typedef enum{
    standardMode, fastMode, fastPlusMode
} i2c_speedMode;
typedef enum{
    master,slave
}i2c_mode;
typedef enum{
    repeatedStartOn, repeatedStartOff //the repeated start thing allows the user to switch the state of the controller 
                                        //without losing the bus arbitration, meaning that after it's done transmitting it will become a receiver

}i2c_repeatedStart;
typedef struct{
    //i2c_module module;
    i2c_speedMode i2c_speed;
    uint32 clk_speed; //input the speed in hz
    i2c_mode mode;
    
}i2c_initStruct;
typedef struct{
    uint8_t slave_address;
    uint8_t data[numberOfBytes];
    i2c_repeatedStart repeatedStart;
    uint8_t slave_addressRepeatedStart; //only used when repeated start is on

}i2c_masterMultipleBytesStruct;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
//void I2C_initMaster();
void i2c_sendByte(uint8 slave_address, uint8 byte);
//void i2c_initSLave(i2c_initMasterTransmitMultipleDataStruct* i2c_initMasterTransmitMultiplePtr);
uint8_t i2c_recieveByte(uint8_t slave_address);
void i2c_init(i2c_initStruct* i2c_initPtr);
void i2c_sendMultipleBytes(i2c_masterMultipleBytesStruct* i2c_masterMultipleBytesPtr );
uint8* I2C_recieveMultipleBytes(uint8 slave_address);

#endif
