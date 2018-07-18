
#include <SPI.h>
#include "IldaReader.h"

/*
   SDCARD WIRING FOR NODEMCU:
   SS/CS   GPIO 4  (D2)
   SCK     GPIO 14 (D5/CLK)
   MISO    GPIO ?  (D6)
   MOSI    GPIO ?  (D7)
*/

int ledPin = D0; // GPIO16
IldaReader ildaReader;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  delay(10);
  digitalWrite(ledPin, HIGH);

  // Init connection with SD card adapter on CS pin D2.
  if(ildaReader.init(D2)) {
    Serial.println("Try to read ILDA file.");
    if(ildaReader.openFile("RANDOM2.ILD")) {
      ildaReader.readFile();
      ildaReader.closeFile();
    }
  }
  
}

void loop() {
  // NOP
}



