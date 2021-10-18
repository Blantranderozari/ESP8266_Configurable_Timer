#include "WebTask.h"
#include <ESP8266WiFi.h>
#include <aREST.h>

// The port to listen for incoming TCP connections
#define LISTEN_PORT           80


// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Create aREST instance
aREST rest = aREST();

// redeclare static data member to suppress link error
Config* WebTask::pSetting;  
ConfigTask* WebTask::pConfTask;
SwitchTask* WebTask::pSwitchTask;

WebTask::WebTask(){
#ifdef DEBUG
  Serial.println(F("Creating Web class"));
#endif
}

void WebTask::setConfigTaskpointer(ConfigTask* pClass){
  pConfTask = pClass;
#ifdef DEBUG  
  if(pConfTask == NULL){
    Serial.println(F("pConfTask assignment failed"));
  }
#endif  
  return;
}

int WebTask::set_period(String duration){
  pSetting->period = duration.toInt();
  return 1;
}

int WebTask::set_timeon(String duration){
  pSetting->time_on = duration.toInt();
  return 1;
}

int WebTask::activate(String command){
  return 1;
}

int WebTask::save(String command){
  pConfTask->saveConfiguration();
  ESP.restart();
  return 1;
}

void WebTask::setup(){
  pSetting = pConfTask->getConfig();

#ifdef DEBUG
  if(pSetting == NULL){
    Serial.println(F("pSetting assignment failed"));
  }
#endif

  // Give id and name to device
  rest.set_id("1");
  rest.set_name("Automatic Timer Switch");
  
  // The SSID & password should not be passed as REST variables
  //  rest.variable("ssid",&pSetting->ssid);
  //  rest.variable("password",&pSetting->password);
  rest.variable("period",&pSetting->period);
  rest.variable("time_on",&pSetting->time_on);

  rest.function("setperiod",set_period);
  rest.function("settimeon",set_timeon);
  rest.function("activate",activate);
  rest.function("save",save);

  // Connect to WiFi
  WiFi.begin(pSetting->ssid, pSetting->password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(F("WiFi connected"));

  // Start the server
  server.begin();
  Serial.println(F("Server started"));
  Serial.println(WiFi.localIP());   // Print the IP address
  
  return;
}

void WebTask::loop(){
//  Serial.println(F("Entering WebTask loop"));

  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  } else {
    Serial.println("Client connected");
  }

  while(!client.available()){
#ifdef DEBUG
    Serial.println(F("Waiting for client"));
#endif
    delay(1); 
  }

#ifdef DEBUG
  Serial.println(F("Transfer to REST ..."));
#endif  
  rest.handle(client);

  return;
}
