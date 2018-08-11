import processing.serial.*; // Serial port library
Serial port; // Serial port name to use
int currentStage = 0; // Actual stage where the user is
int lifes = 0; // User chances

// BUTTONS SWITCHED OFF
int yOFF[] = {16, 172, 109};
int bOFF[] = {238, 198, 30};
int xOFF[] = {37, 81, 223};
int aOFF[] = {227, 33, 33};

// BUTTONS SWITCHED ON
int yON[] = {23, 236, 150};
int bON[] = {255, 248, 142};
int xON[] = {144, 169, 251};
int aON[] = {250, 140, 140};

void setup()
{
  clear(); // Clearing screen
  port = new Serial(this, Serial.list()[1], 9600); // SNES Pad port (dependeing on each computer)  
  size(500, 650); // Screen size
  
  initScreen(); // Showing splash screen to start the game
}
 
void draw() {
  // While a port is available to use
  while (port.available() > 0) {
    /* Reading buttons through port
     * Letters sending from Arduino are reciving by Processing
     * in ASCII code (integer)
     */
    int button = port.read();
    
    if(button > 64){ // Character A      
      getButtonName(button); // Let's see wich button was pressed
      
      // In case of button would be START, let's play!
      if(button == 79){
        stage();
      }
    }
  }
}

// Depending on wich ASCII code Processing receives...
void getButtonName(int button){
  println(button);

  switch(button){
        case 89:
                println("Y");
                fill(yON[0], yON[1], yON[2]); // Blinking green button
                ellipse(125, 320, 100, 100);
                break;
                
        case 66:
                println("B");
                fill(bON[0], bON[1], bON[2]); // Blinking yellow button
                ellipse(250, 440, 100, 100);
                break;
                
        case 88:
                println("X");
                fill(xON[0], xON[1], xON[2]); // Blinking blue button
                ellipse(250, 200, 100, 100);
                break;
                
        case 65:
                println("A");
                fill(aON[0], aON[1], aON[2]); // Blinking red button
                ellipse(375, 320, 100, 100);
                break;
                
        // START button, let's play!
        case 75:
                if(lifes == 0){
                  lifes = 3;
                  currentStage = 1;
                }
                
                println("START");
                loadingScreen();
                break;
                
        // ASCII code -> x
        // to detect when a button is not pressed after have been pressed
        case 120:
                stage();
                break;
                
        // Next Stage
        case 103:
                currentStage++;
                loadingScreen();
                break;
        
        // Loosing 1 life
        case 110:
                lifes--;
                loadingScreen();
      }
}

// LOADING SCREEN
void loadingScreen(){
  /* Checking if there are lifes available
     If not, go to GAME OVER screen */
  if(lifes > 0){
    if(currentStage <= 5){
      if(currentStage == 0){
        currentStage++;
      }
      
      // Creating screen's elements
      background(55,55,55); // Background color
      fill(244,244,244); // Color for texts
      textSize(30); // Text's size
      
      // Loading a logo image
      PImage logo = loadImage("logo.png");
      image(logo, 100, 50, 300, 137); // Logo's position in the screen
      
      // Loading font type specific
      PFont font2p = loadFont("font2p.vlw");
      textFont(font2p, 22); // Font Family and font size
      textAlign(CENTER); // Centered text
      text("STAGE " + currentStage, 250, 300);
      
      // Loading  heart image into the screen
      PImage heart = loadImage("heart.png");
      image(heart, 187, 320, 32, 28); // Heart image position
      textSize(22);
      textAlign(LEFT);
      text("x " + lifes, 246, 345);
      
      // Loading
      textSize(18);
      textAlign(CENTER);
      text("loading ...", 250, 600);
    }
    // If user ends the game, show a final screen
    else{
      endOfGame();
    }
  }
  // If user lose the game, show the GAME OVER screen
  else{
    gameOver();
  }
}


// LOADING STAGE TEMPLATE
// Declaring and putting all the screen elements into the interface
void stage(){  
  background(243, 243, 243);
  
  fill(44, 44, 44);
  textSize(30);
  textAlign(CENTER);
  text("STAGE " + currentStage, 250, 80);
  
  // GRAY circle
  fill(220,220,220);
  ellipse(250, 325, 400, 400);
  
  // Y BUTTON
  fill(yOFF[0], yOFF[1], yOFF[2]);
  ellipse(125, 320, 100, 100);
  
  // B BUTTON
  fill(bOFF[0], bOFF[1], bOFF[2]);
  ellipse(250, 440, 100, 100);
  
  // X BUTTON
  fill(xOFF[0], xOFF[1], xOFF[2]);
  ellipse(250, 200, 100, 100);
  
  // A BUTTON
  fill(aOFF[0], aOFF[1], aOFF[2]);
  ellipse(375, 320, 100, 100);
  
  // LIFES
  PImage heart = loadImage("heart.png");
  image(heart, 375, 600, 32, 28);
  textSize(22);
  textAlign(LEFT);
  text("x", 420, 625);
  text(lifes, 450, 625);
}

// GAME OVER screen, Oh no! you lose
void gameOver(){
  background(0,0,0);
  
  fill(255, 255, 255);
  textSize(30);
  textAlign(CENTER);
  text("GAME OVER", 250, 325);
}

// CONGRATULATIONS !!! YOU WIN
void endOfGame(){
  background(38,77,71);
  PImage logo = loadImage("logo.png");
  
  image(logo, 100, 50, 300, 137);
  
  textAlign(CENTER);
  textSize(40);
  fill(243, 243, 243);
  text("YOU WIN !", 250, 400);
}

// Showing first screen with logo and 'press start' message 
void initScreen(){
  background(55,55,55);
  fill(244,244,244);
  textSize(30);
  
  PImage logo = loadImage("logo.png");
  image(logo, 100, 50, 300, 137);
  
  PFont font2p = loadFont("font2p.vlw");
  textFont(font2p, 22);
  textAlign(CENTER);
  text("PRESS START", 250, 300);
  
  // Credits
  textSize(12);
  text("made by", 250, 600);
  text("Luis Alemañ", 250, 615);
}
