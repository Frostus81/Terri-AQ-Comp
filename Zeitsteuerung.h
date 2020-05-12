#ifndef Zeitsteuerung_h
#define Zeitsteuerung_h

#include "Arduino.h"

RTC_DS1307 rtc;

void get_Timep(){
  DateTime now = rtc.now();
  char buf1[] = "hh:mm";
  String zeit = "tTime.txt=\""+String(now.toString(buf1))+"\"";
  Serial.print(zeit);
}

#endif
