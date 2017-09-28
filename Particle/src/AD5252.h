#include "spark_wiring_i2c.h"
#include "spark_wiring_constants.h"


#define AD5252_RDAC_1 0x01
#define AD5252_RDAC_3 0x03
#define AD5252_RDAC_ALL 0x08

#define AD5252_QC 0x98

#define AD5252_QC_DEINCREMENT 0x00
#define AD5252_QC_INCREMENT 0x28

#define AD5252_QC_6DB 0x00
#define AD5252_QC_STEP 0x16

// #define AD5252_QC_DEINC_6DB 0x98
// #define AD5252_QC_DEINC_STEP 0xA8

// #define AD5252_QC_INC_6DB 0xC0
// #define AD5252_QC_INC_STEP 0xD0

class AD5252{
public:
    int address = 0x2C;
    void setAddress(int a0, int a1);
    void setWiper(int channel, int value);
    void quickCommand(int command);
    void quickCommand(int channel, int command);
    void init();
    int talk(String cmd);
    void readChannels();
    int rdac_1=0;
    int rdac_2=0;
public:
    void begin();
    void writeByte(int reg, int data);
    void readBuffer(int reg, int *buff, int length);
    int readByte(int reg);
};
