#ifndef _WEB_TASK_H_
#define _WEB_TASK_H_

#include <Scheduler.h>
#include "ConfigTask.h"
#include "SwitchTask.h"

class WebTask: public Task {
  public:
    WebTask();
    void setConfigTaskpointer(ConfigTask* pClass);
    static int set_period(String duration);
    static int set_timeon(String duration);
    static int activate(String command);
    static int save(String command);
      
  protected:
    void setup();
    void loop();

  private:
    static Config* pSetting;
    static ConfigTask* pConfTask;
    static SwitchTask* pSwitchTask;

};


#endif
