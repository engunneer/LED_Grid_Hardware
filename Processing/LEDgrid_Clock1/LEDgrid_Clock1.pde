
//size must be called from settings()
void settings() {
  size((15*PIXEL_SIZE)+1,(15*PIXEL_SIZE)+1);
}

//code runs once, on startup
void setup() {
  hardware = new Hardware(15,15);  // how many columns and rows there actually are.
  int numports = hardware.printPorts(); //comment this line once you know which port you need
  if (numports>0) {
    hardware.init(this, 0); //which index to use from the printed port list.
    hardware.setBrightness(0.25);
  } else {
    hardware.simulate();
  }
  //initialize the global pixel array
  for (int j = 0; j<allThePixels.length;j++){
    for (int i=0; i<allThePixels.length;i++){
      //allThePixels[0]=pixelStorage;
      allThePixels[i][j]= new Pixel(i,j,color(0,10,0),false,0);
    }
  }
  frameRate(10);
}


//DataType [] ArrayName = new DataType[length];
//make a global array of pixels
Pixel [][] allThePixels = new Pixel[15][15];

//code runs each time the screen is refreshed
void draw() {
  //all black
  for (int j = 0; j<allThePixels.length;j++){
    for (int i = 0; i<allThePixels.length;i++){
      allThePixels[i][j].col = color(0,0,0);
    }
  }
  
  float second = second();
  float minute = minute() + (second/60.0);
  float hour = hour() + (minute/60.0);

  int center=7;
  float  step = 0.2;
  //hour hand
  for(float radius=0; radius <6; radius += step){
  float hangle = radians(((hour%12)*30.0)-90);
  int hx = (int)(radius*cos(hangle))+center;
  int hy = (int)(radius*sin(hangle))+center;
  hx=constrain(hx,0,14);
  hy=constrain(hy,0,14);
  allThePixels[hx][hy].col = color(255*(8-radius)/8,0,0);
  }
  //minute hand
  for(float radius=0; radius <8; radius += step){
  float mangle = radians((minute*6)-90);
  int mx = (int)(radius*cos(mangle))+center;
  int my = (int)(radius*sin(mangle))+center;
  mx=constrain(mx,0,14);
  my=constrain(my,0,14);
  allThePixels[mx][my].col = color(red(allThePixels[mx][my].col),255*(9-radius)/9,0);
  }
  //second hand
  for(float radius=0; radius <8; radius += step){
  float sangle = radians((second*6)-90);
  int sx = (int)(radius*cos(sangle))+center;
  int sy = (int)(radius*sin(sangle))+center;
  sx=constrain(sx,0,14);
  sy=constrain(sy,0,14);
  allThePixels[sx][sy].col = color(red(allThePixels[sx][sy].col),green(allThePixels[sx][sy].col),255*(9-radius)/9);
  }


  displayPixels(allThePixels);
  //send the status of the allThePixels array to the LED hardware, if present
  //also save the resulting array back which contains updated touch information
  hardware.update(allThePixels); 
  //println(allThePixels[4][2].touch);  //example to print the state of a particular pixel's touch
}