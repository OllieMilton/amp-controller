#include "mbed.h"
#include "Amplifier.h"
#include "EthernetInterface.h"
#include "DigiPot.h"
#include "HTTPServer.h"
#include "HttpAmpRequestHandler.h"
//#include "LocalFileSystem.h"
#define DEBUG
#include "hl_debug.h"

HTTPServer  svr;
//LocalFileSystem local("local");
Serial pc(USBTX, USBRX);
const int port = 80;
int main() {
    pc.baud(460800);
    INFO("Amp controller V0.1");
    AmpConf conf;
    conf.ampPower = p17;
    conf.x0 = p19;
    conf.x1 = p20;
    conf.x2 = p21;
    conf.x3 = p22;
    conf.y0 = p23;
    conf.y1 = p24;
    conf.y2 = p25;
    conf.data = p26;
    conf.strobe = p27;
    conf.reset = p28;
    conf.speakers = p29;
    conf.miso = p6;
    conf.mosi = p5;
    conf.clk = p7;
    conf.cs = p8;
    Amplifier amp(conf);
    INFO("starting...");
    HttpAmpRequestHandler::setAmplifier(&amp);
    svr.addHandler<HttpAmpRequestHandler>("/ampcontrol");
    EthernetInterface eth;
    eth.init();
    eth.connect();
    INFO("IP Address is %s\n\r", eth.getIPAddress());
    INFO("Starting http server...");
    if (!svr.start(port, &eth)) {
        INFO("Server not starting !");
        exit(0);
    }
    INFO("Server started");
    while (true) {
        svr.poll();
    }
     
}