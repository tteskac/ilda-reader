#include <Arduino.h>
#include "Frame.h"
#include "FrameData.h"
#include <SD.h>

// Format spec: https://www.ilda.com/resources/StandardsDocs/ILDA_IDTF14_rev011.pdf

Frame::Frame(){}

bool Frame::getFrame(File file) {

  FrameData data;
  bool lastPoint;
  byte bytes[FrameData::NUMBER_OF_DATA_BYTES];

  // End of file...
  if (file.size() - (file.position() + Frame::NUMBER_OF_HEADER_BYTES) < Frame::NUMBER_OF_HEADER_BYTES + FrameData::NUMBER_OF_DATA_BYTES) {
    // false = no more frames to read.
    return false;
  }
  
  // Skip header data
  file.seek(file.position() + Frame::NUMBER_OF_HEADER_BYTES);
  
  do
  {
    file.read(bytes, FrameData::NUMBER_OF_DATA_BYTES);
    lastPoint = isLastPoint(bytes);
    data.x = (bytes[FrameData::X_BYTE] * 256) | (bytes[FrameData::X_BYTE + 1]);
    data.y = (bytes[FrameData::Y_BYTE] * 256) | (bytes[FrameData::Y_BYTE + 1]);
    data.laserOn = !getBit(bytes[FrameData::STATUS_BYTE], FrameData::LASER_ON_BIT);
    //this.frameData.Add(data); 

    // DEBUG - remove this when you don't need it! Read speed will be reduced from 20ms to 20us !!!
    Serial.print("Point: ");
    Serial.print(data.x);
    Serial.print(", ");
    Serial.print(data.y);
    Serial.print(", ");
    Serial.println(data.laserOn);

    // TODO: do here whatever you need to do with this point.

  // Read next if not last.
  } while (!lastPoint);

  // true = no more points in current frame to read.
  return true;
}

// Get the last-point-bit-flag from status byte x
bool Frame::isLastPoint(byte* bytes)
{
  return getBit(bytes[FrameData::STATUS_BYTE], FrameData::LAST_POINT_BIT);
}

// Helpter function to get arbitrary bit value from byte.
bool Frame::getBit(byte b, int bitNumber)
{
  return (b & (1 << bitNumber - 1)) != 0;
}
