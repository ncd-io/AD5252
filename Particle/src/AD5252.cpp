#include "AD5252.h"

void AD5252::setAddress(int a0, int a1){
    address |= (a0 + (a1*2));
}

void AD5252::init(){
    begin();
}

void AD5252::setWiper(int channel, int value){
    if(channel == AD5252_RDAC_ALL){
        setWiper(AD5252_RDAC_1, value);
        setWiper(AD5252_RDAC_3, value);
    }else{
        writeByte(AD5252_RDAC_1, value);
    }
}

void AD5252::quickCommand(int command){
    quickCommand(AD5252_RDAC_ALL, command);
}

void AD5252::quickCommand(int channel, int command){
    readByte(channel + command);
}

void AD5252::begin(){
    if(!Wire.isEnabled()){
        Wire.begin();
    }
}

void AD5252::writeByte(int reg, int data){
    Wire.beginTransmission(address);
    Wire.write(reg);
    if(data < 256) Wire.write(data);
    Wire.endTransmission();
}

int AD5252::readByte(int reg){
    writeByte(reg, 256);
    Wire.requestFrom(address, 1);
    return Wire.read();
}

void AD5252::readBuffer(int reg, int *buff, int len){
    writeByte(reg, 256);
    Wire.requestFrom(address, len);
    for(int i=0;i<len;i++){
        buff[i] = Wire.read();
    }
}

void AD5252::readChannels(){
    int buff[2];
    readBuffer(AD5252_RDAC_1, buff, 2);
    rdac_1 = buff[0];
    rdac_2 = buff[1];
}

int AD5252::talk(String command){
    int channel = 0;
    int op = 0;
    int value = 0;
    int percentage = false;
    int p = command.indexOf(" ");
    bool channel_next = false;
    
    String word;
    if(p > -1){
        while(command.length() > 0){
            if (p > -1){
                word = command.substring(0, p);
                command = command.substring(p+1);
                p = command.indexOf(" ");
            }else{
                word = command;
                command = "";
            }
            if(word.equalsIgnoreCase("channel") || word.equalsIgnoreCase("rdac")){
                channel_next = true;
            }else if(word.equalsIgnoreCase("all")){
                channel = AD5252_RDAC_ALL;
            }else if(word.equalsIgnoreCase("percent")){
                percentage = true;
            }else if(word.equalsIgnoreCase("increment")){
                op += AD5252_QC;
                op += AD5252_QC_INCREMENT;
            }else if(word.equalsIgnoreCase("deincrement")){
                op += AD5252_QC;
                op += AD5252_QC_DEINCREMENT;
            }else if(word.equalsIgnoreCase("db")){
                op += AD5252_QC_6DB;
            }else if(word.equalsIgnoreCase("step")){
                op += AD5252_QC_STEP;
            }else{
                int test = word.toInt();
                if(test > 0){
                    if(channel_next){
                        channel = test == 1 ? AD5252_RDAC_1 : AD5252_RDAC_3;
                        channel_next = false;
                    }else{
                        value = test;
                    }
                }
            }
        }
    }
    if(percentage) value *= 2.56;
    String message = String(channel);
    message.concat(" ");
    if(op == 0){
        message.concat("setWiper");
        message.concat(" ");
        message.concat(value);
        setWiper(channel, value);
    }else{
        message.concat("quickCommand");
        message.concat(" ");
        message.concat(op);
        quickCommand(channel, op);
    }
    return 1;
}
