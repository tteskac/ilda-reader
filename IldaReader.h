#include <WString.h>
#include <SD.h>

class IldaReader
{
  public:
    IldaReader();
    bool init(int csPin);
    bool openFile(String fileName);
    bool checkHeader();
    void readFile();
    void closeFile();
    
  public:
    File root;
    File file;
 
};

