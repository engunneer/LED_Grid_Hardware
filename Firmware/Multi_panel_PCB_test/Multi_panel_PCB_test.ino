
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define NUMBOARDS 6  //32 bits to hold 25 bits of data
#define NUMPIXELSPERBOARD      25
#define NUMTOUCHBYTESPERBOARD 4  //32 bits to hold 25 bits of data

#define TESTING 1
void setup() {

#if TESTING
  interfaceSetup();
#endif  
  displaySetup();
  touchSetup();

}

void loop() {

  touchCyclic();

#if TESTING
    //copy touchBits to LEDs for testing
    for(int j=0; j<NUMBOARDS; j++)
    {
      uint32_t boardBits = touchGetBoardBits(j);
      Serial.print(j + ": ");
      Serial.println(boardBits, BIN);
      for(int i=0; i<NUMPIXELSPERBOARD; i++)
      {
        if ((boardBits>>i)&0x0001)
          setPixel((j*NUMPIXELSPERBOARD) + i,0,0,5);
        else
          setPixel((j*NUMPIXELSPERBOARD) + i,0,5,0);
      }
    }
#else
    interfaceCyclic();
#endif

  displayPixels();
  
  #if TESTING
    delay(20);
  #else
    delay(1);
  #endif
}


