#ifndef _SWITCH_TASK_H_
#define _SWITCH_TASK_H_

#include <Scheduler.h>
#include "ConfigTask.h"

#define MULTIPLIER 1000

class SwitchTask: public Task {
  private:
    Config* pSetting = NULL;
    ConfigTask* pConfTask = NULL;
    int time_on, time_off;
 
  protected:
    void setup();
    void loop();
    
  public:
    SwitchTask();
    void setConfigTaskpointer(ConfigTask* pClass);
};

#endif
