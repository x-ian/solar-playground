/* -------------------------------------------
/* DS1307 I2C Zeit seriell lesen und schreiben
/* www.frag-duino.de
/* -------------------------------------------
/* Befehle:
/* settime 23:45:58 (hh:mm:ss)
/* setdate 23.01.87 (tt.mm.jj)
/* gettime --> Ausgabe 23:45:23
/* getdate --> Ausgabe 12.02.13
 ------------------------------------------- */
 
 
// Includes
#include <Wire.h>
 
// Konstanten
#define DS1307_ADRESSE 0x68 // I2C Addresse
 
// Variablen
char c;
String readString = "";
int sekunde, minute, stunde, tag, wochentag, monat, jahr;
 
void setup(){
 while (!Serial) {
    delay(1);  // for Leonardo/Micro/Zero
  }
  Wire.begin();
  Serial.begin(57000);
  Serial.println("Uhr initialisiert. Verfuegbare Befehle:\n - gettime\n - getdate\n - settime hh:mm:ss\n - setdate dd:mm:yy");
}
 
void loop(){
  while (Serial.available()) {
    // Input lesen
    delay(3);
    char c = Serial.read();
    readString += c;
  }
 
  if (readString.length() >0) {
    // Input verarbeiten
 
    if(readString.substring(0,7)=="settime"){
      Serial.print("settime> Setze Uhrzeit. Vorher: ");
      ausgabe(true);
      stunde=readString.substring(8,10).toInt();
      minute=readString.substring(11,13).toInt();
      sekunde=readString.substring(14,16).toInt();
      eingabe();
      delay(100);
      Serial.print("Uhrzeit nachher: ");
      ausgabe(true);
    }
    else if(readString.substring(0,7)=="setdate"){
      Serial.print("setdate> Setze Datum. Vorher: ");
      ausgabe(false);
      tag=readString.substring(8,10).toInt();
      monat=readString.substring(11,13).toInt();
      jahr=readString.substring(14,16).toInt();
      eingabe();
      delay(100);
      Serial.print("Datum nachher: ");
      ausgabe(false);
    }
    else if(readString.substring(0,7)=="gettime"){
      Serial.print("gettime> ");
      ausgabe(true);
    }
    else if(readString.substring(0,7)=="getdate"){
      Serial.print("getdate> ");
      ausgabe(false);
    }
    else
    {
      Serial.print("Unbekannter Befehl: ");
      Serial.println(readString);
    }
 
    readString="";
  }
  delay(1000);
}
 
void ausgabe(boolean zeit){
  // True=Zeit ausgeben. False = Datum ausgeben
 
  // Initialisieren
  Wire.beginTransmission(DS1307_ADRESSE);
  Wire.write(0x00);
  Wire.endTransmission();
 
  Wire.requestFrom(DS1307_ADRESSE, 7);
 
  sekunde = bcdToDec(Wire.read());
  minute = bcdToDec(Wire.read());
  stunde = bcdToDec(Wire.read() & 0b111111);
  wochentag = bcdToDec(Wire.read());
  tag = bcdToDec(Wire.read());
  monat = bcdToDec(Wire.read());
  jahr = bcdToDec(Wire.read());
 
  // Ausgabe
  if(zeit){
    Serial.print(stunde);
    Serial.print(":");
    Serial.print(minute);
    Serial.print(":");
    Serial.println(sekunde);
  }
  else
  {
    Serial.print(tag);
    Serial.print(".");
    Serial.print(monat);
    Serial.print(".");
    Serial.println(jahr);
  }
}
 
void eingabe(){
  // Setzt die aktuelle Zeit
 
  Wire.beginTransmission(DS1307_ADRESSE);
  Wire.write(0x00);
  Wire.write(decToBcd(sekunde));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(stunde));
  Wire.write(decToBcd(wochentag));
  Wire.write(decToBcd(tag));
  Wire.write(decToBcd(monat));
  Wire.write(decToBcd(jahr));
  Wire.write(0x00);
  Wire.endTransmission();
}
 
// Hilfsfunktionen
byte decToBcd(byte val) {
  return ((val/10*16) + (val%10));
}
byte bcdToDec(byte val) {
  return ((val/16*10) + (val%16));
}
