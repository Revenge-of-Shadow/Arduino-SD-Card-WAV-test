
//#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
#define SD_ChipSelectPin 10  //using digital pin 4 on arduino nano 328, can use other pins
#define DPin_Speaker      9
#include <SPI.h>
#include <SD.h>
#include <string.h>
#include <TMRpcm.h>

TMRpcm tmrpcm;   // create an object for use in this sketch


File root;




void setup(){
  
  tmrpcm.speakerPin = DPin_Speaker; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc
  tmrpcm.setVolume(6);
  Serial.begin(9600);
  
  noTone(DPin_Speaker);
  while (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");  
    tone(DPin_Speaker, 440, 100);
    delay(200);
    tone(DPin_Speaker, 440, 100);
    delay(200);
  }
  //tone(DPin_Speaker, 440, 200);
  root = SD.open("/");
  printDirectory(root);
}



void loop(){  
  //tone(8, 440, 200);

  //tmrpcm.play("sentry_scan.wav");
  delay(100);

}


void printDirectory(File dir) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    if (entry.isDirectory()) {
      printDirectory(entry);
      entry.close();
    } else {
      // files have sizes, directories do not
      
      String filename = entry.name();
      entry.close();
      
      String str = filename.substring(filename.length() - 3);
      str.toUpperCase();
      
      if(!strcmp(str.c_str(), "WAV")){
        Serial.print("> ");
        Serial.println(filename.c_str());
        tmrpcm.play(filename.c_str());
        while(tmrpcm.isPlaying()){delay(100);}
      }
    }
  }
}


