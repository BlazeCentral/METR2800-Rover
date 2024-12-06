#include <SoftwareSerial.h>
#include <Servo.h>
/////////////////////////
/////////MOTORS//////////
/////////////////////////
// Motor A Front Left
const int SPEED_CONTROL_A = 11;
const int IN_A = 22;
const int OUT_A = 23;

// Motor B Back Left
const int SPEED_CONTROL_B = 2;
const int IN_B = 24;
const int OUT_B = 25;

// Motor C Back Right
const int SPEED_CONTROL_C = 12;
const int IN_C = 26;
const int OUT_C = 27;

// Motor D Front Right
const int SPEED_CONTROL_D = 8;
const int IN_D = 28;
const int OUT_D = 29;

// Different Speeds
const int SLOW = 100;
const int MEDIUM = 150;
const int FAST = 200;

const int RECORRECT = 70;

/////////////////////////
/////////SERVOS//////////
/////////////////////////
Servo claw, yellow, purple, base;

//////////////////////////
/////////SENSORS//////////
//////////////////////////
const int LIMIT_SWITCH = 51;
const int FRONT_IR = 36;
const int BACK_IR = 35;
const int HOLE_IR = 34;
const int CLAW_IR = 37;

void setup() {
  set_pin_modes();
  Serial.begin(9600);

  base.writeMicroseconds(800); // Centre arm 

  // // Top left ball
  grab_ball_1(); // Grab the first ball
  //delay(200);

  // // Middle left ball (tallest)
  move_to_ball_2(); // Move forward until beside second ball
  grab_ball_2(); // Grab the second ball

  // // Bottom left ball
  move_to_ball_3(); // Move forward until at the edge of the rig
  grab_ball_3(); // Grab the third ball

  // // Deposit the first three balls
  //deposit_1(); // Move to drop the balls and then forward a little bit
  //rotate(); // Rotate 180 degrees

  // // Top right ball
  //move_to_ball_4(); // Strafe to the side, and the move forward until at the edge of the rig 
  //grab_ball_4(); // Grab the fourth ball

  // // Middle right ball
  //move_to_ball_5(); // Move backward until beside fifth ball
  //grab_ball_5(); // Grab the fifth ball

  // // Bottom Right Ball
  //move_to_ball_6(); // Move backward until at the edge of the rig
  //grab_ball_6(); // Grab the sixth ball

  // // Deposit the last six balls
  //deposit_2(); // Deposits the final ball

  // The program will now enter the loop function, which is empty
}

/////////////////////////////////////////////////////////////
///////////////////// CONTROL FUNCTIONS /////////////////////
/////////////////////////////////////////////////////////////

// BALL 1 TOP LEFT
void grab_ball_1() { // Top Left
  base.writeMicroseconds(800);
  delay(1000);
  claw.write(40);
  delay(100);
  base.writeMicroseconds(2600);
  delay(1000);
  yellow.write(60);
  delay(200);
  purple.write(180);
  delay(500);
  claw.write(120);
  delay(300);
  purple.write(145);
  delay(200);
  yellow.write(35);
  delay(200);
  purple.write(75);
  delay(200);
  base.writeMicroseconds(800);
  delay(1000);
  claw.write(40);
  delay(200);
}

void move_to_ball_2() { // Middle Left
  // Set up to go forward
  forward_setup();
  // Move at a medium speed
  go(MEDIUM);
  // Continue moving until the claw sensor reads low (senses the pole)
  while (!read_claw_IR()) {
    //Move
  }
  stop();
  delay(200);
  // When claw IR detects the pole, stop
  strafe_right_setup();
  go_sideways(SLOW);
  while (!read_limit_switch()) {
    // Move
  }
  stop();
}

void grab_ball_2() { // Middle Left
  claw.write(40);
  purple.write(90);
  base.writeMicroseconds(2600);
  delay(500);
  purple.write(90);
  delay(300);
  yellow.write(60);
  delay(300);
  purple.write(20);
  delay(500);
  yellow.write(120);
  delay(600);
  purple.write(90);
  delay(1200);
  yellow.write(120);
  delay(200);
  //Grab the ball
  claw.write(130);
  delay(300);
  for (int i = 93; i > 60; i--) {
    purple.write(i);
    delay(20);
  }
  // purple.write(60);
  delay(100);
  yellow.write(90);
  delay(300);
  base.writeMicroseconds(1200);
  delay(500);
  purple.write(90);
  delay(300);
  yellow.write(20);
  delay(300);
  base.writeMicroseconds(800);
  delay(300);
  purple.write(80);
  delay(300);
  claw.write(40);
}

