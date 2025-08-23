#include <SoftwareSerial.h>

SoftwareSerial softSerial(6,7); //RX, TX

void setup() {
  softSerial.begin(9600);
  softSerial.print("?");
}

void loop() {
  softSerial.print("yukkuri sitettene\r");
  delay(5000);
}
