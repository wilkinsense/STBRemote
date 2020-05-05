#include <SPI.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <IRsend.h>
#include <map>

#define RECV_PIN 14
#define IR_LED 12

#include "TimerMgr.h"
#include "IRRemoteHandler.h"
#include "UNR1Handler.h"
#include "ULR1Handler.h"

TimerMgr* m_timer;

IRrecv irrecv(RECV_PIN);
IRsend irsend(IR_LED);
bool m_bSendIRToBox = true;
bool m_bReadFromSerial = true;
bool m_bOutputIRRemoteInformation = false;

decode_results results;

std::vector<IRRemoteHandler *> m_RCUHandlers;

void handleRecord() {
  String output = "";
  if (irrecv.decode(&results)) {
    output += resultToHexidecimal(&results);
    irrecv.resume();  // Receive the next value

    uint32_t intValue = (uint32_t)strtoul(output.c_str(), 0, 16);
    output += '\n';
    if (m_bOutputIRRemoteInformation)
    {
      output += resultToSourceCode(&results);
    }
    Serial.print(output);
    //Serial.print(" : ");

    for (size_t rcuIndex = 0; rcuIndex < m_RCUHandlers.size(); rcuIndex++)
    {
        Serial.println("Identifying...");
        IRRemoteHandler *handler = m_RCUHandlers[rcuIndex];
        if (handler->IdentifyRCUCommand(intValue))
        {
            break;
        }
    }
  } 
  else {
    //output = "empty";
  }
}

void setup()
{    
    Serial.begin(115200);
    delay(10);
    if (!m_bReadFromSerial)
    {
        Serial.println("\nInitialized");
    }

    irrecv.enableIRIn();  // Start the receiver
    irsend.begin(); // Start IR sender

    m_timer = new TimerMgr();
    m_RCUHandlers.push_back(new UNR1Handler());
    m_RCUHandlers.push_back(new ULR1Handler());

    if (m_bReadFromSerial)
    {
        Serial.flush();
    }
}

void sensorCallback()
{
    Serial.println("Returned from request!");
}

String command;
void loop()
{
    //
    if (m_bSendIRToBox)
    {
        handleSend(m_bReadFromSerial);
    }
    else
    {
        handleRecord();
    }

    m_timer->tickTimers();
}

bool bMakingRequest = false;

void handleSend(bool bUseSerial)
{
    bool bCommandReady = false;
    
    if (bUseSerial)
    {
        if (Serial.available() > 0)
        {
            char currentLetter = Serial.read();
            bCommandReady = currentLetter == '\0';
           
            if (bCommandReady)
            {
              Serial.println();
            }
            else
            {
              command.concat(currentLetter);
              Serial.print(currentLetter);
            }
        }
    }

    if (bCommandReady)
    {
        for (size_t rcuIndex = 0; rcuIndex < m_RCUHandlers.size(); rcuIndex++)
        {
            IRRemoteHandler *handler = m_RCUHandlers[rcuIndex];
            if (handler->HandleRCUCommand(command, irsend))
            {
                break;
            }
        }

        command = "";
    }
}
