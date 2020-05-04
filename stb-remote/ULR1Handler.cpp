#include "ULR1Handler.h"
#define ULR1_CODE_REPEAT_COUNT 4

uint16_t ULR1_BTN_DELIMITER_CODE[19] = {6042, 1224,  1208, 1214,  606, 608,  604, 1238,  578, 1240,  576, 1232,  584, 1240,  580, 626,  584, 606,  606};  // UNKNOWN E3DC5833

uint16_t ULR1_BTN_PWR_ON_CODE1[19] = {6022, 1296,  1136, 1236,  582, 628,  1188, 634,  578, 606,  606, 632,  580, 684,  1132, 1212,  1210, 684,  528};  // UNKNOWN 6D8867D7
uint16_t ULR1_BTN_PWR_ON_CODE2[19] = {6028, 1222,  1210, 1212,  606, 608,  606, 1284,  532, 1234,  1188, 606,  1208, 1214,  606, 1212,  604, 1214,  604};  // UNKNOWN 38C34200

uint16_t ULR1_BTN_PWR_OFF_CODE1[19] = {6014, 1252,  1180, 1242,  576, 636,  1180, 638,  576, 634,  576, 648,  564, 1242,  1180, 1252,  1168, 1242,  576};  // UNKNOWN 692D04A0
uint16_t ULR1_BTN_PWR_OFF_CODE2[19] = {6014, 1252,  1180, 1242,  576, 636,  574, 1244,  574, 1242,  1180, 638,  1180, 1242,  574, 1244,  574, 1242,  576};  // UNKNOWN 38C34200

uint16_t ULR1_BTN_RED[19] = {6014, 1264,  1170, 1242,  576, 636,  574, 1242,  576, 636,  574, 650,  562, 1242,  1178, 650,  564, 636,  574};  // UNKNOWN C332FABB

uint16_t ULR1_BTN_REPEAT[19] = {6024, 1254,  1180, 1244,  574, 638,  576, 636,  1180, 1244,  576, 1242,  1180, 636,  576, 1242,  552, 660,  574};  // UNKNOWN 21FEFDF9
uint16_t ULR1_BTN_NEXT[19] = {6042, 1222,  1180, 1244,  548, 664,  574, 638,  1206, 1234,  532, 1268,  1208, 1214,  550, 1268,  548, 1268,  550};  // UNKNOWN 9D71047C
uint16_t ULR1_BTN_REWIND[19] = {6046, 1240,  1164, 1244,  548, 664,  548, 664,  1178, 1244,  548, 664,  1178, 1244,  548, 664,  1178, 640,  548};  // UNKNOWN E6D07133
uint16_t ULR1_BTN_FASTFORWARD[19] = {6016, 1252,  1180, 1242,  578, 636,  576, 638,  1180, 1242,  576, 1244,  572, 640,  550, 662,  1180, 638,  574};  // UNKNOWN 9B72C267

uint16_t ULR1_BTN_PLAYPAUSE[19] = {6012, 1252,  1180, 1242,  574, 638,  574, 636,  1180, 1252,  564, 638,  1180, 638,  576, 646,  564, 1244,  576};  // UNKNOWN D049E0A6
uint16_t ULR1_BTN_STOP[19] = {6042, 1224,  1178, 1260,  534, 664,  548, 662,  1208, 1214,  550, 664,  548, 1268,  548, 662,  550, 662,  574};  // UNKNOWN FBAD8623

std::map<String, std::vector<uint16_t *>> ULR1Handler::m_nameToArrayMap
{
    { "ULR1_BTN_PWR_ON",        std::vector<uint16_t *> { ULR1_BTN_PWR_ON_CODE1,    ULR1_BTN_PWR_ON_CODE2,  ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_PWR_OFF",       std::vector<uint16_t *> { ULR1_BTN_PWR_OFF_CODE1,   ULR1_BTN_PWR_OFF_CODE2, ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_RED",           std::vector<uint16_t *> { ULR1_BTN_RED,             ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_REPEAT",        std::vector<uint16_t *> { ULR1_BTN_REPEAT,          ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_NEXT",          std::vector<uint16_t *> { ULR1_BTN_NEXT,            ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_FASTFORWARD",   std::vector<uint16_t *> { ULR1_BTN_FASTFORWARD,     ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_PLAYPAUSE",     std::vector<uint16_t *> { ULR1_BTN_PLAYPAUSE,       ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_STOP",          std::vector<uint16_t *> { ULR1_BTN_STOP,            ULR1_BTN_DELIMITER_CODE } },
};

ULR1Handler::ULR1Handler() { }
ULR1Handler::~ULR1Handler() { }

bool ULR1Handler::IdentifyRCUCommand(uint16_t command)
{
    return false;
}
        
bool ULR1Handler::HandleRCUCommand(String command, IRsend irsend)
{
    auto it = m_nameToArrayMap.find(command);
    if (it != m_nameToArrayMap.end())
    {
        for (auto codeArray : it->second)
        {
            for (int index = 0; index < ULR1_CODE_REPEAT_COUNT; index++)
            {
                irsend.sendRaw(codeArray, 19, 38); // 38 = kHz
                delay(100);
            }
        }
        return true;
    }
    return false;
}