#include "SwitchTask.h"

SwitchTask::SwitchTask(){
#ifdef DEBUG
  Serial.println(F("Creating SwitchTask class"));
#endif
  return;     
}

void SwitchTask::setConfigTaskpointer(ConfigTask* pClass){
  pConfTask = pClass;

#ifdef DEBUG
  if(pConfTask == NULL){
    Serial.println(F("pConfTask assignment failed"));
  }
#endif
  return;
}
  
void SwitchTask::setup(){
  pSetting = pConfTask->getConfig();

#ifdef DEBUG
  if(pSetting == NULL){
    Serial.println(F("pSetting assignment failed"));
  }
#endif

  time_on = (int)pSetting->time_on;
  time_off = (int)pSetting->period - time_on;
  Serial.println(F("value of time_on & time off in SwitchTask: "));
  Serial.println(time_on);
  Serial.println(time_off);
  
  pinMode(LED_BUILTIN,OUTPUT);
  return;
}

void SwitchTask::loop(){

#ifdef DEBUG  
  Serial.println(F("Turn the LED ON "));
#endif

  digitalWrite(LED_BUILTIN,LOW);
  delay(time_on*MULTIPLIER);

#ifdef DEBUG
  Serial.println(F("Turn the LED OFF "));
#endif

  digitalWrite(LED_BUILTIN,HIGH);
  delay(time_off*MULTIPLIER);
  
  return;
}
