#include "spark_wiring_i2c.h"
#include "spark_wiring_constants.h"
#include "Particle.h"


#define AD5252_RDAC_1 0x01
#define AD5252_RDAC_3 0x03
#define AD5252_RDAC_ALL 0x08

#define AD5252_QC 0x98

#define AD5252_QC_DEINCREMENT 0x00
#define AD5252_QC_INCREMENT 0x28

#define AD5252_QC_6DB 0x00
#define AD5252_QC_STEP 0x16

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
    int rdac_3=0;
public:
    void begin();
    void writeByte(int reg, int data);
    int readByte(int reg);
};
