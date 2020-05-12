#ifndef Buttons_h
#define Buttons_h

#include "Arduino.h"

//saufg: Trigger Sonnenaufgang, suntg: Trigger Sonnenuntergang, mond: Trigger Mondlicht, tagl: Trigger Tageslicht, over: Trigger Übersteurt durch manuel.
int saufg, suntg, mond, tagl, aus, over;
float counter1, counter2, counter3 = 200, counter4 = 80;

/*
 * Button für manuellen Sonnenaufgang
 */
void aufgang(){
  saufg = 1;
  suntg = 0; 
  mond = 0;
  tagl = 0;
  aus = 0;
}

/*
 * Button für manuellen Sonnenuntergang
 */
void untergang(){
  saufg = 0;
  suntg = 1; 
  mond = 0;
  tagl = 0;
  aus = 0;
}

/*
 * Button für manuellen Mondschein
 */
void mondl(){
  saufg = 0;
  suntg = 0;
  mond = 1;
  tagl = 0;
  aus = 0;
}

/*
 * Button für manuell Licht aus
 */
void lichtaus(){
  saufg = 0;
  suntg = 0; 
  mond = 0;
  tagl = 0;
  aus = 1;
}

/*
 * Button für Ende manuelle Steuerung und zurück zu Tageslicht
 */
void resetten(){
  saufg = 0;
  suntg = 0; 
  mond = 0;
  tagl = 1;
  aus = 0;
  counter1 = 0;
  counter2 = 0;
  counter3 = 200;
  counter4 = 80;
}

#endif
