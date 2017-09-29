// This #include statement was automatically added by the Particle IDE.
#include "AD5252.h"

AD5252 pot;

void setup() {
    pot.init();
    Particle.function("potTalk", &AD5252::talk, &pot);
    Particle.variable("RDAC_1", pot.rdac_1);
    Particle.variable("RDAC_3", pot.rdac_3);
}

void loop() {
    pot.readChannels();
}
