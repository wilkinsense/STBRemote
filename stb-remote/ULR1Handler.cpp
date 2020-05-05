#include "ULR1Handler.h"
#include <SPI.h>
#define ULR1_CODE_REPEAT_COUNT 4

uint16_t ULR1_BTN_DELIMITER_CODE[19] = {6042, 1224,  1208, 1214,  606, 608,  604, 1238,  578, 1240,  576, 1232,  584, 1240,  580, 626,  584, 606,  606};  // UNKNOWN E3DC5833

uint16_t ULR1_BTN_NUM_1[19] = {6044, 1222,  1178, 1262,  588, 608,  548, 662,  548, 662,  574, 638,  550, 1286,  530, 662,  550, 1268,  548};  // UNKNOWN C9767F76
uint16_t ULR1_BTN_NUM_2[19] = {6024, 1222,  1206, 1218,  602, 608,  606, 606,  548, 662,  550, 662,  1208, 628,  530, 664,  1206, 610,  604};  // UNKNOWN C8155AB1
uint16_t ULR1_BTN_NUM_3[19] = {6044, 1224,  1208, 1214,  548, 664,  550, 662,  548, 664,  548, 664,  1206, 1216,  548, 662,  1208, 1214,  548};  // UNKNOWN B6996DAE
uint16_t ULR1_BTN_NUM_4[19] = {6026, 1224,  1206, 1218,  548, 664,  574, 640,  548, 664,  548, 1268,  604, 608,  550, 662,  1180, 1244,  548};  // UNKNOWN 969AE844
uint16_t ULR1_BTN_NUM_5[19] = {6042, 1242,  1190, 1214,  548, 664,  548, 662,  548, 664,  548, 1268,  550, 1268,  548, 1268,  574, 638,  574};  // UNKNOWN 4AAFAC67
uint16_t ULR1_BTN_NUM_6[19] = {6016, 1254,  1180, 1242,  574, 638,  574, 638,  574, 638,  576, 1244,  1178, 640,  574, 1242,  576, 1254,  564};  // UNKNOWN 9C2A936C
uint16_t ULR1_BTN_NUM_7[19] = {6018, 1254,  1180, 1244,  576, 638,  576, 636,  576, 636,  576, 1242,  1180, 1244,  574, 1246,  1180, 638,  574};  // UNKNOWN 833ED333
uint16_t ULR1_BTN_NUM_8[19] = {6046, 1224,  1208, 1214,  550, 680,  532, 664,  548, 664,  1178, 640,  548, 664,  548, 1268,  1178, 640,  548};  // UNKNOWN 55F2B93
uint16_t ULR1_BTN_NUM_9[19] = {6004, 1252,  1180, 1244,  576, 636,  574, 638,  576, 650,  1166, 638,  576, 1242,  574, 1256,  1168, 1244,  574};  // UNKNOWN DE78B0D0
uint16_t ULR1_BTN_NUM_0[19] = {6044, 1224,  1178, 1244,  548, 662,  550, 662,  548, 1268,  550, 662,  548, 1268,  548, 1268,  1178, 638,  556};  // UNKNOWN F32F72D7
uint16_t ULR1_BTN_NUM_DASH[19] = {6014, 1254,  1180, 1244,  574, 638,  574, 638,  574, 1244,  574, 648,  1170, 638,  574, 1242,  1178, 1244,  576};  // UNKNOWN BDE97C12
uint16_t ULR1_BTN_NUM_ENTER[19] = {6042, 1224,  1208, 1214,  550, 662,  548, 664,  572, 1262,  530, 664,  1178, 1244,  1206, 610,  558, 656,  548};  // UNKNOWN 3F23F43

