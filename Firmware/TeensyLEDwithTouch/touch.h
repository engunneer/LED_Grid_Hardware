
#define T_PL 2  //pulse PL low to latch the current status of the shift register
#define T_CLK 9  //on rising edge, data will shift
#define T_SER 11 //data input

#define NUMBITSPERBOARD 25  //32 bits to hold 25 bits of data
#define NUMBOARDS 9

/* Width of pulse to trigger the shift register to read and latch. */
#define PULSE_WIDTH_USEC   2

boolean touchBit[(NUMBOARDS * NUMBITSPERBOARD)+1];

uint16_t touchXY( uint8_t x, uint8_t y)
{
  uint16_t i;

  //cribbed from NeoMatrix, but with all options removed
      uint16_t minor, major, majorScale;

      uint16_t tile;

      minor = x / kTileWidth;            // Tile # X/Y; presume row major 
      major = y / kTileHeight;
      x     = x - (minor * kTileWidth);  // Pixel X/Y within tile
      y     = y - (major * kTileHeight); // (-* is less math than modulo)

      // Determine actual major axis of tiling
      majorScale = kMatrixWidth / kTileWidth;

      // Determine tile number
      tile = (major * majorScale) + minor;

      // Index of first pixel in tile
      uint16_t tileOffset = tile * kTileWidth * kTileHeight;

    // Determine pixel number within tile/matrix
      uint16_t pixelOffset = (y * kTileWidth) + x;

  i = pixelOffset + tileOffset;
  return i;
}

boolean touchGetBit(int x, int y)
{
  return touchBit[(uint16_t)touchXY(x,y)];
}

byte touchGet5Bits(int x, int y)
{
  byte returnByte = 0;
  //packs five bits starting from x,y increasing in x direction
  //100XXXXX
  for(int i=0; i<5; i++){
    returnByte |= (touchGetBit(x+i,y) << (i));
  }
  return returnByte | 0x80;
}

void touchSetup(){
  pinMode(T_SER, INPUT_PULLUP);
  pinMode(T_CLK, OUTPUT);
  pinMode(T_PL, OUTPUT);

  //initial states
  digitalWrite(T_CLK, LOW);
  digitalWrite(T_PL, HIGH);

  }


void touchCyclic() {
  //start the clock HIGH
  digitalWriteFast(T_CLK, HIGH);
  delayMicroseconds(PULSE_WIDTH_USEC);

  //set PL to LOAD 
  digitalWriteFast(T_PL, LOW);
  delayMicroseconds(PULSE_WIDTH_USEC); // give the chips some time to do their job
  delayMicroseconds(PULSE_WIDTH_USEC);

  //set PL to SHIFT
  digitalWriteFast(T_PL, HIGH);
  delayMicroseconds(PULSE_WIDTH_USEC);
  
for(int i = 0; i < (NUMBOARDS); i++)
  {
    for(int j = 0; j < (NUMBITSPERBOARD); j++)
    {
      int bitIndex = (i*NUMBITSPERBOARD) + j;
        delayMicroseconds(PULSE_WIDTH_USEC);

        // get the bit
        touchBit[bitIndex] = (boolean)(0x01- digitalRead(T_SER));
        /* Pulse the Clock (rising edge shifts the next bit).        */
        digitalWriteFast(T_CLK, LOW);
        delayMicroseconds(PULSE_WIDTH_USEC);
        digitalWriteFast(T_CLK, HIGH);
    }
    for(int j = 0; j < (32 - NUMBITSPERBOARD); j++)
    {
          /* Pulse the Clock (rising edge shifts the next bit).
          Each board has 7 extra bits we don't care about
          */
          delayMicroseconds(PULSE_WIDTH_USEC);
          digitalWriteFast(T_CLK, LOW);
          delayMicroseconds(PULSE_WIDTH_USEC);
          digitalWriteFast(T_CLK, HIGH);
    }      
    //extra delay betwen boards
    delayMicroseconds(PULSE_WIDTH_USEC*10);
  }

  //leave the PL line at SHIFT
  digitalWriteFast(T_PL, HIGH);
  delayMicroseconds(PULSE_WIDTH_USEC); // give the chips some time to do their job

  return;
}
  


