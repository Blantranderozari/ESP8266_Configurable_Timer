#include "ConfigTask.h"

//#define CONFIG_FILENAME "/default.txt"
const char* Confilename = "/default.txt";

ConfigTask::ConfigTask(){
#ifdef DEBUG
  Serial.println(F("Creating ConfigTask class"));
#endif
}

bool ConfigTask::loadConfiguration() {
  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<256> doc;
  
  File configFile = LittleFS.open(Confilename,"r");
  if (!configFile) {
#ifdef DEBUG
    Serial.print("Unable to open config file");   // failed. Use factory settings
#endif
  } else {
    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, configFile);
#ifdef DEBUG
    if (error){
      Serial.print(F("deserializeJson() failed with code: "));
      Serial.println(error.c_str());
    }
#endif
  }
    
  // Copy values from the JsonDocument to the Config
  strlcpy(settings.ssid, doc["ssid"] | "Blantran de Rozari", sizeof(settings.ssid));
  strlcpy(settings.password, doc["password"] | "soka19dramaga", sizeof(settings.password));
  settings.period = doc["period"]|5;
  settings.time_on = doc["time_on"]|3;

#ifdef DEBUG  
  Serial.println(F("print active settings"));
  serializeJsonPretty(doc, Serial);
#endif

  configFile.close();
  return true; 
}

bool ConfigTask::saveConfiguration() {
  // Open file for writing
  File configFile = LittleFS.open(Confilename, "w");
  if (!configFile) {
#ifdef DEBUG
    Serial.println(F("Failed to create file"));
#endif
    return false;
  }

  // Allocate a temporary JsonDocument
  // Use arduinojson.org/assistant to compute the capacity.
  StaticJsonDocument<256> doc;

  // Set the values in the document
  doc["ssid"] = settings.ssid;
  doc["password"] = settings.password;
  doc["period"] = settings.period;
  doc["time_on"] = settings.time_on;

  // Serialize JSON to file
  if (serializeJson(doc, configFile) == 0) {
#ifdef DEBUG
    Serial.println(F("Failed to write to file"));
#endif
    return false;
  }

#ifdef DEBUG
  serializeJsonPretty(doc, Serial);
  Serial.println(F("Configuration saved!"));
#endif

  // Close the file
  configFile.close();  
  return true;
}

Config* ConfigTask::getConfig(){
  return &settings;
}

void ConfigTask::setup(){
  // Mount file system
  if (!LittleFS.begin()) {
#ifdef DEBUG
     Serial.println(F("Failed to mount file system"));
#endif
     return;
  }

#ifdef DEBUG
  Serial.println(F("FS mounted..."));
#endif

  if(!loadConfiguration()){
#ifdef DEBUG
    Serial.println(F("Failed to open config file"));
#endif
    return;
  }

//  saveConfiguration();
}

void ConfigTask::loop(){
#ifdef DEBUG
  Serial.println(F("Entering ConfigTask loop"));
  delay(5000);
  Serial.println(F("Leaving ConfigTask loop"));
#endif
  return;
}
