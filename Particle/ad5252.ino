// This #include statement was automatically added by the Particle IDE.
#include "AD5252.h"

AD5252 pot;

void setup() {
    pot.init();
    Particle.function("potTalk", &AD5252::talk, &pot);
    Particle.variable("RDAC_1", pot.rdac_1);
    Particle.variable("RDAC_2", pot.rdac_2);
}

void loop() {
    pot.readChannels();
}
