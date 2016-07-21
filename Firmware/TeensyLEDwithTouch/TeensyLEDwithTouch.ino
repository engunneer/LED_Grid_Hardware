#include "display.h"
#include "touch.h"
#include "interface.h"

const uint8_t matrixWidth = 15;  //total pixels
const uint8_t matrixHeight = 15; //total pixels
#define NUMBOARDS      9  //32 bits to hold 25 bits of data

#define TESTING 0

void setup() {
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
        if (touchGetBit(i,j))
          displaySetPixel(i,j,200,0,00);
        else
          displaySetPixel(i,j,0,20,0);
      }
    }
    //Serial.println(touchXY(14,14));
  #else
    interfaceCyclic();
  #endif

  displayShow();

  #if TESTING
    delay(20);
  #else
    delay(1);
  #endif
}

