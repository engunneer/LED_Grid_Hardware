import processing.serial.*;

//gloabl variables
Hardware hardware;
final int MAX_TOUCH  = 16;

class Hardware{

  Serial myPort;
  int delayTime = 1;
  byte [] byteData;
  int HWCols, HWRows, counter;
 
  Hardware(int hwCols,int hwRows){
    HWCols = hwCols;
    HWRows = hwRows;
  }
 
  void printPorts(){
    // List all the available serial ports:
    printArray(Serial.list());
  }
  
  void init(PApplet parent, int portNumber){
  
    // if portNumber is possible
    if (Serial.list().length >= portNumber) {
      // Open the port you are using at the rate you want:
      myPort = new Serial(parent, Serial.list()[portNumber], 230400);
      println("Opened serial port " + Serial.list()[portNumber]);
    }
    else
        println("requested serial port not available. cycle USB plug and restart sketch.");
    
  }
  
  //set scalar value from 0 to 1 to dim overall display
  void setBrightness (float brightness){
    byte brightbyte = (byte)(brightness  * 254);
    byteData = new byte[]{};
        byteData = concat(byteData, new byte[]{(byte)100,(byte)0,(byte)brightbyte,(byte)0,(byte)0,(byte)0,(byte)255});
    //write all the data!
    myPort.write(byteData);
  }
  
  //update the actual hardware, if connected
  void update(Pixel[][] pixelData){
    if (myPort == null){
        return ; //port is not open or created, so skip all this and just return the input.
    }
    //don't update hardware bigger than the actual number of pixels, or bigger than the input data
    int numCols = min(pixelData.length,HWCols);
    int numRows = min(pixelData[0].length,HWRows); //based on https://forum.processing.org/one/topic/getting-lengths-of-multidimensional-arrays.html

    //send out color data
    byteData = new byte[]{};
    for (int j = 0; j<numCols;j++){
      for (int i = 0; i<numRows;i++){
        int r = (pixelData[i][j].col >> 16) & 0xFF;  // Faster way of getting red(pixelData[i][j].col)
        int g = (pixelData[i][j].col >> 8) & 0xFF;   // Faster way of getting green(pixelData[i][j].col)
        int b = (pixelData[i][j].col) & 0xFF;        // Faster way of getting blue(pixelData[i][j].col)
        
        //prevent sending 255 on any color bit - the human eye won't notice.
        //also apply brightness (linearly)
        /*  Brightness now handled in hardware!
        r = (int)(Brightness * min(r,254));
        g = (int)(Brightness * min(g,254));
        b = (int)(Brightness * min(b,254));
        */
        r = (int)(min(r,254));
        g = (int)(min(g,254));
        b = (int)(min(b,254));
        byteData = concat(byteData, new byte[]{(byte)i,(byte)j,(byte)r,(byte)g,(byte)b,(byte)0,(byte)255});
        
      }
    }
    //write all the data!
    myPort.write(byteData);

    //read all the data
    if (myPort.available() > 225) {
      //now get any touch data that has shown up and store it in the pixelData
      byte[] inBuffer = new byte[1000];

      final boolean printStuff = false; //use for debug
      
      int returned = myPort.readBytes(inBuffer);//readBytesUntil(-1,inBuffer) - 1;
      
      if(printStuff) println(returned + " " + counter++);

      if (returned > 0) {
        if(returned > 225) returned = 225;
        ConvertBytes(pixelData, inBuffer, returned);
      }
      else
      {
        println("myPort.readBytesUntil returned " + returned);
      }  
    }

    //return pixelData; //no need to return, as it's passed byref
  }
  
  
  void ConvertBytes(Pixel[][] pixelData, byte[] rawTouchBytes, int buflength){

    for(int i=0;i<buflength;i++){
      //if(printStuff) print(inBuffer[i] + " "); //display raw buffer data
      
      //filter out the 0x80
      rawTouchBytes[i] &= 0x1F;
      
      //calculate the location of this data from i
      int thisDataX = (i%15);
      int thisDataY = i/15;
                
      pixelData[thisDataX][thisDataY].touch = (rawTouchBytes[i])>0;
      pixelData[thisDataX][thisDataY].touchLevel = rawTouchBytes[i];
      //if(printStuff) println("i:" + i + " X:" + (thisDataStartX+touchi) + " Y:" + thisDataStartY + " = " + thisBit);
    }
    //return pixelData; //no need to return, as it's passed byref
  }
  
} //class