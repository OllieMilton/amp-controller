#ifndef AMPLIFIER_H
#define AMPLIFIER_H

#include <string>
#include <mbed.h>
#include "CD22M3494.h"
#include "DigiPot.h"

const string DEST_ASC   = "Amplifer";
const string RADIO      = "Radio";
const string SQUEEZE    = "SqueezeBox";
const string AUX1       = "AUX1";
const string AUX2       = "AUX2";

struct AmpConf {
    PinName ampPower, x0, x1, x2, x3, y0, y1, y2, data, strobe, reset, miso, mosi, clk, cs, speakers;
};

class Amplifier {
    
    public:
        Amplifier(AmpConf ampConf);
        void powerOn();
        void powerOff();
        void muteInput();
        void unmuteInput();
        void volumeUp();
        void volumeDown();
        bool routeSource(string source);
        Association* getAssociation(string name);
        string getSources();
    private:
        void muteSpeakers();
        void unmuteSpeakers();
        string assoc;
        const string* sources;
        CD22M3494 *switcher;
        DigitalOut *ampPower;
        DigitalOut *speakers;
        DigiPot *volume;
};

#endif