uint16_t ULR1_BTN_VOL_UP[19] = {6014, 1252,  1178, 1244,  574, 638,  574, 1242,  576, 1242,  1180, 638,  1178, 1244,  576, 1242,  576, 1240,  576};  // UNKNOWN 38C34200
uint16_t ULR1_BTN_VOL_DOWN[19] = {6042, 1224,  1208, 1216,  548, 682,  530, 1270,  550, 1268,  1208, 610,  1208, 1216,  548, 1268,  550, 1268,  550};  // UNKNOWN 38C34200
uint16_t ULR1_BTN_VOL_MUTE[19] = {6042, 1224,  1208, 1216,  548, 682,  530, 1270,  550, 1268,  1208, 610,  1208, 1216,  548, 1268,  550, 1268,  550};  // UNKNOWN 38C34200
uint16_t ULR1_BTN_CHAN_UP[19] = {6014, 1254,  1180, 1244,  576, 648,  564, 638,  574, 648,  1168, 1254,  564, 1242,  1180, 650,  1168, 638,  576};  // UNKNOWN 165412B7
uint16_t ULR1_BTN_CHAN_DOWN[19] = {6028, 1242,  1180, 1246,  548, 664,  550, 662,  550, 662,  1178, 1244,  1178, 640,  1178, 638,  1178, 1246,  548};  // UNKNOWN 5815B090

uint16_t ULR1_BTN_GUIDE[19] = {6014, 1252,  1180, 1242,  578, 636,  576, 636,  1180, 646,  1170, 638,  576, 636,  576, 638,  576, 636,  576};  // UNKNOWN 427EBE9F
uint16_t ULR1_BTN_ACTIVE[19] = {6014, 1252,  1180, 1244,  576, 636,  576, 636,  1180, 650,  1168, 638,  576, 1242,  576, 636,  576, 1242,  574};  // UNKNOWN 9D65B0BC
uint16_t ULR1_BTN_LIST[19] = {6036, 1222,  1208, 1226,  594, 620,  592, 620,  1196, 620,  1198, 622,  1198, 608,  606, 606,  1208, 618,  594};  // UNKNOWN AB4D94A9
uint16_t ULR1_BTN_EXIT[19] = {6014, 1252,  1178, 1256,  564, 636,  576, 642,  1174, 638,  574, 1242,  1180, 648,  1170, 1242,  1180, 1242,  576};  // UNKNOWN 34498102
uint16_t ULR1_BTN_UP[19] = {6012, 1254,  1180, 1242,  576, 636,  572, 638,  1180, 648,  564, 636,  576, 1242,  1178, 652,  1168, 1242,  574};  // UNKNOWN F24119FE
uint16_t ULR1_BTN_RIGHT[19] = {6012, 1254,  1178, 1244,  574, 638,  576, 636,  1178, 638,  574, 1242,  574, 638,  1178, 1244,  574, 1242,  574};  // UNKNOWN BC9DF06
uint16_t ULR1_BTN_DOWN[19] = {6002, 1264,  1168, 1242,  574, 638,  574, 636,  1180, 638,  574, 638,  1178, 638,  1180, 1242,  576, 636,  574};  // UNKNOWN B489062B
uint16_t ULR1_BTN_LEFT[19] = {6040, 1224,  1178, 1242,  576, 636,  574, 636,  1178, 640,  548, 664,  1180, 1242,  1178, 1244,  574, 1242,  548};  // UNKNOWN C53794B4
uint16_t ULR1_BTN_SELECT[19] = {6006, 1252,  1180, 1244,  576, 638,  574, 648,  1170, 636,  576, 1252,  564, 1254,  1168, 1242,  1180, 638,  576};  // UNKNOWN 75A956A7
uint16_t ULR1_BTN_PREV[19] = {6042, 1222,  1210, 1212,  576, 636,  576, 650,  590, 620,  1196, 1212,  1208, 1230,  1192, 1228,  562, 648,  590};  // UNKNOWN 5BFBFDE9
uint16_t ULR1_BTN_RECORD[19] = {6014, 1252,  1182, 1242,  576, 636,  576, 636,  1180, 1254,  566, 1240,  576, 1244,  574, 636,  1182, 1240,  578};  // UNKNOWN 81A840E6
uint16_t ULR1_BTN_INFO[19] = {6040, 1224,  1210, 1212,  574, 652,  562, 650,  1196, 608,  1208, 1214,  1210, 620,  592, 1214,  576, 1254,  564};  // UNKNOWN F640360

