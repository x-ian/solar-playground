#include <VirtualWire.h>

const int transmit_pin = 12;

void setup()
{
  Serial.begin(57600);
  vw_set_tx_pin(transmit_pin);
  vw_setup(2000);   // Bits per sec
}

byte count = 1;

void loop()
{
  byte msgType = 66;
  byte probeId = 3;
  byte timeBlock = 57;
  byte ah = 2;
  
  byte msg[6] = {msgType, probeId, timeBlock, ah, '#', msgType};

  msg[4] = count;
  vw_send((uint8_t *)msg, 6);
  vw_wait_tx(); // Wait until the whole message is gone
  Serial.println("send");
  delay(1000);
  count = count + 1;
}
