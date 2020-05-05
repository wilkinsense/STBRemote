#ifndef __ULR1_REMOTE_HANDLER
#define __ULR1_REMOTE_HANDLER

#include "IRRemoteHandler.h"
#include <map>
#include <vector>

class ULR1Handler : public IRRemoteHandler
{
    public:
        ULR1Handler();
        virtual ~ULR1Handler();
        
        virtual bool IdentifyRCUCommand(uint32_t command) override;
        virtual bool HandleRCUCommand(String command, IRsend irsend) override;
    private:
        static std::map<uint32_t, String> m_hexToButtonMap;
        static std::map<String, uint16_t *> m_nameToArrayMap;
};

#endif //__ULR1_REMOTE_HANDLER
