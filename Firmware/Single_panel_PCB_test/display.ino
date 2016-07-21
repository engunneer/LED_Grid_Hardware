// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            2

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      25

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int pixelsR [NUMPIXELS];
int pixelsG [NUMPIXELS];
int pixelsB [NUMPIXELS];


void displaySetup(){
  
  pixels.begin(); // This initializes the NeoPixel library.

  //display test
  for(int i=0;i<NUMPIXELS;i++){
    pixelsR[i] = i * (32 / NUMPIXELS) + 32;
    displayPixels();
    delay(10);
  }
  for(int i=0;i<NUMPIXELS;i++){
    pixelsR[i] = 0;
    pixelsG[i] = i * (32 / NUMPIXELS) + 32;
    displayPixels();
    delay(10);
  }
  for(int i=0;i<NUMPIXELS;i++){
    pixelsG[i] = 0;
    pixelsB[i] = i * (32 / NUMPIXELS) + 32;
    displayPixels();
    delay(10);
  }
  for(int i=0;i<NUMPIXELS;i++){
    pixelsB[i] = 0;
    displayPixels();
    delay(10);
  }

}

void displayPixels() {
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(pixelsR[i],pixelsG[i],pixelsB[i])); 

  }
    pixels.show(); // This sends the updated pixel color to the hardware.
}


void setPixel(int i, int r, int g, int b){
  pixelsR[i] = r;
  pixelsG[i] = g;
  pixelsB[i] = b;
  }
