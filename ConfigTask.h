#ifndef _CONFIG_TASK_H_
#define _CONFIG_TASK_H_

#include <FS.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <Scheduler.h>


struct Config {
  char ssid [32];
  char password [14];
  int period;   // period in minutes (1 - 60)
  int time_on;  // in minutes but should be less than period (1 - 59)
};

class ConfigTask : public Task {
  private:
    struct Config settings;
    bool isDirty=false;
    
  protected:
    void setup();
    void loop();
    
  public:
    ConfigTask();
    bool loadConfiguration(); // can be used to reload as well
    bool saveConfiguration();
    bool updateConfig();  

    Config* getConfig();
    bool setConfig(Config* config);

};

#endif