uint16_t ULR1_BTN_ONDEMAND[19] = {6014, 1266,  1166, 1244,  576, 636,  574, 1240,  1182, 1242,  576, 1240,  1180, 1242,  1180, 1242,  576, 636,  576};  // UNKNOWN 4A47214B

uint16_t ULR1_BTN_RED[19] = {6014, 1264,  1170, 1242,  576, 636,  574, 1242,  576, 636,  574, 650,  562, 1242,  1178, 650,  564, 636,  574};  // UNKNOWN C332FABB

uint16_t ULR1_BTN_REPEAT[19] = {6024, 1254,  1180, 1244,  574, 638,  576, 636,  1180, 1244,  576, 1242,  1180, 636,  576, 1242,  552, 660,  574};  // UNKNOWN 21FEFDF9
uint16_t ULR1_BTN_NEXT[19] = {6042, 1222,  1180, 1244,  548, 664,  574, 638,  1206, 1234,  532, 1268,  1208, 1214,  550, 1268,  548, 1268,  550};  // UNKNOWN 9D71047C
uint16_t ULR1_BTN_REWIND[19] = {6046, 1240,  1164, 1244,  548, 664,  548, 664,  1178, 1244,  548, 664,  1178, 1244,  548, 664,  1178, 640,  548};  // UNKNOWN E6D07133
uint16_t ULR1_BTN_FASTFORWARD[19] = {6016, 1252,  1180, 1242,  578, 636,  576, 638,  1180, 1242,  576, 1244,  572, 640,  550, 662,  1180, 638,  574};  // UNKNOWN 9B72C267

uint16_t ULR1_BTN_PLAYPAUSE[19] = {6012, 1252,  1180, 1242,  574, 638,  574, 636,  1180, 1252,  564, 638,  1180, 638,  576, 646,  564, 1244,  576};  // UNKNOWN D049E0A6
uint16_t ULR1_BTN_STOP[19] = {6042, 1224,  1178, 1260,  534, 664,  548, 662,  1208, 1214,  550, 664,  548, 1268,  548, 662,  550, 662,  574};  // UNKNOWN FBAD8623

uint16_t ULR1_BTN_PWR_ON_CODE1[19] = {6022, 1296,  1136, 1236,  582, 628,  1188, 634,  578, 606,  606, 632,  580, 684,  1132, 1212,  1210, 684,  528};  // UNKNOWN 6D8867D7
uint16_t ULR1_BTN_PWR_ON_CODE2[19] = {6028, 1222,  1210, 1212,  606, 608,  606, 1284,  532, 1234,  1188, 606,  1208, 1214,  606, 1212,  604, 1214,  604};  // UNKNOWN 38C34200

uint16_t ULR1_BTN_PWR_OFF_CODE1[19] = {6014, 1252,  1180, 1242,  576, 636,  1180, 638,  576, 634,  576, 648,  564, 1242,  1180, 1252,  1168, 1242,  576};  // UNKNOWN 692D04A0
uint16_t ULR1_BTN_PWR_OFF_CODE2[19] = {6014, 1252,  1180, 1242,  576, 636,  574, 1244,  574, 1242,  1180, 638,  1180, 1242,  574, 1244,  574, 1242,  576};  // UNKNOWN 38C34200

uint16_t ULR1_BTN_MENU[19] = {6002, 1262,  1170, 1242,  576, 646,  564, 646,  1170, 636,  576, 636,  576, 648,  1168, 638,  1180, 648,  564};  // UNKNOWN 76CF1379

