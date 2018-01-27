#include "display.h"
#include "interface.h"

const uint8_t matrixWidth = 15;  //total pixels
const uint8_t matrixHeight = 15; //total pixels
#define NUMBOARDS      9  //32 bits to hold 25 bits of data

#define TESTING 0


void setup() {
  analogWriteResolution(12);
  #if TESTING
  #else  
  interfaceSetup();
  #endif  
  displaySetup();
}

void loop()
{

  #if TESTING

    for (int i=0;i<matrixWidth;i++){
      for (int j=0;j<matrixHeight;j++){
        switch (millis()%15){
          case 0:
            displaySetPixel(i,j,0x00,0x00,0x00);
            break;
          case 1:
            displaySetPixel(i,j,0xdd,0xdd,0xdd);
            break;
          case 2:
            displaySetPixel(i,j,0xdd,0x3f,0x00);
            break;
          case 3:
            displaySetPixel(i,j,0xdd,0x7e,0x00);
            break;
          case 4:
            displaySetPixel(i,j,0xdd,0xbd,0x00);
            break;
          case 5:
            displaySetPixel(i,j,0xbd,0xdd,0x00);
            break;
          case 6:
            displaySetPixel(i,j,0x7e,0xdd,0x00);
            break;
          case 7:
            displaySetPixel(i,j,0x3f,0xdd,0x00);
            break;
          case 8:
            displaySetPixel(i,j,0x00,0xdd,0x00);
            break;
          case 9:
            displaySetPixel(i,j,0x00,0xdd,0x3f);
            break;
          case 10:
            displaySetPixel(i,j,0x00,0xdd,0x7e);
            break;
          case 11:
            displaySetPixel(i,j,0x00,0xdd,0xbd);
            break;
          case 12:
            displaySetPixel(i,j,0x00,0xbd,0xdd);
            break;
          case 13:
            displaySetPixel(i,j,0x00,0x7e,0xdd);
            break;
          case 14:
            displaySetPixel(i,j,0x00,0x3f,0xdd);
            break;
          case 15:
            displaySetPixel(i,j,0x00,0x00,0xdd);
            break;
        }
      }
    }
    //Serial.println(touchXY(14,14));
  #else
    interfaceCyclic();
    if (interfaceIsIdle()){
      displayIdle();
    }
  #endif

  displayShow();

  #if TESTING
    delay(5);
  #else
    delay(1);
  #endif
}

