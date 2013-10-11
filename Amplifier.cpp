#include "Amplifier.h"

Amplifier::Amplifier(AmpConf ampConf) {
    sources = new string(RADIO+","+SQUEEZE+","+AUX1+","+AUX2);
    switcher = new CD22M3494(ampConf.x0, 
        ampConf.x1, 
        ampConf.x2, 
        ampConf.x3, 
        ampConf.y0, 
        ampConf.y1, 
        ampConf.y2, 
        ampConf.data, 
        ampConf.strobe, 
        ampConf.reset);
    switcher->associate(DEST_ASC, Y0, Y1);
    switcher->associate(RADIO, X0, X1);
    switcher->associate(SQUEEZE, X6, X7);
    switcher->associate(AUX1, X2, X3);
    switcher->associate(AUX2, X4, X5);
    ampPower = new DigitalOut(ampConf.ampPower);
    volume = new DigiPot(ampConf.miso, ampConf.mosi, ampConf.clk, ampConf.cs);
    speakers = new DigitalOut(ampConf.speakers);
    assoc = "";
}

void Amplifier::powerOn() {
    // first mute the input incase we already have a signal
    // this prevents the amp from overloading while the speakers are disconnected.
    muteInput();
    muteSpeakers();
    ampPower->write(1);
    unmuteSpeakers();
    unmuteInput();
}

void Amplifier::powerOff() {
    // first mute the input incase we already have a signal
    // this prevents the amp from overloading while the speakers are disconnected.
    muteInput();
    muteSpeakers();
    ampPower->write(0);
}

void Amplifier::muteInput() {
    volume->mute();
}

void Amplifier::unmuteInput() {
    volume->unmute();
}

void Amplifier::volumeUp() {
    volume->increment();
}

void Amplifier::volumeDown() {
    volume->decrement();
}

void Amplifier::muteSpeakers() {
    speakers->write(0);
}
        
void Amplifier::unmuteSpeakers() {
    speakers->write(1);
}

bool Amplifier::routeSource(string source) {
    if (assoc != "") {
        switcher->unRouteAssociations(assoc, DEST_ASC);
    }
    assoc = source;
    return switcher->routeAssociations(source, DEST_ASC);
}

Association* Amplifier::getAssociation(string name) {
    return switcher->getAssociation(name);
}

string Amplifier::getSources() {
    return *sources;
}

string Amplifier::getCurrentAssociation() {
    return assoc;
}