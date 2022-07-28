#ifndef EE24XX08_H
#define EE24XX08_H

#include "mbed.h"

#define EE24xx08ADDR  0xA0

/** Ee24xx08 class.
 *  I2C eeprom (without functional adress pins) driver
 *  for 24xx00,24xx01,24xx02,24xx04,24xx08,24xx016 device
 
 * Example:
 * @code
 * #include "mbed.h"
 * #include "Ee24xx08.h"
 *
 * Serial ser(USBTX,USBRX);
 * I2C iic(p28,p27);Ee24xx08 eeprom(&iic, &ser);
 *
 * int main() 
 * {
 *    char str[12] = "hello wolrd";
 *
 *     eeprom.write(54,str,12);
 *     wait(1);
 *     eeprom.read(54,str,12);
 *     ser.printf("%s\r\n",str);
 *     
 *     while(1) 
 *     {
 *     }
 * }
 * @endcode
 */  
class Ee24xx08
{
    public:
    /** Create Ee24xx08 instance
    * @param I2C bus connected to eeprom
    */
    Ee24xx08(I2C *i2c);
    
    /**Write byte on eeprom
    * @param addr Byte address in memory
    * @param byte Byte to write in memory
    * @returns 0 if succes
    */   
    bool write(const short  addr, const char byte);
    
    /**Write buffer on eeprom
    * @param addr Buffer start address in memory
    * @param buffer buffer to write in memory
    * @param len number of byte to write in memory
    * @returns 0 if succes
    */     
    bool write(const short  addr, const char* buffer,const int len);
    
    /**Read byte on eeprom
    * @param addr Byte address in memory
    * @param byte Byte to read in memory
    * @returns 0 if succes
    */ 
    bool read(const short  addr, char *byte);
    
    /**Read buffer on eeprom
    * @param addr Buffer start address in memory
    * @param buffer buffer to read in memory
    * @param len number of byte to read in memory
    * @returns 0 if succes
    */ 
    bool read(const short  addr, char* buffer,const int len);
        
    protected:
        I2C *_i2c;
};

#endif