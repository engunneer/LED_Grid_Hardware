
//code runs once, on startup
void setup() {
  hardware = new Hardware(15,15);  // how many columns and rows there actually are.
  hardware.printPorts(); //comment this line once you know which port you need
  hardware.init(this, 1); //which index to use from the printed port list.
  hardware.setBrightness(0.5);
  
  //initialize the global pixel array
  for (int j = 0; j<allThePixels.length;j++){
    for (int i=0; i<allThePixels.length;i++){
      //allThePixels[0]=pixelStorage;
      allThePixels[i][j]= new Pixel(50*i,50*j,color(0,10,0),false,0);
    }
  }
  size(751,751);
  frameRate(30);
}

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

//DataType [] ArrayName = new DataType[length];
//make a global array of pixels
Pixel [][] allThePixels = new Pixel[15][15];

//code runs each time the screen is refreshed
void draw() {
    
  /*
  //fill each pixel with a random color
  for (int j = 0; j<allThePixels.length;j++){
    for (int i=0; i<allThePixels.length;i++){
      allThePixels[i][j].col= color(random(255),random(255),random(255));
    }
  }
  */
  
  /*
  //fill pixels with a slowly-shifting red gradient (linear, direction depends on i/j combination: 
  //i alone==> gradient along x; j alone==> along y; i+j==>diagonal;i*j hyperbolic fade from x and y axes
  //i^2+j^2, i^2*j^2 also give interesting results.
  //All patterns centered at the origin
  for (int j = 0; j<allThePixels.length;j++){
    for (int i=0; i<allThePixels.length;i++){
      allThePixels[i][j].col= color(50+20*(i+j),0,0);
    }
  }
  */

  
  /*
  //color only the center 4 pixels in the array (note:will still light up 4 pixels in an odd array, but they'll be off-center)
  //allThePixels = new Pixel[10][10];
  for (int j = 0; j<allThePixels.length;j++){
    for (int i=0; i<allThePixels.length;i++){
      if ((i == allThePixels.length/2 || i == allThePixels.length/2-1) && (j == allThePixels.length/2 || j == allThePixels.length/2-1)){
        allThePixels[i][j].col= color(125+20*(i),0,0);
      }
      
      else {
        allThePixels[i][j].col= color(0,0,0);
      }
    }
  }
  */
  
  /*
   //color only the center 4 pixels in the array (note:will still light up 4 pixels in an odd array, but they'll be off-center)
  for (int j = 0; j<allThePixels.length;j++){
    for (int i=0; i<allThePixels.length;i++){
      if ((i == allThePixels.length/2 || i == allThePixels.length/2-1) && (j == allThePixels.length/2 || j == allThePixels.length/2-1)){
        allThePixels[i][j].col= color(125+20*(i),0,0);
      }
      if ((i <= allThePixels.length/2+1 && i >= allThePixels.length/2-2) && (j <= allThePixels.length/2+1 && j >= allThePixels.length/2-2)){ //&! (i == allThePixels.length/2 || i == allThePixels.length/2-1) && (j == allThePixels.length/2 || j == allThePixels.length/2-1)){
        allThePixels[i][j].col= color(0,125+20*(i),0);
      }
      else {
        allThePixels[i][j].col= color(0,0,0);
      }
    }
  }
  */
  
  
  //turn on any pixel that is touched with a random color (requires hardware)
  for (int j = 0; j<allThePixels.length;j++){
    for (int i = 0; i<allThePixels.length;i++){
      if (allThePixels[i][j].touch)
        allThePixels[i][j].col = color(random(MAX_TOUCH - allThePixels[i][j].touchLevel)*15,random(MAX_TOUCH - allThePixels[i][j].touchLevel)*15,random(MAX_TOUCH - allThePixels[i][j].touchLevel)*15);
      else
        allThePixels[i][j].col = color(0,0,0);
    }
  }
  
  
  /*
  //Max white
  for (int j = 0; j<allThePixels.length;j++){
    for (int i = 0; i<allThePixels.length;i++){
      allThePixels[i][j].col = color(254,254,254);
    }
  }
  */
  
  //println(allThePixels[9][9].xPos);
  //println(allThePixels.length);
   
  //print the contents of the allThePixels array to the screen
  for (int k=0; k<allThePixels.length;k++){
    for (int l=0; l<allThePixels.length;l++){
      fill(allThePixels[k][l].col);
      rect(allThePixels[k][l].xPos,allThePixels[k][l].yPos, 50,50);
    }
  }
  
  //send the status of the allThePixels array to the LED hardware, if present
  //also save the resulting array back which contains updated touch information
  hardware.update(allThePixels); 
  //println(allThePixels[4][2].touch);  //example to print the state of a particular pixel's touch
}