void move_to_ball_3() { // Bottom Left
  // Set up to go forward
  forward_setup();
  // Move at a medium speed
  go(MEDIUM);
  // Continue moving until the front sensor reads low (senses the edge of the rig)
  while (read_front_IR()) {
    //Move
  }
  stop();
  delay(200);
  // When claw IR detects the pole, stop
  strafe_right_setup();
  go_sideways(SLOW);
  while (!read_limit_switch()) {
    // Move
  }
  stop();
}

void grab_ball_3() { // Bottom Left
  claw.write(40);
  base.writeMicroseconds(2200);
  delay(500);
  yellow.write(13);
  delay(400);
  purple.write(145);
  delay(400);
  claw.write(120);
  delay(300);
  purple.write(85);
  delay(300);
  base.writeMicroseconds(800);
  delay(1000);
  claw.write(40);
  delay(100);
}

void deposit_1() {
  // Delay variables
  int alignWithHoleDelay = 1000; // NEED TO WORK OUT THE CORRECT DELAY TIME TO LINE UP WITH THE HOLE
  int dropTime = 1000; //NEED TO WORK OUT TIME TO DROP ALL BALLS
  int moveTime = 1000; // NEED TO WORK OUT DELAY TIME TO MOVE A BIT FORWARD OFF THE HOLE BEFORE ROTATING
  // Move backwards to align with the hole
  back_setup();
  go(SLOW);
  delay(alignWithHoleDelay); 
  stop();
  // Strafe left until over hole
  strafe_left_setup();
  go(MEDIUM);
  while (read_hole_IR()) {
    // Keep moving until it goes over the hole
  }
  // Wait to drop all balls
  stop();
  delay(dropTime);

  // Move forward a bit
  forward_setup();
  go(MEDIUM);
  delay(moveTime);
  stop();
}

void rotate() {
  // Delay time, how long it takes to rotate
  int rotatetime = 1000; //NEED TO WORK OUT HOW LONG IT TAKES TO ROTATE
  // Rotate 180 degrees
  rotate_clockwise_setup();
  go(MEDIUM);
  delay(rotatetime);
  stop();
}

void move_to_ball_4() { // Top Right
  // Move to the other side of the rig
  strafe_right_setup();
  go(MEDIUM);
  while (!read_limit_switch) {
    // Keep going
  }

  // Move forward until at edge of rig
  // Set up to go forward
  forward_setup();
  // Move at a medium speed
  go(MEDIUM);
  // Continue moving until the front sensor reads low (senses the edge of the rig)
  while (read_front_IR()) {
    // Check the limit switch
    if (!read_limit_switch()) {
      stop();
      strafe_right_setup();
      go(SLOW);
      while (!read_limit_switch()) {
        //Keep going until limit switch on
      }
      forward_setup();
      go(MEDIUM);
    }
  }

  // stop
  stop();
}

void grab_ball_4() { // Top Right
  base.writeMicroseconds(800);
  delay(1000);
  claw.write(40);
  delay(100);
  yellow.write(10);
  delay(200);
  purple.write(90);
  delay(200);
  base.writeMicroseconds(2350);
  delay(1000);
  purple.write(140);
  delay(500);
  claw.write(110);
  delay(500);
  purple.write(90);
  delay(200);
  yellow.write(20);
  delay(200);
  base.writeMicroseconds(800);
  delay(1000);
  claw.write(40);
  delay(100);
}

void move_to_ball_5() { // Middle Right
  // Set up to go backward
  back_setup();
  // Move at a medium speed
  go(MEDIUM);
  // Continue moving until the claw sensor reads low (senses the pole)se;
  while (!read_claw_IR()) {
    // Check the limit switch
    if (!read_limit_switch()) {
      stop();
      strafe_right_setup();
      go(SLOW);
      while (!read_limit_switch()) {
        //Keep going until limit switch on
      }
      forward_setup();
      go(MEDIUM);
    }
  }

  // Stop
  stop();
}

