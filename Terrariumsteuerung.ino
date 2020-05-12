#include "Nextion.h"
#include "RTClib.h"
#include "DHT.h"
#include "Buttons.h"
#include "Lichtsteuerung.h"
#include "Zeitsteuerung.h"
#include <Adafruit_NeoPixel.h>

#define DHTPIN 13     // Temp- und Luftfeuchtigkeitssensor ist an diesen Pin angeschlossen
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

/*
 * Globale Variabeln 
 */
float temperature = 0.0f;
float humidity = 0.0f;

DHT dht(DHTPIN, DHTTYPE);

NexButton bSoauf = NexButton(0, 2, "bSoauf");
NexButton bSontg = NexButton(0, 11, "bSontg");
NexButton bMond = NexButton(0, 12, "bMond");
NexButton bOff = NexButton(0, 3, "bOff");
NexButton bRst = NexButton(0, 13, "bRst");
NexText tTempC = NexText(0, 7, "tTempC");
NexText tState = NexText(0, 1, "tState");
NexProgressBar jHumidity = NexProgressBar(0, 6, "jHumidity");
NexText tHumidity = NexText(0, 8, "tHumidity");

NexTouch *nex_listen_list[] = {
  &bSoauf,
  &bSontg,
  &bOff,
  &bMond,
  &bRst,
  NULL
};

/*
 * Konfiguration Echtzeit
 */
char daysOfTheWeek[7][12] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};

void setup (){
  dht.begin();

  strip.begin();
  strip.setBrightness(125);//Helligkeit einstellen
  strip.show();
  
  while (!Serial); // for Leonardo/Micro/Zero

  Serial.begin(9600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2020, 4, 1, 7, 35, 10));
  }
  nexInit();
  bSoauf.attachPop(bSoaufPopCallback, &bSoauf);
  bSontg.attachPop(bSontgPopCallback, &bSontg);
  bOff.attachPop(bOffPopCallback, &bOff);
  bMond.attachPop(bMondPopCallback, &bMond);
  bRst.attachPop(bRstPopCallback, &bRst);
}

/*
 * Button für manuellen Sonnenaufgang
 */
void bSoaufPopCallback(void *ptr){
  aufgang();
  over = 1;
}

/*
 * Button für manuellen Sonnenuntergang
 */
void bSontgPopCallback(void *ptr){
  untergang();
  over = 1;
}

/*
 * Button für manuellen Mondschein
 */
void bMondPopCallback(void *ptr){
  Mondlicht();
  over = 1;  
}

/*
 * Button für manuell Licht aus
 */
void bOffPopCallback(void *ptr){
  Lichtaus();
  over = 1;  
}

/*
 * Button für Ende manuellen Sonnenuntergang
 */
void bRstPopCallback(void *ptr){
  Taglicht();
  over = 0;
}

/*
 * Zeit an Nextion schicken
 */
void ZeitanNextion(){
  get_Timep();
  endNextionCommand();
}

/*
 * Sensordaten lesen und an Display senden
 */
void readSensor(){
 humidity = dht.readHumidity();
 temperature = dht.readTemperature();
}

void Feuchtigkeit(){
  String feuchtigkeit = "tHumidity.txt=\""+String(humidity,1)+" %\"";
  Serial.print(feuchtigkeit);
  endNextionCommand();
}

void Temperatur(){
  String temperatur = "tTempC.txt=\""+String(temperature,1)+" C\"";
  Serial.print(temperatur);
  endNextionCommand();
}

/*
 * Lichtsteuerung
 * "over" steht für den Override, damit manuelle Eingaben nicht durch die Zeitsteuerung unterbrochen werden
 */
void Lichtsteuerung(){
  if (!over){  
  DateTime now = rtc.now();
  char zbuf3[]  = "hh:mm";
  String zString = now.toString(zbuf3);
    
    if (zString >= "00:01" && zString <= "06:29"){
      Lichtaus();
    }    
    if(zString == "06:30"){
      saufg = 1;
    }
    
    if(zString >= "07:00" && zString <= "21:29"){
      Taglicht();
    }
    
    if(zString == "21:30"){
      tagl = 0;
      suntg = 1;
    }
    
    if (zString >= "22:00" && zString <= "23:59"){
      Mondlicht();
    }
  }
}

void Lichtstatus(){
 if(tagl){
    Tag();
    endNextionCommand();
    }
 if(mond){
    Nacht();
    endNextionCommand();
    }
 if(suntg){
    Abend();
    endNextionCommand();
    }
 if(saufg){
    Morgen();
    endNextionCommand();
    }
 if(aus){
    Dunkel();
    endNextionCommand();
    }
  }

void endNextionCommand() //Nötig um einen Befehl an das Nextion TFT zu übergeben
{
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
}

/*
 * Zum debuggen den ganzen Teil aktivieren oder die gewünschten Parameter in den Loop kopieren.
 */

//void Debug()
//{
//  Serial.print("Sonnenaufgang: ");
//  Serial.print(saufg);
//  Serial.print(" / Sonnenuntergang: ");
//  Serial.print(suntg);
//  Serial.print(" / Mondlicht: ");
//  Serial.print(mond);
//  Serial.print(" / Taglicht: ");
//  Serial.print(tagl);
//  Serial.print(" / Override: ");
//  Serial.print(over);
//  Serial.println();
//  Serial.print("Lichtstatus: ");
//  Serial.println();
//  Serial.print(counter1);
//  Serial.print(" / ");
//  Serial.print(counter2);
//  Serial.print(" / ");
//  Serial.print(counter3);
//  Serial.print(" / ");
//  Serial.println(counter4);
//  }

void loop(){
  nexLoop(nex_listen_list);
  readSensor();
  Feuchtigkeit();
  Temperatur();
  ZeitanNextion();
  Lichtsteuerung();
  Lichtstatus();
  Sonnenstand();
  Serial.println();
  delay(1000);
//Debug();
}
