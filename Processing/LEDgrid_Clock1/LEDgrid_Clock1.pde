
//size must be called from settings()
void settings() {
  size((15*PIXEL_SIZE)+1,(15*PIXEL_SIZE)+1);
}

//code runs once, on startup
void setup() {
  boolean dosimulation = true;
  println(System.getProperty("os.name"));
  if (System.getProperty("os.name").equals("Linux")) dosimulation = false;
  
  hardware = new Hardware(15,15);  // how many columns and rows there actually are.
  if (!dosimulation) {
    hardware.printPorts(); //comment this line once you know which port you need
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
  frameRate(15);
}


//DataType [] ArrayName = new DataType[length];
//make a global array of pixels
Pixel [][] allThePixels = new Pixel[15][15];
long millisAtLastSecond;
int lastSecond;

//code runs each time the screen is refreshed
void draw() {
  
  
  
  if (second() != lastSecond)
    millisAtLastSecond = millis();
  lastSecond = second();
  
  long milliseconds = millis() -  millisAtLastSecond;
  
  float second = second() + (milliseconds/1000.0);
  float minute = minute() + (second/60.0);
  float hour = hour() + (minute/60.0);

  //background Color
  for (int j = 0; j<allThePixels.length;j++){
    for (int i = 0; i<allThePixels.length;i++){
      allThePixels[i][j].col = color(0,0,0);
    }
  }


  int center=7;
  float  step = 0.2;
  //hour hand
  for(float radius=0; radius <6; radius += step){
  float hangle = radians(((hour%12)*30.0)-90);
  int hx = (int)(radius*cos(hangle))+center;
  int hy = (int)(radius*sin(hangle))+center;
  hx=constrain(hx,0,14);
  hy=constrain(hy,0,14);
  allThePixels[hx][hy].col = color(255*(8-radius)/8,green(allThePixels[hx][hy].col),blue(allThePixels[hx][hy].col));
  }
  //minute hand
  for(float radius=0; radius <8; radius += step){
  float mangle = radians((minute*6)-90);
  int mx = (int)(radius*cos(mangle))+center;
  int my = (int)(radius*sin(mangle))+center;
  mx=constrain(mx,0,14);
  my=constrain(my,0,14);
  allThePixels[mx][my].col = color(red(allThePixels[mx][my].col),255*(9-radius)/9,blue(allThePixels[mx][my].col));
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


  if (hour<=4.5)     hardware.setBrightness(0.01);
  else if (hour<=5)     hardware.setBrightness(0.10);
  else if (hour<=7)     hardware.setBrightness(0.15);
  else if (hour>=23)     hardware.setBrightness(0.01);
  else if (hour>=22)     hardware.setBrightness(0.05);
  else if (hour>=20)     hardware.setBrightness(0.15);
  else hardware.setBrightness(0.25);

  displayPixels(allThePixels);
  //send the status of the allThePixels array to the LED hardware, if present
  //also save the resulting array back which contains updated touch information
  hardware.update(allThePixels); 
  //println(allThePixels[4][2].touch);  //example to print the state of a particular pixel's touch
}