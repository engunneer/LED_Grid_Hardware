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
int secondsSinceConnection = 0;
long millisAtLastSerial;

boolean interfaceIsIdle(){
  return (secondsSinceConnection > 3);
}

void interfaceSetup(){  // initialize serial:
  Serial.begin(921600);
  Serial.setTimeout(1); 

  pinMode(LED, OUTPUT);

  }
  
void interfaceCyclic()
{
  
  while (Serial.available()) {
  millisAtLastSerial = millis();
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

      //if we get a message for the last pixel, trigger a sending of all touch data
      if((xCoord == (maxCol-1))&&(yCoord==(maxRow-1))){
        //pack the touch bits and ship them out
        outputCount = 0;
        for(int row=0;row<maxRow;row++){
          for(int col=0;col<maxCol;col++){
            outputBuffer[outputCount] = touchGetLevel(col ,row) || 0x80;
            outputCount++;
          }
        }
        outputBuffer[outputCount] = (byte)255;
        outputCount++;
        Serial.write(outputBuffer, outputCount);
        LEDstate = !LEDstate;
        digitalWrite(LED, LEDstate);
      }

    } else {
      inputBuffer[inputCount] = c;
      inputCount++;
    }
  }
  
  secondsSinceConnection = (millis() - millisAtLastSerial) / 1000;
}
