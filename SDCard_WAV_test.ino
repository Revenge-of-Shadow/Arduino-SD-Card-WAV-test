
#define SD_ChipSelectPin 10  
#define DPin_Speaker      9
#include <SPI.h>
#include <SD.h>
#include <string.h>
#include <TMRpcm.h>

TMRpcm tmrpcm; 
File root;




void setup(){
  
  tmrpcm.speakerPin = DPin_Speaker; 
  tmrpcm.setVolume(6);
  Serial.begin(9600);
  
  noTone(DPin_Speaker);

  while (!SD.begin(SD_ChipSelectPin)) {  
    Serial.println("SD fail");  
    tone(DPin_Speaker, 440, 100);
    delay(200);
    tone(DPin_Speaker, 440, 100);
    delay(200);
  }
  
  root = SD.open("/");
  printDirectory(root);
}



void loop(){  
  delay(100);

}


void printDirectory(File dir) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // No more files present.
      break;
    }
    if (entry.isDirectory()) {

      printDirectory(entry);
      entry.close();
    } 
    else {

      String filename = entry.name();
      entry.close();
      
      String str = filename.substring(filename.length() - 3);
      str.toUpperCase();
      
      if(!strcmp(str.c_str(), "WAV")){
        Serial.print("> ");
        Serial.println(filename.c_str());
        tmrpcm.play(filename.c_str());

        while(tmrpcm.isPlaying()){
          delay(100);
          }
      }
    }
  }
}


