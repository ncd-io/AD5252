# Usage

This library provides a class for reading and controlling the AD5252. The ad5252.ino file provides a simple use case for the Particle cloud. You can copy all files from the `src` directory into Particle build, or clone this library into Particle Dev.

>Create a new instance of the device
```cpp
AD5252 Potent;
```

>Set I2C address. There are 2 address pins on this device, this function expects a (1) to be sent for each installed jumper (a0, a1).

>***init() must be called after this is set***
```cpp
Potent.setAddress(1,0);
```

>Set the wiper for a particular channel, the channels can be referenced with the constants AD5252_RDAC_1, AD5252_RDAC_3, or AD5252_RDAC_ALL. The value should be 0-255
```cpp
Potent.setWiper(AD5252_RDAC_1, 200);
```

>Issue a quick command to a particular channel. Quick commands can be built by combining the QC constants
```cpp
//Increment channel 1 by 1 step
Potent.quickCommand(AD5252_RDAC_1, AD5252_QC_INCREMENT+AD5252_QC_STEP);
```

>Read the values of both channels, and update their associated properties
```cpp
Potent.readChannels();
int channel_1 = Potent.rdac_1;
int channel_2 = Potent.rdac_3;
```

>Talk to the device using a human readable String
```cpp
//Set RDAC_1 to 90% of it's total allowed value
Potent.talk("Set channel 1 to 90 percent");

//Increment RDAC_3 6 db (quick command)
Potent.talk("Increment rdac 3 6 db");

//Set RDAC_1 to 225
Potent.talk("rdac 1 225");
```
