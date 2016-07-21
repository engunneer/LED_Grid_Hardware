// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            2

// How many NeoPixels are attached to the Arduino?
#define NUMBOARDS 6  //32 bits to hold 25 bits of data
#define NUMPIXELSPERBOARD      25


// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELSPERBOARD*NUMBOARDS, PIN, NEO_GRB + NEO_KHZ800);

void displaySetup(){
  
  pixels.begin(); // This initializes the NeoPixel library.

  //display test
  pixels.setBrightness(15);
  displayTest(209,0,0);
  displayTest(255,102, 34);
  displayTest(255,218,33);
  displayTest(51,221,0);
  displayTest(17,51,204);
  displayTest(34,0,102);
  displayTest(51,0,68);
  displayTest(0,0,0);
  pixels.setBrightness(255);
}

void displayTest(uint8_t r, uint8_t g, uint8_t b){
  for(int i=0;i<NUMPIXELSPERBOARD*NUMBOARDS;i++)
    setPixel(i, r, g, b);
  displayPixels();
  delay(50);
}

void displayPixels() {
    pixels.show(); // This sends the updated pixel color to the hardware.
}


void setPixel(int16_t i, uint8_t r, uint8_t g, uint8_t b){
  pixels.setPixelColor(i, pixels.Color(r,g,b)); 
  }
