#ifndef Lichtsteuerung_h
#define Lichtsteuerung_h

#include "Arduino.h"
#include "Buttons.h"
#include <Adafruit_NeoPixel.h>

#define N_Pixels 6 //6 NeoPixel
#define LED_PIN 6 //NeoPixel sind an diesen Pin angeschlossen
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_Pixels, LED_PIN, NEO_GRB + NEO_KHZ800);

// Füllt LED-Pixel nacheinander mit Farbe
void colorWipe(uint32_t c, uint8_t wait){
  for(uint16_t i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, c);
    strip.show();
  }
}

void Lichtaus(){
  colorWipe (strip.Color(0, 0, 0),0); //Farbe des Lichtaus in r, g, b
  strip.show();
  lichtaus();
}
void Mondlicht(){
  colorWipe (strip.Color(0, 0, 25),0); //Farbe des Mondlichtes in r, g, b
  strip.show();
  mondl();
}

void Taglicht(){
  colorWipe (strip.Color(200, 80, 0),0); //Farbe des Taglichtes in r, g, b
  strip.show();
  resetten();
}

void Tag(){
    String taglicht = "tState.txt=\""+String("Taglicht")+"\"";
    Serial.print(taglicht);
}

void Nacht(){
    String mond1 = "tState.txt=\""+String("Mondlicht")+"\"";
    Serial.print(mond1);
}

void Abend(){
    String suntg = "tState.txt=\""+String("Sonnenuntergang")+"\"";
    Serial.print(suntg);
}

void Morgen(){
    String saufg = "tState.txt=\""+String("Sonnenaufgang")+"\"";
    Serial.print(saufg);
}

void Dunkel(){
    String aus = "tState.txt=\""+String("Licht aus")+"\"";
    Serial.print(aus);
}

void Sonnenstand()
{
unsigned long interval=5000; // Zeit zur nächsten Farbe (5000 = 30 min)
unsigned long previousMillis=0; // millis() returns an unsigned long.
unsigned long previousMillis2=0; // millis() returns an unsigned long.
  /*
 * Fade Sonnenaufgang
 */
  unsigned long currentMillis = millis(); // grab current time

  if (saufg == 1){
  if ((unsigned long)(currentMillis - previousMillis) >= interval) {
      counter1+=0.71;
      counter2+=0.22;
      if(counter2>=79.2){
        saufg = 0;
        tagl = 1;
        counter1 = 0;
        counter2 = 0;
      }
    // fade led mit counter
    colorWipe (strip.Color(counter1, counter2, 0), 0);
    strip.show();
    previousMillis = millis();
   }
  }

    /*
   * Fade Sonnenuntergang
   */
  unsigned long currentMillis2 = millis(); // grab current time

  if (suntg == 1){
  if ((unsigned long)(currentMillis2 - previousMillis2) >= interval) {
      counter3-=0.71;
      counter4-=0.22;
      if(counter4<=1){
          suntg = 0;
          mond = 1;
          counter3 = 200;
          counter4 = 80;
                    }
    // fade led mit counter
    colorWipe (strip.Color(counter3, counter4, 0), 0);
    strip.show();
    previousMillis2 = millis();
   }
  }
}

#endif
