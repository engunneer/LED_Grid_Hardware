#include "display.h"


const uint8_t matrixWidth = 15;  //total pixels
const uint8_t matrixHeight = 15; //total pixels
#define NUMBOARDS      9  //32 bits to hold 25 bits of data



void setup() {
  displaySetup();
}

void loop()
{

  uint32_t ms = millis();
    int32_t yHueDelta32 = ((int32_t)cos16( ms * 27 ) * (350 / kMatrixWidth));
    int32_t xHueDelta32 = ((int32_t)cos16( ms * 39 ) * (310 / kMatrixHeight));
    DrawOneFrame( ms / 65536, yHueDelta32 / 32768, xHueDelta32 / 32768);
    FastLED.show();

/*    for (int i=0;i<matrixWidth;i++){
      for (int j=0;j<matrixHeight;j++){
        displaySetPixelHSV(i,j,i<<4,0xc0,j<<4);
      }
    }
    //Serial.println(touchXY(14,14));
*/
  displayShow();

    delay(1);
}

