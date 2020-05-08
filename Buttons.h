#ifndef Buttons_h
#define Buttons_h

#include "Arduino.h"
int saufg = 0, suntg = 0, mond = 0, tagl = 0, over = 0;
float counter1, counter2, counter3 = 255, counter4 = 80;

/*
 * Button für manuellen Sonnenaufgang
 */
void aufgang() 
{
  saufg = 1;
  suntg = 0; 
  mond = 0;
  over = 1;
  tagl = 0;
}

/*
 * Button für manuellen Sonnenuntergang
 */
void untergang() 
{
  saufg = 0;
  suntg = 1; 
  mond = 0;
  over = 1;
  tagl = 0;
}

/*
 * Button für manuellen Mondschein
 */
void mondl() 
{
  saufg = 0;
  suntg = 0;
  mond = 1;
  over = 1;
  tagl = 0;

}

/*
 * Button für manuell Licht aus
 */
void lichtaus() 
{
  saufg = 0;
  suntg = 0; 
  mond = 0;
  tagl = 0;
  over = 1;

}

/*
 * Button für Ende manuellen Sonnenuntergang
 */
void resetten() 
{

  saufg = 0;
  suntg = 0; 
  mond = 0;
  over = 0;
  tagl = 1;
  counter1 = 0;
  counter2 = 0;
  counter3 = 255;
  counter4 = 80;
}

#endif
