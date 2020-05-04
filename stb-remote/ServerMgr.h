#ifndef SERVER_MGR
#define SERVER_MGR

#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

class ServerMgr
{
public:
	ServerMgr(String host, int port, String endpoint);
	void sendRequest(JsonObject& json, std::function<void(void)> fn);
	bool receivedResponse();
  
  JsonObject& getResponseJson(); 
  String getResponseString();

  WiFiClient client;
  String m_host;
  int m_httpPort;
  String m_endpoint;

  bool m_bReady = false;

private:
   String waitForResponse();

   std::function<void(void)> m_callback;
   String m_response;
};

#endif
