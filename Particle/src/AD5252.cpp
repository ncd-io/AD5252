#include "AD5252.h"

void AD5252::setAddress(int a0, int a1){
    address |= (a0 + (a1*2));
}

void AD5252::init(){
    begin();
}

void AD5252::setWiper(int channel, int value){
    if(channel == AD5252_RDAC_ALL){
		writeByte(AD5252_RDAC_1, value);
		writeByte(AD5252_RDAC_3, value);
    }else{
		Particle.publish("channel", String(channel));
        writeByte(channel, value);
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

void AD5252::readChannels(){
    rdac_1 = readByte(AD5252_RDAC_1);
    rdac_3 = readByte(AD5252_RDAC_3);
}

int AD5252::talk(String command){
    int channel = 0;
    int op = 0;
    int value = 0;
    int percentage = false;
    int p = command.indexOf(" ");
    bool channel_next = false;
	bool inctype_set = false;

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
            }else if(word.equalsIgnoreCase("db") | word.equalsIgnoreCase("db")){
                op += AD5252_QC_6DB;
				inctype_set = true;
            }else if(word.equalsIgnoreCase("step")){
                op += AD5252_QC_STEP;
				inctype_set = true;
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
    if(op == 0){
        setWiper(channel, value);
    }else{
		if(!inctype_set && value==1){
			op += AD5252_QC_STEP;
		}
        quickCommand(channel, op);
    }
    return 1;
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
