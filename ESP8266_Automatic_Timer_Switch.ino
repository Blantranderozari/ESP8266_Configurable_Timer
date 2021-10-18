/*
 * Automatic Timer Switch
 * 
 * By: Antonius Blantran de Rozari
 * Created: Sep 20th 2020
 * Last Modified: Oct 13th 2020
 * 
 * Note:
 * The blue LED on the ESP-01 modul is connected to GPIO1 which is also the
 * TxD pin; so we cannot use the Serial.print() at the same time. This sketch uses
 * LED_BUILTIN to find the pin with the internal LED
 * 
 */

#include "ConfigTask.h"
#include "WebTask.h"
#include "SwitchTask.h"

// define macro
#define VERSION 0.2
#define DEBUG

void setup() {
  // Initialize serial port
  Serial.begin(115200);
  delay(1000);

//#ifdef DEBUG
  Serial.println(F("Serial monitor initialized"));
//#endif

  static ConfigTask configTask;
  static WebTask webTask;
  static SwitchTask switchTask;

  switchTask.setConfigTaskpointer(&configTask);
  webTask.setConfigTaskpointer(&configTask);

  Scheduler.start(&configTask);
  Scheduler.start(&webTask);
  Scheduler.start(&switchTask);
  Scheduler.begin();

}

void loop() {  
}
