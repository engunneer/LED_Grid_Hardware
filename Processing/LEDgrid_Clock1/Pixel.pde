int PIXEL_SIZE = 30;

//define Pixel class
class Pixel{
  //declare variables to store desired object properties
  color col;
  int xPos;
  int yPos;
  int size;
  boolean touch;
  int touchLevel;
  
  //create pixel constructor function to make pixel objects from input data 
  Pixel(){
    xPos = 20;//x;
    yPos = 100;//y;
    col = 50;//c;
    touch = false;//t;
    touchLevel = 0;
    //println(xPos);
  }
    
  //create pixel constructor function to make pixel objects from input data 
  Pixel(int x, int y, color c, boolean t, int l){
    xPos = x*PIXEL_SIZE;
    yPos = y*PIXEL_SIZE;
    col = c;
    touch = t;
    touchLevel = l;
    size=PIXEL_SIZE;
    //println(xPos);
  }

} 

void displayPixels(Pixel[][] pixelData)
{
// Locally display the state of allThePixels
  //print the contents of the allThePixels array to the screen
  for (int k=0; k<pixelData.length;k++){
    for (int l=0; l<pixelData.length;l++){
      fill(pixelData[k][l].col);
      rect(pixelData[k][l].xPos,pixelData[k][l].yPos, pixelData[k][l].size,pixelData[k][l].size);
    }
  }

}