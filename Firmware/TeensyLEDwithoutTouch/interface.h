//serial notes for teensy  http://www.pjrc.com/teensy/td_serial.html
#define maxRow 15
#define maxCol 15

#define bufferLength 10
#define bufferLengthOut 230 

#define BYTESPERPIXEL 6

#define LED 13
bool LEDstate = false;

byte inputBuffer[bufferLength];
byte outputBuffer[bufferLengthOut];
int inputCount = 0;
int outputCount = 0;

void interfaceSetup(){  // initialize serial:
  Serial.begin(230400);
  Serial.setTimeout(1); 

  pinMode(LED, OUTPUT);

  }
  
void interfaceCyclic()
{
  while (Serial.available()) {
  byte c = Serial.read();
    if ((c == 255) && (inputCount>=BYTESPERPIXEL)) {
      //EOM
      byte xCoord = inputBuffer[0]; //row
      byte yCoord = inputBuffer[1]; //col
      byte value1 = inputBuffer[2];
      byte value2 = inputBuffer[3];
      byte value3 = inputBuffer[4];
      byte colorMode = inputBuffer[5];
      if ((xCoord < maxCol) && (yCoord < maxRow))
      {
        if (colorMode == 0)
          displaySetPixel(xCoord, yCoord, value1, value2, value3);
        else if (colorMode == 1)
          displaySetPixelHSV(xCoord, yCoord, value1, value2, value3);
      }
      else
      {
        //special commands
        if (xCoord == 100)
          displaySetBrightness(value1);
      }
      inputCount = 0;

    } else {
      inputBuffer[inputCount] = c;
      inputCount++;
    }
  }
  
  
}
