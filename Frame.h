#include <Arduino.h>
#include <SD.h>

// Format spec: https://www.ilda.com/resources/StandardsDocs/ILDA_IDTF14_rev011.pdf

class Frame
{
  public:
    Frame();
    bool getFrame(File file);

   private:
    bool isLastPoint(byte* bytes);
    bool getBit(byte b, int bitNumber);

  public:
    static const int NUMBER_OF_HEADER_BYTES = 32;
    
};
