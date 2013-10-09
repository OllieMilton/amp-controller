#ifndef AMPHTTPREQUESTHANDLER_H
#define AMPHTTPREQUESTHANDLER_H

#define DEBUG
#include "hl_debug.h"

#include "HTTPRequestHandler.h"
#include "Amplifier.h"
#include <string>

const string POWER      = "power";
const string ROUTE      = "route";
const string VOLUME     = "volume";
const string MUTE       = "mute";
const string ON         = "on";
const string OFF        = "off";
const string UP         = "up";
const string DOWN       = "down";
const string GET_SRCS   = "getsrcs";

class HttpAmpRequestHandler : public HTTPRequestHandler {
    static Amplifier* amplifier;
    public :
        HttpAmpRequestHandler(const char* rootPath, const char* localPath, HTTPConnection::HTTPMessage& Msg, TCPSocketConnection& Tcp);
        
        /** Destructor 
        */
        virtual ~HttpAmpRequestHandler();
  
        /** static creation function for this object.
        */
        static inline HTTPRequestHandler* create(const char* rootPath, const char* localPath, HTTPConnection::HTTPMessage& msg, TCPSocketConnection& tcp) { return new HttpAmpRequestHandler(rootPath, localPath, msg, tcp); }
              
        /** Handler function to serve GET requests
        */
        virtual int handleGetRequest();
        
        /** Handler function to serve PUT requests
        */
        virtual int handlePutRequest();
        
        /** Handler function to serve POST requests
        */
        virtual int handlePostRequest();
        
        static void setAmplifier(Amplifier* arg) {amplifier = arg;}
                
     private:
        std::string m_rootPath;
        std::string m_localPath;
        

};
#endif