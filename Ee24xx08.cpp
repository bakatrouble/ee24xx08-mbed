#include "Ee24xx08.h"


//***********************************/************************************
//                         Constructors                                 //
//***********************************/************************************
Ee24xx08::Ee24xx08(I2C *i2c) : _i2c(i2c) {
}

//***********************************/************************************
//                             Public Methods                           //
//***********************************/************************************      
bool Ee24xx08::write(const short addr, const char byte) {
    char i2cBuffer[2];
    i2cBuffer[0] = (unsigned char) addr; //8lsb of address word
    i2cBuffer[1] = byte;                //byte to write
    return _i2c->write(EE24xx08ADDR | ((addr >> 7) & 0X0E), i2cBuffer, 2);  //i2c adress + page adress & data send
}

bool Ee24xx08::write(const short addr, const char *buffer, const int len) {
    MBED_ASSERT(len % 0x10 == 0);

    char i2cBuffer[17];
    i2cBuffer[0] = (unsigned char) addr;

    int ret;
    for (int page=0; page < len; page += 0x10) {
        memcpy(i2cBuffer + 1, buffer + page, 0x10);
        ret = _i2c->write(EE24xx08ADDR | ((addr >> 7) & 0X0E), i2cBuffer, 17);
        if (ret)
            break;
    }
    return ret;
}

bool Ee24xx08::read(const short addr, char *byte) {
    if (_i2c->write(EE24xx08ADDR | ((addr >> 7) & 0X0E), (char *) &addr, 1, true)) {
        return true;
    }
    return _i2c->read(EE24xx08ADDR | ((addr >> 7) & 0X0E), byte, 1);
}

bool Ee24xx08::read(const short addr, char *buffer, const int len) {
    MBED_ASSERT(len % 0x10 == 0);

    int ret;
    for (int page=0; page < len; page += 0x10) {
        char pageAddr = addr + page;
        ret = _i2c->write(EE24xx08ADDR | ((addr >> 7) & 0X0E), &pageAddr, 1, true);
        if (ret)
            return true;
        ret = _i2c->read(EE24xx08ADDR | ((addr >> 7) & 0X0E), buffer + page, 0x10);
        if (ret)
            return true;
    }
    return false;
}
