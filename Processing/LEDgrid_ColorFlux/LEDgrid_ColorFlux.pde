final int PANEL_WIDTH = 15;
final int PANEL_HEIGHT = 15;

//size must be called from settings()
void settings() {
  size((PANEL_WIDTH*PIXEL_SIZE)+1,(PANEL_HEIGHT*PIXEL_SIZE)+1);
}

//code runs once, on startup
void setup() {
  boolean dosimulation = true;
  println(System.getProperty("os.name"));
  if (System.getProperty("os.name").equals("Linux")) dosimulation = false;
  
  hardware = new Hardware(PANEL_WIDTH,PANEL_HEIGHT);  // how many columns and rows there actually are.
  if (!dosimulation) {
    hardware.printPorts(); //comment this line once you know which port you need
    hardware.init(this, 0); //which index to use from the printed port list.
    hardware.setBrightness(0.25);
  } else {
    hardware.simulate();
  }
  //initialize the global pixel array
  for (int j = 0; j<PANEL_HEIGHT;j++){
    for (int i=0; i<PANEL_WIDTH;i++){
      //allThePixels[0]=pixelStorage;
      allThePixels[i][j]= new Pixel(i,j,color(0,0,0),false,0);
    }
  }
  frameRate(15);
  colorMode(HSB);
}


//DataType [] ArrayName = new DataType[length];
//make a global array of pixels
Pixel [][] allThePixels = new Pixel[PANEL_WIDTH][PANEL_HEIGHT];

//code runs each time the screen is refreshed
void draw() {
  
  int hue,sat,bright;
  
  float num1 = sin((millis()/30207.0));
  float num2 = cos((millis()/101197.0));
  float num3 = sin(millis()/67012.0);
  float num4 = sin(millis()/140012.0);
  float num5 = sin(millis()/279582.0);
  
  for (int j = 0; j<PANEL_HEIGHT;j++){
    for (int i = 0; i<PANEL_WIDTH;i++){
      //allThePixels[0]=pixelStorage;
      hue = (int)((j * 10 * num3) + (i * (num5 * 5) * 255.0 / PANEL_WIDTH) + (num1 * 255) + 256) % 255;
      sat = (int)(num4 * 128) + 192;
      bright = (int)(num2 * 128) + 192;
      allThePixels[i][j].col = color(hue, sat, bright);
    }
  }

  displayPixels(allThePixels);
  //send the status of the allThePixels array to the LED hardware, if present
  //also save the resulting array back which contains updated touch information
  hardware.update(allThePixels); 
  //println(allThePixels[4][2].touch);  //example to print the state of a particular pixel's touch
}