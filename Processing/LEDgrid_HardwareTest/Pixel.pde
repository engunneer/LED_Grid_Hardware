//define Pixel class
class Pixel{
  //declare variables to store desired object properties
  color col;
  int xPos;
  int yPos;
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
    xPos = x;
    yPos = y;
    col = c;
    touch = t;
    touchLevel = l;
    //println(xPos);
  }

} 