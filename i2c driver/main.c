#include "I2C.h"
int main()
{
  i2c_initStruct i2c_initConfig ={standardMode, 20000000, master};
  i2c_init(&i2c_initConfig);
 
  
  i2c_masterMultipleBytesStruct i2c_masterMultipleBytesConfig;
  i2c_masterMultipleBytesConfig.slave_address=1;
  i2c_masterMultipleBytesConfig.data[0]=1;
  i2c_masterMultipleBytesConfig. slave_addressRepeatedStart=2;
  i2c_masterMultipleBytesConfig.repeatedStart= repeatedStartOff;
  i2c_sendMultipleBytes(&i2c_masterMultipleBytesConfig);
  
  return 0;
}
