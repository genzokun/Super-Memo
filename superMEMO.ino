#include <SNESpad.h>

// Pin Numbers of SNES PAD strobe/clock/data
SNESpad nintendo = SNESpad(2,3,4);

int state = 0;
int snesButtons[] = {1, 2, 256, 512}; // Colored Buttons

int red = 11; // RGB LED red channel
int green = 10; // RGB LED green channel
int blue = 9; // RGB LED blue channel

int lifes = 3; // Number of lifes (chances) to pass the game

// Diferent combinations (Stage #)
int coloredButtons[4] = {1,2,512, 256};

void setup() {
  Serial.begin(9600); // Serial port to listen
}

void loop() {
  state = nintendo.buttons(); // int value when a button is pressed

  // If a button is pressed, show what button it was
  if(state != 0){
    showButton(state);
  }
}

// Turning ON Yellow Button (B)
void ledB(){
  analogWrite(green, 5);
  analogWrite(red, 50);
}

// Turning ON Green Button (Y)
void ledY(){
  analogWrite(green, 5);
}

// Turning ON Blue Button (X)
void ledX(){
  analogWrite(blue, 20);
}

// Turning ON Red Button (A)
void ledA(){
  analogWrite(red, 20);
}

// To clear LED lights
void resetRGB(){
  analogWrite(red, 0);
  analogWrite(green, 0);
  analogWrite(blue, 0);
  delay(100);
}

// STAGE #1
void stageOne(){
  int shots = 4; // Number of buttons in a combination
  int i;
  int numbers1[4]; // Chain of buttons for this stage
  int combination[4]; // Chain of user's pressed buttons

  sendLifes(); // Checking lifes
  delayScreen(); // A delay Screen showing info about game state
  
  // Creating a combination
  for(i = 0 ; i < 4 ; i++){
    numbers1[i] = (random(0,4)); // Randomizing values to have different combinations at a time
    showButton(snesButtons[numbers1[i]]); // Switching ON a generated button
    combination[i] = snesButtons[numbers1[i]]; // New combination saved here
    delay(700); // Delay between each button
  }

  resetRGB(); // Reset LED
  int userCombination = 0; // Preparing for user's combination

  // Catching pressed buttons by user
  while(userCombination < 4){ // This number depends on wich stage the user is
      if(nintendo.buttons() != 0){ // If there is a button pressed
        combination[userCombination] = nintendo.buttons(); // Catch the button pressed
        showButton(nintendo.buttons()); // Showing the button pressed by user
        userCombination++;
        delay(300);
      }
  }

  /* Checking the CPU combination with USER combination
     If the combinations are equals... go to next stage */
  if(compareButtons(numbers1, combination, shots)){
    delay(3000);
    stageTwo();
  }
  /* If not, One life less for the user and go again to the same stage
     but with a different combination */
  else{
    lifes--;
    delay(300);
    if(lifes > 0){
      stageOne();
    }
  }
}

/*
    Same comments are valid for each stage
*/
// STAGE #2
void stageTwo(){
  int shots = 6;
  int i;
  int numbers1[6];
  int combination[6];

  sendLifes();
  delayScreen();
  
  // Creating 1st combination
  for(i = 0 ; i < 6 ; i++){
    numbers1[i] = (random(0,4));
    showButton(snesButtons[numbers1[i]]);
    combination[i] = snesButtons[numbers1[i]]; // New combination saved here
    delay(700);
  }

  resetRGB();
  int userCombination = 0;

  // Catching pressed buttons by user
  while(userCombination < 6){
      if(nintendo.buttons() != 0){
        combination[userCombination] = nintendo.buttons();
        showButton(nintendo.buttons());
        userCombination++;
        delay(300);
      }
  }
  
  if(compareButtons(numbers1, combination, shots)){
    delay(1000);
    stageThree();
  }
  else{
    lifes--;
    delay(300);
    Serial.print("Lifes: ");
    Serial.println(lifes);
    if(lifes > 0){
      stageTwo();
    }
  }
}

// STAGE #3
void stageThree(){
  int shots = 7;
  int i;
  int numbers1[7];
  int combination[7];

  sendLifes();
  delayScreen();
  
  // Creating 1st combination
  for(i = 0 ; i < 7 ; i++){
    numbers1[i] = (random(0,4));
    showButton(snesButtons[numbers1[i]]);
    combination[i] = snesButtons[numbers1[i]]; // New combination saved here
    delay(700);
  }

  resetRGB();
  int userCombination = 0;

  // Catching pressed buttons by user
  while(userCombination < 7){
      if(nintendo.buttons() != 0){
        combination[userCombination] = nintendo.buttons();
        showButton(nintendo.buttons());
        userCombination++;
        delay(300);
      }
  }
  
  if(compareButtons(numbers1, combination, shots)){
    delay(1000);
    stageFour();
  }
  else{
    lifes--;
    delay(300);
    Serial.print("Lifes: ");
    Serial.println(lifes);
    if(lifes > 0){
      stageThree();
    }
  }
}

