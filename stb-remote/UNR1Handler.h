#ifndef __UNR1_REMOTE_HANDLER
#define __UNR1_REMOTE_HANDLER

#include "IRRemoteHandler.h"
#include <map>

class UNR1Handler : public IRRemoteHandler
{
    public:
        UNR1Handler();
        virtual ~UNR1Handler();
        
        virtual bool IdentifyRCUCommand(uint16_t command) override;
        virtual bool HandleRCUCommand(String command, IRsend irsend) override;
    private:
        static std::map<uint32_t, String> m_hexToButtonMap;
        //static std::map<String, uint16_t *> m_nameToArrayMap;
        static std::map<String, uint16_t> m_nameToArrayMap;
};

#endif //__UNR1_REMOTE_HANDLER