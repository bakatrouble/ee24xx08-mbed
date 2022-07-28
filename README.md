# ee24xx08-mbed

## Original code
https://os.mbed.com/users/mederic/code/Ee24xx08/

## Changes
* Reading/writing large chunks of data by 16-byte pages, please make sure that buffers are padded

## Example
```c++
#include <mbed.h>
#include <Ee24xx08.h>

I2C i2c(I2C_SDA, I2C_SCL);
Ee24xx08 eeprom(&i2c);

struct data_t {
    uint8_t a;
    uint8_t b;
} __attribute__((aligned (0x10)));  // alignment for GCC, change for other compilers

data_t write_buf = { 0xF0, 0x0D };
data_t read_buf = {};

int main() {
    int ret;
    uint8_t b;
    
    ret = eeprom.write(0x00, &write_buf, sizeof(write_buf));
    if (ret)
        error("buf write error");
    printf("buffer written\r\n");
    ret = eeprom.read(0x00, &read_buf, sizeof(read_buf));
    if (ret)
        error("buf read error");
    printf("buffer read back\r\n");
    printf("a = %d\r\nb = %d\r\n", read_buf.a, read_buf.b);
    
    ret = eeprom.write(0xDE, 0xAD);
    if (ret)
        error("byte write error");
    printf("byte written\r\n");
    ret = eeprom.read(0xDE, &b);
    if (ret)
        error("byte read error");
    printf("byte read back: 0x%02X\r\n", b);
}
```