#include "HttpAmpRequestHandler.h"
#include "Amplifier.h"
#include <string>

Amplifier* HttpAmpRequestHandler::amplifier;

HttpAmpRequestHandler::HttpAmpRequestHandler(const char* rootPath, const char* localPath, HTTPConnection::HTTPMessage& Msg, TCPSocketConnection& Tcp)
    : HTTPRequestHandler(Msg, Tcp) {
    
    m_rootPath = rootPath;
    m_localPath = localPath;
    handleRequest();
}

HttpAmpRequestHandler::~HttpAmpRequestHandler() {

}

int HttpAmpRequestHandler::handleGetRequest() {
    INFO("%s",m_rootPath.c_str());
    INFO("%s",m_localPath.c_str());
    char* outBuf = "UNRECOGNISED-COMMAND";
    int result = HTTP_NotFound;
    if (msg.args.count(POWER)) {
        if (msg.args[POWER] == ON) {
            amplifier->powerOn();        
            outBuf = "POWER-ON";
            result = HTTP_Ok;
        } else if (msg.args[POWER] == OFF) {
            amplifier->powerOff();
            outBuf = "POWER-OFF";
            result = HTTP_Ok;
        }
    }
    if (msg.args.count(MUTE)) {
        if (msg.args[MUTE] == ON) {
            amplifier->muteInput();        
            outBuf = "MUTE-ON";
            result = HTTP_Ok;
        } else if (msg.args[MUTE] == OFF) {
            amplifier->unmuteInput();
            outBuf = "MUTE-OFF";
            result = HTTP_Ok;
        }
    }
    if (msg.args.count(VOLUME)) {
        if (msg.args[VOLUME] == UP) {
            amplifier->volumeUp();        
            outBuf = "VOLUME-UP";
            result = HTTP_Ok;
        } else if (msg.args[VOLUME] == DOWN) {
            amplifier->volumeDown();
            outBuf = "VOLUME-DOWN";
            result = HTTP_Ok;
        }
    }
    if (msg.args.count(ROUTE)) {
        if (amplifier->routeSource(msg.args[ROUTE])) {
            outBuf = "ROUTE-DONE";
            result = HTTP_Ok;
        } else {
            outBuf = "UNKNOWN-SRC";
        }
    }
    if (msg.args.count(GET_SRCS)) {
        outBuf = (char*)amplifier->getSources().c_str();
        result = HTTP_Ok;
    }
    if (msg.args.count(GET_CUR_SRC)) {
        outBuf = (char*)amplifier->getCurrentAssociation().c_str();
        result = HTTP_Ok;
    }
    
    startResponse(result, strlen(outBuf));
    processResponse(strlen(outBuf), outBuf);
    endResponse();
    return result;
}

int HttpAmpRequestHandler::handlePostRequest() {
    return HTTP_NotFound;
}

int HttpAmpRequestHandler::handlePutRequest() {
    return HTTP_NotFound;
}