// STAGE #4
void stageFour(){
  int shots = 8;
  int i;
  int numbers1[8];
  int combination[8];

  sendLifes();
  delayScreen();
  
  // Creating 1st combination
  for(i = 0 ; i < 8 ; i++){
    numbers1[i] = (random(0,4));
    showButton(snesButtons[numbers1[i]]);
    combination[i] = snesButtons[numbers1[i]]; // New combination saved here
    delay(700);
  }

  resetRGB();
  int userCombination = 0;

  // Catching pressed buttons by user
  while(userCombination < 8){
      if(nintendo.buttons() != 0){
        combination[userCombination] = nintendo.buttons();
        showButton(nintendo.buttons());
        userCombination++;
        delay(300);
      }
  }
  
  if(compareButtons(numbers1, combination, shots)){
    delay(1000);
    stageFive();
  }
  else{
    lifes--;
    delay(300);
    Serial.print("Lifes: ");
    Serial.println(lifes);
    if(lifes > 0){
      stageFour();
    }
  }
}

// STAGE #5 -- FINAL STAGE
void stageFive(){
  int shots = 10;
  int i;
  int numbers1[10];
  int combination[10];

  sendLifes();
  delayScreen();
  
  // Creating 1st combination
  for(i = 0 ; i < 10 ; i++){
    numbers1[i] = (random(0,4));
    showButton(snesButtons[numbers1[i]]);
    combination[i] = snesButtons[numbers1[i]]; // New combination saved here
    delay(400);
  }

  resetRGB();
  int userCombination = 0;

  // Catching pressed buttons by user
  while(userCombination < 10){
      if(nintendo.buttons() != 0){
        combination[userCombination] = nintendo.buttons();
        showButton(nintendo.buttons());
        userCombination++;
        delay(300);
      }
  }
  
  if(compareButtons(numbers1, combination, shots)){
    Serial.println("CONGRATULATIONS !!!!!!");
  }
  else{
    lifes--;
    delay(300);
    Serial.print("Lifes: ");
    Serial.println(lifes);
    if(lifes > 0){
      stageFive();
    }
  }
}

/////////////// END OF STAGES 


// Function to compare both combinations
bool compareButtons(int cpu[], int user[], int shots){
  bool next = false; // This controls if user passed the stage
  int equals = 0;
  int i = 0;

  // Checking if combinations are the same
  for(i = 0 ; i < shots ; i++){
    if(snesButtons[cpu[i]] == user[i]){
      equals++;
    }
  }

  // Showing LEDS depending on YES ot NOT PASSED
  if(equals == shots){
    for(i = 0 ; i < 3 ; i ++){
      resetRGB();
      showButton(2);
    }
    next = true; // Go to the next stage
    Serial.println("g"); // ASCII = 103

  }else{
    /* ERROR! combination are not the same
       So, let the LED blink in red color 3 times */
    for(i = 0 ; i < 3 ; i ++){
      resetRGB();
      showButton(256);
    }
    next = false;
    Serial.println("n"); // ASCII = 110
  }
  
  resetRGB();
  return next;
}

/* This function send to Processing a signal by serial port
   to say that Processing has to show a loading screen */
void delayScreen(){
    delay(4000);
    Serial.println("O"); // ASCII 79
    delay(1500);
}

// Another signal by serial to Processing to check user's lifes
void sendLifes(){
  Serial.println("F"); // ASCII 70
}

// Showing buttons in LED mode using RGB
void showButton(int button){
  switch(button){
    // COLORED BUTTONS
    case 1:
      Serial.println("B");
      resetRGB();
      ledB();
      Serial.println("x"); // ASCII = 120
      break;
    case 2:
      Serial.println("Y");
      resetRGB();
      ledY();
      Serial.println("x"); // ASCII = 120
      break;
    case 256:
      Serial.println("A");
      resetRGB();
      ledA();
      Serial.println("x"); // ASCII = 120
      break;
    case 512:
      Serial.println("X");
      resetRGB();
      ledX();
      Serial.println("x"); // ASCII = 120
      break;

    // DIRECTIONAL BUTTONS
    case 16:
      Serial.println("^");
      break;
    case 32:
      Serial.println("v");
      break;
    case 64:
      Serial.println("<");
      break;
    case 128:
      Serial.println(">");
      break;

    // TRIGGER BUTTONS
    case 1024:
      Serial.println("L");
      break;
    case 2048:
      Serial.println("R");
      break;

    // SELECT & START BUTTONS
    case 4:
      Serial.println("Q");
      resetRGB();
      break;
    case 8:
      Serial.println("K");
      stageOne();
      break;
  }
  delay(150);
}

