
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define NUMPIXELS      25

int pixelPointer = 0;
int colorPointer = 0;

void setup() {

displaySetup();
interfaceSetup();
touchSetup();

}

void loop() {


  long touchBits = touchGetData();

  //copy touchBits to Blue LEDs
  for(int i=0; i<NUMPIXELS; i++)
  {
    if ((touchBits>>i)&0x0001)
      setPixel(i,0,0,20);
    else
      setPixel(i,0,0,0);
  }

  
  displayPixels();
  
  //Serial.println(touchBits, BIN);
  delay(1);
}


