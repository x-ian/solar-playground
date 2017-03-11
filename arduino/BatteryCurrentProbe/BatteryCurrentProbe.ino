// https://github.com/PaulStoffregen/Time
#include <TimeLib.h> 

// https://github.com/PaulStoffregen/DS1307RTC
#include <DS1307RTC.h> 

#include <EEPROM.h>

#include <Wire.h>

// https://www.pjrc.com/teensy/td_libs_VirtualWire.html
// superceded by RadioHead http://www.airspayce.com/mikem/arduino/RadioHead/
#include <VirtualWire.h>

// low level RTC comm: https://www.frag-duino.de/index.php/maker-faq/26-ds1307-real-time-clock-modul-mit-arduino-ansteuern

const int eepromStorageMostRecentElementAddress = 1;

const int eepromStorageStartAddress = 11;
const int eepromStorageMaxElements = 10;
const int eepromStorageBytesOfOneElement = 2 + 2;

const int batteryId = 1;

const int transmit_pin = 12;

void setup(){
 while (!Serial) {
    delay(1);  // for Leonardo/Micro/Zero
  }
  Wire.begin();
  Serial.begin(57000);
  Serial.println("setup");
  
  //eepromClear();
  //printCurrentEeprom();

  //setTime();
  setupRTC();
  printCurrentTimestamp();

  setupRF433();
}

void setupRF433() {
  vw_set_tx_pin(transmit_pin);
  vw_setup(2000);   // Bits per sec
}

void printCurrentEeprom() {
  int nextPosition = getEepromStorageMostRecentPosition();
  for (int i = 0; i < eepromStorageMaxElements; i++) {
    Serial.print("@");
    Serial.print(nextPosition);
    Serial.print(": ");
    unsigned int timeBlock = 0;
    EEPROM.get(nextPosition, timeBlock);
    //Serial.print(EEPROM.read(nextPosition));
    Serial.print(timeBlock);
    Serial.print(" ");
    int value = 0;
    EEPROM.get(nextPosition+2, value);
    //Serial.println(EEPROM.read(nextPosition+2));
    Serial.println(value);

    nextPosition = nextPosition - eepromStorageBytesOfOneElement;
    if (nextPosition < eepromStorageStartAddress) {
      // overflow in eeprom storage, go back to end
      nextPosition = eepromStorageStartAddress + ((eepromStorageMaxElements - 1) * eepromStorageBytesOfOneElement);
    }
  }
}

void setupRTC() {
/*     
  if (RTC.chipPresent()) {
    Serial.println("The DS1307 is stopped. Please run the SetTime");
    Serial.println("example to initialize the time and begin running.");
    Serial.println();
  } else {
    Serial.println("DS1307 read error!  Please check the circuitry.");
    Serial.println();
  }
*/

  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus()!= timeSet) 
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time"); 
}

void loop(){
  //printCurrentTimestamp();
  byte value = (byte) random();
  //unsigned int timeBlocks = now15MinBlocks();
  unsigned int timeBlocks = nowMinBlocks();

  storeInEeprom(timeBlocks, value);
  //printCurrentEeprom();
  
  transmitData(timeBlocks, value);
  
  Serial.println();
  delay(60000);
 }

byte count = 1;

void transmitData(unsigned int timeBlocks, byte value) {
  byte msgType = 66;
  
  byte msg[7] = {msgType, batteryId, '#', highByte(timeBlocks), lowByte(timeBlocks), value, msgType};

  msg[2] = count;
  vw_send((uint8_t *)msg, 7);
  vw_wait_tx(); // Wait until the whole message is gone
  Serial.print("transmit: ");
  Serial.print(msg[0]);
  Serial.print(" (msg type)   ");
  Serial.print(msg[1]);
  Serial.print(" (bat id)   ");
  Serial.print(msg[2]);
  Serial.print(" (msg count)   ");
  Serial.print(msg[3]);
  Serial.print(" (time block high)   ");
  Serial.print(msg[4]);
  Serial.print(" (time block low)   ");
  Serial.print(msg[5]);
  Serial.print(" (value) ");
  Serial.println(msg[6]);
  
  count = count + 1;
}

int getEepromStorageMostRecentPosition() {
  int eepromStoragePointer = EEPROM.read(eepromStorageMostRecentElementAddress);
//  if (eepromStoragePointer == 0) {
//    // assume fresh EEPROM, start from beginning
//    eepromStoragePointer = 11;
//  }
  return eepromStoragePointer;
}

void storeInEeprom(unsigned int timeBlocks, byte value) {
  int mostRecentPosition = getEepromStorageMostRecentPosition();
  int nextPosition = mostRecentPosition + eepromStorageBytesOfOneElement;
  if (mostRecentPosition == 0) {
    // nothing was saved yet, set nextPosition to start of array
    nextPosition = eepromStorageStartAddress;
  }
  if (nextPosition >= (eepromStorageStartAddress + (eepromStorageMaxElements * eepromStorageBytesOfOneElement))) {
    // overflow in eeprom storage, go back to initial start
    nextPosition = eepromStorageStartAddress;
  }
  EEPROM.put(nextPosition, timeBlocks);
  EEPROM.put(nextPosition + 2, value);
  EEPROM.put(eepromStorageMostRecentElementAddress, nextPosition);
}

unsigned int now15MinBlocks() {
    // 1483228800 unix epoch for 2017-01-01 00:00:00
    return (unsigned int) ((now() - 1483228800l) / 900);  
}

unsigned int nowMinBlocks() {
    // 1483228800 unix epoch for 2017-01-01 00:00:00
    return (unsigned int) ((now() - 1483228800l) / 60);  
}

void eepromClear() {
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
  Serial.println("eeprom cleared");
}

void printCurrentTimestamp(){
  tmElements_t tm;
  if (RTC.read(tm)) {
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.print('-');
    Serial.print(tm.Month);
    Serial.print('-');
    Serial.print(tm.Day);
    Serial.print(' ');
    print2digits(tm.Hour);
    Serial.print('-');
    print2digits(tm.Minute);
    Serial.print('-');
    print2digits(tm.Second);
    Serial.println();

    Serial.print("secs since 1/1/70: ");
    Serial.println(now());

    Serial.print("15 min blocks since 1/1/70: ");
    Serial.println(now() / 900);

    // 1483228800 unix epoch for 2017-01-01 00:00:00
    Serial.print("15 min blocks since 1/1/17: ");
    Serial.println(now15MinBlocks());
    
  }
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}
