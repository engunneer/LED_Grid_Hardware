#include <FastLED.h>

#define LED_PIN  8

#define COLOR_ORDER GRB
#define CHIPSET     WS2812

#define DEFAULT_BRIGHTNESS 128

// Params for width and height
const uint8_t kMatrixWidth = 15;  //total pixels
const uint8_t kMatrixHeight = 15; //total pixels
const uint8_t kTileWidth = 5;     //single tile
const uint8_t kTileHeight = 5;    //single tile

#define NUM_LEDS (kMatrixWidth * kMatrixHeight)

CRGB leds_plus_safety_pixel[ NUM_LEDS + 1];
CRGB* const leds( leds_plus_safety_pixel + 1);

uint16_t displayXY( uint8_t x, uint8_t y)
{
  uint16_t i;

  //cribbed from NeoMatrix, but with all options removed
      uint16_t minor, major, majorScale;

      uint16_t tile;

      minor = x / kTileWidth;            // Tile # X/Y; presume row major to
      major = y / kTileHeight,           // start (will swap later if needed)
      x     = x - (minor * kTileWidth);  // Pixel X/Y within tile
      y     = y - (major * kTileHeight); // (-* is less math than modulo)

      // Determine actual major axis of tiling
      majorScale = kMatrixWidth / kTileWidth;

      // Determine tile number
      tile = major * majorScale + minor;

      // Index of first pixel in tile
      uint16_t tileOffset = tile * kTileWidth * kTileHeight;
    // Determine pixel number within tile/matrix
      uint16_t pixelOffset = y * kTileWidth + x;
  
    i = pixelOffset + tileOffset;
  
  return i;
}

uint16_t displayXYsafe( uint8_t x, uint8_t y)
{
  if( x >= kMatrixWidth) return -1;
  if( y >= kMatrixHeight) return -1;
  return displayXY(x,y);
}


void displayShow(){
    FastLED.show();
}

void displaySetPixel(int16_t raw_index, uint8_t r, uint8_t g, uint8_t b){
  leds[ raw_index ] = CRGB( r, g, b);
  }
void displaySetPixel(int16_t i,int16_t j, uint8_t r, uint8_t g, uint8_t b){
  leds[ displayXYsafe( i, j ) ] = CRGB( r, g, b);
  }
void displaySetPixelHSV(int16_t raw_index, uint8_t h, uint8_t s, uint8_t v){
  leds[ raw_index ] = CHSV( h, s, v);
  }
void displaySetPixelHSV(int16_t i,int16_t j, uint8_t h, uint8_t s, uint8_t v){
  leds[ displayXYsafe( i, j ) ] = CHSV( h, s, v);
  }

void displayTest(uint8_t r, uint8_t g, uint8_t b){
  for (int i=0;i<kMatrixWidth;i++)
    for (int j=0;j<kMatrixHeight;j++)
      displaySetPixel(i,j, r, g, b);
  displayShow();
  delay(100);
}

void displayIdle(){
  for (int i=0;i<kMatrixWidth;i++)
    for (int j=0;j<kMatrixHeight;j++)
    {      
      int hue = (int)(millis()>>8);
      displaySetPixelHSV(i,j, hue, 192, 128);
    }
    displayShow();
}


void displaySetBrightness(int brightnessValue)
{
  FastLED.setBrightness( brightnessValue );
}

void displaySetup(){
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  displaySetBrightness( DEFAULT_BRIGHTNESS );

  displayTest(209,0,0);
  displayTest(255,102, 34);
  displayTest(255,218,33);
  displayTest(51,221,0);
  displayTest(17,51,204);
  displayTest(34,0,102);
  displayTest(51,0,68);
  displayTest(0,0,0);

}