std::map<uint32_t, String> ULR1Handler::m_hexToButtonMap = {
// RCU buttons
  { 0xC9767F76, "ULR1_BTN_NUM_1" },
  { 0xC8155AB1, "ULR1_BTN_NUM_2" },
  { 0xB6996DAE, "ULR1_BTN_NUM_3" },
  { 0x969AE844, "ULR1_BTN_NUM_4" },
  { 0x4AAFAC67, "ULR1_BTN_NUM_5" },
  { 0x9C2A936C, "ULR1_BTN_NUM_6" },
  { 0x833ED333, "ULR1_BTN_NUM_7" },
  { 0x55F2B93,  "ULR1_BTN_NUM_8" },
  { 0xDE78B0D0, "ULR1_BTN_NUM_9" },
  { 0xF32F72D7, "ULR1_BTN_NUM_0" },
  { 0xBDE97C12, "ULR1_BTN_NUM_DASH" },
  { 0x3F23F43,  "ULR1_BTN_NUM_ENTER" },

  { 0x38C34200, "ULR1_BTN_VOL_UP" },
  { 0x38C34200, "ULR1_BTN_VOL_DOWN" },
  { 0x38C34200, "ULR1_BTN_VOL_MUTE" },
  { 0x165412B7, "ULR1_BTN_CHAN_UP" },
  { 0x5815B090, "ULR1_BTN_CHAN_DOWN" },

  { 0x427EBE9F, "ULR1_BTN_GUIDE" },
  { 0x9D65B0BC, "ULR1_BTN_ACTIVE" },
  { 0xAB4D94A9, "ULR1_BTN_LIST" },
  { 0x34498102, "ULR1_BTN_EXIT" },
  { 0xF24119FE, "ULR1_BTN_UP" },
  { 0xBC9DF06,  "ULR1_BTN_RIGHT" },
  { 0xB489062B, "ULR1_BTN_DOWN" },
  { 0xC53794B4, "ULR1_BTN_LEFT" },
  { 0x75A956A7, "ULR1_BTN_SELECT" },
  { 0x5BFBFDE9, "ULR1_BTN_PREV" },
  { 0xC332FABB, "ULR1_BTN_RED" },
  { 0xF640360,  "ULR1_BTN_INFO" },

  { 0x4A47214B, "ULR1_BTN_ONDEMAND" },

  { 0xFBAD8623, "ULR1_BTN_STOP" },
  { 0x81A840E6, "ULR1_BTN_RECORD" },
  { 0xE6D07133, "ULR1_BTN_REWIND" },
  { 0xD049E0A6, "ULR1_BTN_PLAYPAUSE" },
  { 0x9B72C267, "ULR1_BTN_FASTFORWARD" },
  { 0x21FEFDF9, "ULR1_BTN_REPEAT" },
  { 0x9D71047C, "ULR1_BTN_NEXT" },

  { 0x6D8867D7, "ULR1_BTN_PWR_ON" },
  { 0x692D04A0, "ULR1_BTN_PWR_OFF" },
  { 0x76CF1379, "ULR1_BTN_MENU" }
};

