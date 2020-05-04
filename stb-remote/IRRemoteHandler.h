#ifndef __IR_REMOTE_HANDLER
#define __IR_REMOTE_HANDLER

#include <Arduino.h>
#include <IRsend.h>

class IRRemoteHandler
{
    public:
        IRRemoteHandler() {}
        virtual ~IRRemoteHandler() {}
        
        virtual bool IdentifyRCUCommand(uint16_t command) = 0;
        virtual bool HandleRCUCommand(String command, IRsend irsend) = 0;
    private:
};

#endif //__IR_REMOTE_HANDLER
