#include "ServerMgr.h"

ServerMgr::ServerMgr(String host, int port, String endpoint)
{
  m_host = host;
  m_httpPort = port;
  m_endpoint = endpoint;
  
  m_response = "";
  
  //WiFi.begin("HobbitholeME", "H1H2H3H4H5");
  WiFi.begin("Howl's Moving Hotspot", "Miyazaki123");
  //WiFi.begin("Ziraldo", "aaaaaaaa");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  m_bReady = true;
}

void ServerMgr::sendRequest(JsonObject& json, std::function<void(void)> fn)
{
    m_response = "";
    Serial.println("SendRequest");
    while (!client.connected())
    {
      Serial.println("connectionLoop");
        if (client.connect(m_host.c_str(), m_httpPort))
        {
          Serial.println("FormReq");
            char buffer[256];
            json.printTo(buffer, sizeof(buffer));
          
           	String data(buffer);
            String request = "GET ";
            request = request + m_endpoint;
            request = request + " HTTP/1.1";
            request = request + "\r\n";
            request = request + "Content-Type: application/json";
            request = request + "\r\n";
            request = request + "Content-Length: " + data.length();
            request = request + "\r\n";
            request = request + "\r\n";
            request = request + data;
            request = request + "\r\n";
			      //Serial.println(request);            
			      client.print(request);

            m_callback = fn;
        }
        else
        {
          Serial.println("Failed to Connect to server");
        }
    }
}

bool ServerMgr::receivedResponse()
{
   String response = waitForResponse();
   
   if(response != "")
   {      
      m_response = response;
      m_callback();
      return true;
   }
   return false;
}

String ServerMgr::getResponseString()
{  
  return m_response;
}

JsonObject& ServerMgr::getResponseJson()
{
  int str_len = m_response.length() + 1; 
  char char_array[str_len];
  m_response.toCharArray(char_array, str_len);
  
  StaticJsonBuffer<200> jsonBuffer;  
  return jsonBuffer.parseObject(char_array);
}

String ServerMgr::waitForResponse()
{
   String serverResponseString = "";
   int count = 0;
   while(client.available() && client.connected())
   {
       char c = client.read();
       //Serial.println(c);
       serverResponseString += c;

       if(c == '\r')
       serverResponseString = "";
       
       if (c == '}' || c == '\0')
       {
          client.stop();
          break;
       }
   }
   
  return serverResponseString;
}
