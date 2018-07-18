#include "IldaReader.h"
#include "Frame.h"
#include <SD.h>

IldaReader::IldaReader() {}

bool IldaReader::init(int csPin) {
  Serial.print("Initializing SD card...");
  if (!SD.begin(csPin)) {
    Serial.println("initialization failed!");
    return false;
  }
  Serial.println("initialization done.");

  root = SD.open("/");
  Serial.println("Root selected!");
}

bool IldaReader::openFile(String fileName) {
  file = SD.open(fileName, FILE_READ);
  if (! file) {
    Serial.println("Error opening file!");
    return false;
  }
  return true;
}

void IldaReader::readFile() {

  // Read first 32 header bytes from the file and check if the first 4 bytes in ASCII are "ILDA".
  checkHeader();
  
  // Read actual data from ILD file.
  Frame frame;
  int t1,t2,i=0;
  t1 = micros();
  // Read all points from one frame and try again if there are more frames.
  while(frame.getFrame(file)) {
    Serial.print("Frame ");
    Serial.print(++i);
    Serial.println(" end");
  }
  t2 = micros();

  // Some measurement.
  Serial.print("Read time (us): ");
  Serial.println(t2-t1);

}

// Read first 32 header bytes from the file and check if the first 4 bytes in ASCII are "ILDA".
bool IldaReader::checkHeader() {
  byte buf[Frame::NUMBER_OF_HEADER_BYTES];
  file.read(buf, Frame::NUMBER_OF_HEADER_BYTES);
  
  String header = "";
  for (int i = 0; i < 4; i++) {
    header += char(buf[i]);
  }
  
  if (header != "ILDA") {
    Serial.println("INVALID FILE!");
    return false;
  }

  // Return back to start of the file.
  file.seek(0);

  return true;
}

void IldaReader::closeFile() {
  file.close();
}