void grab_ball_5() { // Middle Right
  yellow.write(20);
  purple.write(70);
  claw.write(40);
  base.writeMicroseconds(2600);
  delay(1000);
  yellow.write(45);
  purple.write(82);
  delay(300);
  claw.write(110);
  delay(400);
  purple.write(60);
  delay(200);
  base.writeMicroseconds(800);
  delay(500);
  purple.write(80);
  yellow.write(20);
  delay(500);
  claw.write(40);
}

void move_to_ball_6() { // Bottom Right
  // Set up to go backward
  back_setup();
  // Move at a medium speed
  go(MEDIUM);
  // Continue moving until the back sensor reads low (senses the edge of the rig)
  while (read_back_IR()) {
    // Check the limit switch
    if (!read_limit_switch()) {
      stop();
      strafe_right_setup();
      go(SLOW);
      while (!read_limit_switch()) {
        //Keep going until limit switch on
      }
      forward_setup();
      go(MEDIUM);
    }
  }

  // Stop
  stop();
}

void grab_ball_6() { // Bottom Right
  base.writeMicroseconds(2100);
  delay(500);
  yellow.write(25);
  purple.write(100);
  delay(100);
  yellow.write(0);
  purple.write(140);
  delay(30);
  claw.write(110);
  delay(500);
  purple.write(80);
  yellow.write(20);
  delay(300);
  base.writeMicroseconds(800);
  delay(700);
  claw.write(40);
}

void deposit_2() {
  // Delay variables
  int alignWithHoleDelay = 1000; // NEED TO WORK OUT THE CORRECT DELAY TIME TO LINE UP WITH THE HOLE
  int moveTime = 1000; // NEED TO WORK OUT DELAY TIME TO MOVE A BIT FORWARD OFF THE HOLE BEFORE ROTATING
  // Move backwards to align with the hole
  back_setup();
  go(SLOW);
  delay(alignWithHoleDelay); 
  stop();
  // Strafe left until over hole
  strafe_left_setup();
  go(MEDIUM);
  while (read_hole_IR()) {
      // Keep going until over the hole
  }
  stop();
  // PROGRAM WILL FINISH
}

///////////////////////////////////////////////////////////
///////////////////// SETUP FUNCTIONS /////////////////////
///////////////////////////////////////////////////////////
void set_pin_modes() {
  // Motors
  pinMode(SPEED_CONTROL_A, OUTPUT);
  pinMode(SPEED_CONTROL_B, OUTPUT);
  pinMode(SPEED_CONTROL_C, OUTPUT);
  pinMode(SPEED_CONTROL_D, OUTPUT);
  pinMode(IN_A, OUTPUT);
  pinMode(OUT_A, OUTPUT);
  pinMode(IN_B, OUTPUT);
  pinMode(OUT_B, OUTPUT);
  pinMode(IN_C, OUTPUT);
  pinMode(OUT_C, OUTPUT);
  pinMode(IN_D, OUTPUT);
  pinMode(OUT_D, OUTPUT);

  // Servos
  claw.attach(3);
  yellow.attach(6);
  purple.attach(5);
  base.attach(4, 800, 2600);

  // Sensors
  pinMode(LIMIT_SWITCH, INPUT_PULLUP);
  pinMode(FRONT_IR, INPUT);
  pinMode(BACK_IR, INPUT);
  pinMode(HOLE_IR, INPUT);
  pinMode(CLAW_IR, INPUT);
}

////////////////////////////////////////////////////////////
//////////////////// MOVEMENT FUNCTIONS ////////////////////
////////////////////////////////////////////////////////////

// Will make the robot move forward
// Call the speed you want
void go(int speed) {
  analogWrite(SPEED_CONTROL_A, speed); // Motor A speed
  analogWrite(SPEED_CONTROL_B, speed); // Motor B speed
  analogWrite(SPEED_CONTROL_C, speed); // Motor C speed
  analogWrite(SPEED_CONTROL_D, speed); // Motor D speed
}

void go_sideways(int speed) {
  analogWrite(SPEED_CONTROL_A, speed + RECORRECT); // Motor A speed
  analogWrite(SPEED_CONTROL_B, speed); // Motor B speed
  analogWrite(SPEED_CONTROL_C, speed); // Motor C speed
  analogWrite(SPEED_CONTROL_D, speed + RECORRECT); // Motor D speed
}

