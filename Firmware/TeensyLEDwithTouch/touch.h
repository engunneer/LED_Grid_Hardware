
#define T_PL 2  //pulse PL low to latch the current status of the shift register
#define T_CLK 9  //on rising edge, data will shift
#define T_SER 11 //data input

#define NUMCELLSPERBOARD 25  //32 bits to hold 25 bits of data
#define NUMBOARDS 9

/* Width of pulse to trigger the shift register to read and latch. */
#define PULSE_WIDTH_USEC   1

/* Array of voltages to use for dynamic sensing 1240 counts per volt*/
const int senseVoltages[] = { 0,200,400,600,800,1000,1200,1400 };
int currentVoltageStep;
uint8_t touchLevel[(NUMBOARDS * NUMCELLSPERBOARD)+1];

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

uint8_t touchGetLevel(int x, int y)
{
  return touchLevel[(uint16_t)touchXY(x,y)];
}

//byte touchGet2Levels(int x, int y)
//{
//  byte returnByte = 0;
//  //packs five bits starting from x,y increasing in x direction
//  //1XXX0XXX
//    returnByte = (touchGetLevel(x,y) << 4) | (touchGetLevel(x+1,y));
//  return returnByte | 0x80;
//}

void touchSetup(){
  pinMode(T_SER, INPUT_PULLUP);
  pinMode(T_CLK, OUTPUT);
  pinMode(T_PL, OUTPUT);

  //initial states
  digitalWrite(T_CLK, LOW);
  digitalWrite(T_PL, HIGH);

  currentVoltageStep = 0;
  analogWrite(A14, senseVoltages[currentVoltageStep]);
  }


void touchCyclic() {

  for(int i = 0; i < (NUMBOARDS); i++)
  {
    for(int j = 0; j < (NUMCELLSPERBOARD); j++)
    {
      int cellIndex = (i*NUMCELLSPERBOARD) + j;
      //default to not touched
      touchLevel[cellIndex] = 0;
    }
  }

  for (currentVoltageStep=0;currentVoltageStep<8;currentVoltageStep++)
  {
    //set voltage and delay to settle
    analogWrite(A14, senseVoltages[currentVoltageStep]);
    delayMicroseconds(PULSE_WIDTH_USEC*10);
    
    //start the clock HIGH
    digitalWriteFast(T_CLK, HIGH);
    delayMicroseconds(PULSE_WIDTH_USEC);
  
    //set PL to LOAD 
    digitalWriteFast(T_PL, LOW);
    delayMicroseconds(PULSE_WIDTH_USEC); // give the chips some time to do their job
    //delayMicroseconds(PULSE_WIDTH_USEC);
  
    //set PL to SHIFT
    digitalWriteFast(T_PL, HIGH);
    delayMicroseconds(PULSE_WIDTH_USEC);
    
    for(int i = 0; i < (NUMBOARDS); i++)
    {
      for(int j = 0; j < (NUMCELLSPERBOARD); j++)
      {
        int cellIndex = (i*NUMCELLSPERBOARD) + j;
        delayMicroseconds(PULSE_WIDTH_USEC);

        // get the bit
        if((boolean)(0x01- digitalRead(T_SER))) //touched
        {
          if (touchLevel[cellIndex] == 0)
            touchLevel[cellIndex] = currentVoltageStep;
        }
        /* Pulse the Clock (rising edge shifts the next bit).        */
        digitalWriteFast(T_CLK, LOW);
        delayMicroseconds(PULSE_WIDTH_USEC);
        digitalWriteFast(T_CLK, HIGH);
      }
      for(int j = 0; j < (32 - NUMCELLSPERBOARD); j++)
      {
        /* Pulse the Clock (rising edge shifts the next bit).
        Each board has 7 extra bits we don't care about
        */
        delayMicroseconds(PULSE_WIDTH_USEC);
        digitalWriteFast(T_CLK, LOW);
        delayMicroseconds(PULSE_WIDTH_USEC);
        digitalWriteFast(T_CLK, HIGH);
      }      
      //extra delay between boards
      delayMicroseconds(PULSE_WIDTH_USEC);
    }
    
    //leave the PL line at SHIFT
    digitalWriteFast(T_PL, HIGH);
    delayMicroseconds(PULSE_WIDTH_USEC); // give the chips some time to do their job
  }
  return;
}
  