std::map<String, std::vector<uint16_t *>> ULR1Handler::m_nameToArrayMap
{
    { "ULR1_BTN_NUM_1",         std::vector<uint16_t *> { ULR1_BTN_NUM_1,           ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_NUM_2",         std::vector<uint16_t *> { ULR1_BTN_NUM_2,           ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_NUM_3",         std::vector<uint16_t *> { ULR1_BTN_NUM_3,           ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_NUM_4",         std::vector<uint16_t *> { ULR1_BTN_NUM_4,           ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_NUM_5",         std::vector<uint16_t *> { ULR1_BTN_NUM_5,           ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_NUM_6",         std::vector<uint16_t *> { ULR1_BTN_NUM_6,           ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_NUM_7",         std::vector<uint16_t *> { ULR1_BTN_NUM_7,           ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_NUM_8",         std::vector<uint16_t *> { ULR1_BTN_NUM_8,           ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_NUM_9",         std::vector<uint16_t *> { ULR1_BTN_NUM_9,           ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_NUM_0",         std::vector<uint16_t *> { ULR1_BTN_NUM_0,           ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_NUM_DASH",      std::vector<uint16_t *> { ULR1_BTN_NUM_DASH,        ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_NUM_ENTER",     std::vector<uint16_t *> { ULR1_BTN_NUM_ENTER,       ULR1_BTN_DELIMITER_CODE } },

    { "ULR1_BTN_VOL_UP",        std::vector<uint16_t *> { ULR1_BTN_VOL_UP,          ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_VOL_DOWN",      std::vector<uint16_t *> { ULR1_BTN_VOL_DOWN,        ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_VOL_MUTE",      std::vector<uint16_t *> { ULR1_BTN_VOL_MUTE,        ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_CHAN_UP",       std::vector<uint16_t *> { ULR1_BTN_CHAN_UP,         ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_CHAN_DOWN",     std::vector<uint16_t *> { ULR1_BTN_CHAN_DOWN,       ULR1_BTN_DELIMITER_CODE } },
    
    { "ULR1_BTN_GUIDE",         std::vector<uint16_t *> { ULR1_BTN_GUIDE,           ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_ACTIVE",        std::vector<uint16_t *> { ULR1_BTN_ACTIVE,          ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_LIST",          std::vector<uint16_t *> { ULR1_BTN_LIST,            ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_EXIT",          std::vector<uint16_t *> { ULR1_BTN_EXIT,            ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_UP",            std::vector<uint16_t *> { ULR1_BTN_UP,              ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_RIGHT",         std::vector<uint16_t *> { ULR1_BTN_RIGHT,           ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_DOWN",          std::vector<uint16_t *> { ULR1_BTN_DOWN,            ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_LEFT",          std::vector<uint16_t *> { ULR1_BTN_LEFT,            ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_SELECT",        std::vector<uint16_t *> { ULR1_BTN_SELECT,          ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_PREV",          std::vector<uint16_t *> { ULR1_BTN_PREV,            ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_RED",           std::vector<uint16_t *> { ULR1_BTN_RED,             ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_INFO",          std::vector<uint16_t *> { ULR1_BTN_INFO,            ULR1_BTN_DELIMITER_CODE } },

    { "ULR1_BTN_ONDEMAND",      std::vector<uint16_t *> { ULR1_BTN_ONDEMAND,        ULR1_BTN_DELIMITER_CODE } },
    
    { "ULR1_BTN_STOP",          std::vector<uint16_t *> { ULR1_BTN_STOP,            ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_RECORD",        std::vector<uint16_t *> { ULR1_BTN_RECORD,          ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_REWIND",        std::vector<uint16_t *> { ULR1_BTN_REWIND,          ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_PLAYPAUSE",     std::vector<uint16_t *> { ULR1_BTN_PLAYPAUSE,       ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_FASTFORWARD",   std::vector<uint16_t *> { ULR1_BTN_FASTFORWARD,     ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_REPEAT",        std::vector<uint16_t *> { ULR1_BTN_REPEAT,          ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_NEXT",          std::vector<uint16_t *> { ULR1_BTN_NEXT,            ULR1_BTN_DELIMITER_CODE } },

    { "ULR1_BTN_PWR_ON",        std::vector<uint16_t *> { ULR1_BTN_PWR_ON_CODE1,    ULR1_BTN_PWR_ON_CODE2,  ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_PWR_OFF",       std::vector<uint16_t *> { ULR1_BTN_PWR_OFF_CODE1,   ULR1_BTN_PWR_OFF_CODE2, ULR1_BTN_DELIMITER_CODE } },
    { "ULR1_BTN_MENU",          std::vector<uint16_t *> { ULR1_BTN_STOP,            ULR1_BTN_DELIMITER_CODE } },
};

ULR1Handler::ULR1Handler() { }
ULR1Handler::~ULR1Handler() { }

bool ULR1Handler::IdentifyRCUCommand(uint32_t command)
{
    auto it = m_hexToButtonMap.find(command);
    if (it != m_hexToButtonMap.end())
    {
        Serial.print("Recognized ");
        Serial.println(it->second);
        return true;
    }
    
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