// Will stop all movement
void stop() {
  analogWrite(SPEED_CONTROL_A, 0); // Motor A speed
  analogWrite(SPEED_CONTROL_B, 0); // Motor B speed
  analogWrite(SPEED_CONTROL_C, 0); // Motor C speed
  analogWrite(SPEED_CONTROL_D, 0); // Motor D speed
}

// Setup to move forward
void forward_setup() {
  // A Forward
  digitalWrite(IN_A, HIGH);
  digitalWrite(OUT_A, LOW);
  // B Forward
  digitalWrite(IN_B, HIGH);
  digitalWrite(OUT_B, LOW);
  // C Forward
  digitalWrite(IN_C, HIGH);
  digitalWrite(OUT_C, LOW);
  // D Forward
  digitalWrite(IN_D, HIGH);
  digitalWrite(OUT_D, LOW);
}

// Setup to move backward
void back_setup() {
  // A Backward
  digitalWrite(IN_A, LOW);
  digitalWrite(OUT_A, HIGH);
  // B Backward
  digitalWrite(IN_B, LOW);
  digitalWrite(OUT_B, HIGH);
  // C Backward
  digitalWrite(IN_C, LOW);
  digitalWrite(OUT_C, HIGH);
  // D Backward
  digitalWrite(IN_D, LOW);
  digitalWrite(OUT_D, HIGH);
}

// Setup to strafe left
void strafe_left_setup() {
  // A Backward
  digitalWrite(IN_A, LOW);
  digitalWrite(OUT_A, HIGH);
  // B Forward
  digitalWrite(IN_B, HIGH);
  digitalWrite(OUT_B, LOW);
  // C Backward
  digitalWrite(IN_C, LOW);
  digitalWrite(OUT_C, HIGH);
  // D Forward
  digitalWrite(IN_D, HIGH);
  digitalWrite(OUT_D, LOW);
}

// Setup to strafe right
void strafe_right_setup() {
  // A Forward
  digitalWrite(IN_A, HIGH);
  digitalWrite(OUT_A, LOW);
  // B Backward
  digitalWrite(IN_B, LOW);
  digitalWrite(OUT_B, HIGH);
  // C Forward
  digitalWrite(IN_C, HIGH);
  digitalWrite(OUT_C, LOW);
  // D Backward
  digitalWrite(IN_D, LOW);
  digitalWrite(OUT_D, HIGH);
}

// Setup to rotate clockwise
void rotate_clockwise_setup() {
  // A Forward
  digitalWrite(IN_A, HIGH);
  digitalWrite(OUT_A, LOW);
  // B Forward
  digitalWrite(IN_B, HIGH);
  digitalWrite(OUT_B, LOW);
  // C Backward
  digitalWrite(IN_C, LOW);
  digitalWrite(OUT_C, HIGH);
  // D Backward
  digitalWrite(IN_D, LOW);
  digitalWrite(OUT_D, HIGH);
}

// Setup to rotate anticlockwise
void rotate_anticlockwise_setup() {
  // A Backward
  digitalWrite(IN_A, LOW);
  digitalWrite(OUT_A, HIGH);
  // B Backward
  digitalWrite(IN_B, LOW);
  digitalWrite(OUT_B, HIGH);
  // C Forward
  digitalWrite(IN_C, HIGH);
  digitalWrite(OUT_C, LOW);
  // D Forward
  digitalWrite(IN_D, HIGH);
  digitalWrite(OUT_D, LOW);
}

//////////////////////////////////////////////////////////
//////////////////// SENSOR FUNCTIONS ////////////////////
//////////////////////////////////////////////////////////
bool read_limit_switch() {
  if (digitalRead(LIMIT_SWITCH) == HIGH) {
    return false;
  }
  return true;
}

bool read_front_IR() {
  if (digitalRead(FRONT_IR) == LOW) {
    return true;
  }
  return false;
}

bool read_back_IR() {
  if (digitalRead(BACK_IR) == LOW) {
    return true;
  }
  return false;
}

bool read_hole_IR() {
  if (digitalRead(HOLE_IR) == LOW) {
    return true;
  }
  return false;
}

bool read_claw_IR() {
  if (digitalRead(CLAW_IR) == LOW) {
    return true;
  }
  return false;
}


void loop() {
  // EMPTY
  // This is where the program will end
}
