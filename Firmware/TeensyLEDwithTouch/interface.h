//serial notes for teensy  http://www.pjrc.com/teensy/td_serial.html
#define maxRow 15
#define maxCol 15

#define bufferLength 10
#define bufferLengthOut 230 

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
    if ((c == 255) && (inputCount>=5)) {
      //EOM
      byte xCoord = inputBuffer[0]; //row
      byte yCoord = inputBuffer[1]; //col
      byte redValue = inputBuffer[2];
      byte greenValue = inputBuffer[3];
      byte blueValue = inputBuffer[4];
      displaySetPixel(xCoord, yCoord, redValue, greenValue, blueValue);
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

      //as a response, send the touch data back for this pixel
//      Serial.write(xCoord);
//      Serial.write(yCoord);
//      Serial.write(touchGetBit(xCoord,yCoord));
//      Serial.write(120);
    } else {
      inputBuffer[inputCount] = c;
      inputCount++;
    }
  }
  
  
}
