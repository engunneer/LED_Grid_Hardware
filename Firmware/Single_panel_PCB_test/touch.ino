#define T_PL 3  //pulse PL low to latch the current status of the shift register
#define T_CLK 4  //on rising edge, data will shift
#define T_SER 5 //data input

#define NUMINPUTS 25
#define NUMBYTES 4  //32 bits to hold 25 bits of data


void touchSetup(){
  pinMode(T_SER, INPUT_PULLUP);
  pinMode(T_CLK, OUTPUT);
  pinMode(T_PL, OUTPUT);

  //initial states
  digitalWrite(T_CLK, LOW);
  digitalWrite(T_PL, HIGH);

  
  }

long touchGetData() {
  byte touchBits [NUMBYTES];

  //start the clock high
  digitalWrite(T_CLK, HIGH);

  //latch the registers
  digitalWrite(T_PL, LOW);
  digitalWrite(T_PL, HIGH);

  //shift the data
  for (int i= 0; i<NUMBYTES; i++)
  {
    touchBits[i] = shiftIn(T_SER, T_CLK, LSBFIRST);
    touchBits[i] = ~touchBits[i];
    delay(10);
  }


  return (((long)touchBits[3] << 24) | ((long)touchBits[2] << 16) | ((long)touchBits[1] << 8) | ((long)touchBits[0]));
  }

