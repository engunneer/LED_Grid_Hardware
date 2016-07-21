#include "display.h"
#include "touch.h"
#include "interface.h"

const uint8_t matrixWidth = 15;  //total pixels
const uint8_t matrixHeight = 15; //total pixels
#define NUMBOARDS      9  //32 bits to hold 25 bits of data

#define TESTING 1


void setup() {
  analogWriteResolution(12);
  #if TESTING
  #else  
  interfaceSetup();
  #endif  
  displaySetup();
  touchSetup();
}

void loop()
{
  touchCyclic();
  
  #if TESTING

    for (int i=0;i<matrixWidth;i++){
      for (int j=0;j<matrixHeight;j++){
        switch (touchGetLevel(i,j)){
          case 0:
            displaySetPixel(i,j,0x00,0x00,0x00);
            break;
          case 1:
            displaySetPixel(i,j,0xFF,0x00,0x00);
            break;
          case 2:
            displaySetPixel(i,j,0xFF,0x54,0x00);
            break;
          case 3:
            displaySetPixel(i,j,0xFF,0xAA,0x00);
            break;
          case 4:
            displaySetPixel(i,j,0xFF,0xFF,0x00);
            break;
          case 5:
            displaySetPixel(i,j,0xAA,0xFF,0x00);
            break;
          case 6:
            displaySetPixel(i,j,0x54,0xFF,0x00);
            break;
          case 7:
            displaySetPixel(i,j,0x00,0xFF,0x00);
            break;
        }
      }
    }
    //Serial.println(touchXY(14,14));
  #else
    interfaceCyclic();
  #endif

  displayShow();

  #if TESTING
    delay(5);
  #else
    delay(1);
  #endif
}

