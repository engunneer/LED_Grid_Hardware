#define bufferLength 10

byte inputBuffer[bufferLength];

void interfaceSetup(){  // initialize serial:
  Serial.begin(230400);
  Serial.setTimeout(1); 
  }
  
void interfaceCyclic()
{
  while (Serial.available()) {
    // get the new bytes
    int bytesRead = Serial.readBytesUntil((char)255, inputBuffer, bufferLength);

    if (bytesRead >= 5){
      byte xCoord = inputBuffer[0]; //col
      byte yCoord = inputBuffer[1]; //row
      byte redValue = inputBuffer[2];
      byte greenValue = inputBuffer[3];
      byte blueValue = inputBuffer[4];

      int pixelNum = (yCoord * 5) + xCoord; //only valid for single board
      setPixel(pixelNum, redValue, greenValue, blueValue);

      long boardBits = touchGetBoardBits(0);//only valid for single board
      Serial.write(xCoord);
      Serial.write(yCoord);
      Serial.write((boardBits>>pixelNum)&0x0001);
      Serial.write(255);
    }
  }
}
