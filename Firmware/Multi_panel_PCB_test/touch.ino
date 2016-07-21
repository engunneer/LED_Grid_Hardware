#define T_PL 3  //pulse PL low to latch the current status of the shift register
#define T_CLK 4  //on rising edge, data will shift
#define T_SER 5 //data input

#define NUMBYTESPERBOARD 4  //32 bits to hold 25 bits of data
#define NUMBOARDS 6  //32 bits to hold 25 bits of data

uint32_t boardBits[NUMBOARDS];

void touchSetup(){
  pinMode(T_SER, INPUT_PULLUP);
  pinMode(T_CLK, OUTPUT);
  pinMode(T_PL, OUTPUT);

  //initial states
  digitalWrite(T_CLK, LOW);
  digitalWrite(T_PL, HIGH);

  
  }

uint32_t touchGetBoardBits(int boardnum)
{
  return boardBits[boardnum];
}

void touchCyclic() {

  uint8_t touchBits [NUMBYTESPERBOARD];
  
  //start the clock high
  digitalWrite(T_CLK, HIGH);

  //latch the registers
  digitalWrite(T_PL, LOW);
  digitalWrite(T_PL, HIGH);

  //shift the data
  for (uint8_t j= 0; j<NUMBOARDS; j++)
  {
    for (uint8_t i= 0; i<NUMBYTESPERBOARD; i++)
    {
      touchBits[i] = shiftIn(T_SER, T_CLK, LSBFIRST);
      touchBits[i] = ~touchBits[i];
    }
    boardBits[j] = (((uint32_t)touchBits[3] << 24) | ((uint32_t)touchBits[2] << 16) | ((uint32_t)touchBits[1] << 8) | ((uint32_t)touchBits[0]));
  }
  return;
  
  }

