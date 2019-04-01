#include <Servo.h>
#include "QSerial.h"
QSerial myIRserial;

int type = 0;//initial position. left-0, middle-1, right-2

int cy = 0;
int cx = 0;
int cd = 0;
int x = 0;
int y = 0;
int d = 0;
int xIn;
int yIn;
int dIn;
int delayTLeft = 700; //500 when half bat 400 when full bat
int delayTRight = 700; //500 when half bat 400 when full bat
int delayBeforeT = 250; // 350 when half 250 when full
int lSP = 170;
int rSP = 180;
int turnMod = 60; // 80 when half 90 when full
int resetTMod = -10; // subtracts from turn speed after drop dice. 10 when full -10 when half;

int leftBumper = 1;
int rightBumper = 1;

int IRpin = A3;

int forceSensor = A4;
int forceReading = 1027;
int gripThresh = 300;
int fIRThresh = 400;


int lIRPin = A0;
int cIRPin = A2;
int rIRPin = A1;

int lVal = 0;
int cVal = 0;
int rVal = 0;

int plVal = 0;
int pcVal = 0;
int prVal = 0;

int leftSpeed = 5;
int leftDirection = 4;
int rightSpeed = 6;
int rightDirection = 7;
int thresh = 930;
unsigned long lastInter = 0;
int IRVal = 0;


//---------------------------------

int arrayLeft[5][3] = {{1, 1, 3},
  {1, 5, 0},
  {5, 5, 1},
  {1, 2, 3},
  {1, 4, 3}
};
int arrayCentre[5][3] = {{1, 3, 3},
  {3, 5, 0},
  {5, 3, 1},
  {2, 5, 0},
  {4, 5, 0}
};
int arrayRight[5][3] = {{1, 5, 3},
  {5, 5, 0},
  {5, 1, 1},
  {5, 2, 1},
  {5, 4, 1}
};

int Destinations[5][3];

int txpin = -1;
int rxpin = 12;

char Start1 = '0';
char Start2 = '1';
char Start3 = '2';

//---------------------------------

int panPIN = 8;
int tiltPIN = 9;
int gripPIN = 10;

Servo pan, tilt, grip;
//--------------------------------
int lBump = 2;
int rBump = 3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pan.attach(panPIN);
  tilt.attach(tiltPIN);
  grip.attach(gripPIN);

  // put your setup code here, to run once:
  pinMode(lIRPin, INPUT);
  pinMode(cIRPin, INPUT);
  pinMode(rIRPin, INPUT);

  pinMode(leftSpeed,  OUTPUT);
  pinMode(leftDirection, OUTPUT);
  pinMode(rightSpeed, OUTPUT);
  pinMode(rightDirection, OUTPUT);

  pinMode(lBump, INPUT);
  pinMode(rBump, INPUT);

  pinMode(IRpin, INPUT);
  pinMode(forceSensor, INPUT);

  //  myIRserial.attach(rxpin, txpin);
  //  GetIR();

  //  pan.write(100);
  tilt.write(190);
  grip.write(0);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("BEGINING LOOP()");
  //  Serial.println(Destinations[0][0]);
  //  Serial.println(Destinations[0][1]);
  //  Serial.println(Destinations[0][2]);
  //  xIn = Destinations[0][0];
  //  yIn = Destinations[0][1];
  //  dIn = Destinations[0][2];
  //  GoToDice(xIn,yIn,dIn);
  //  approachDice();
  //  GoToBin(type);
  //  approachBin();
  //
  //  xIn = Destinations[1][0];
  //  yIn = Destinations[1][1];
  //  dIn = Destinations[1][2];
  //  GoToDice(xIn, yIn, dIn);
  //  approachDice();
  //  GoToBin(type);
  //  approachBin();
  //
  //  xIn = Destinations[2][0];
  //  yIn = Destinations[2][1];
  //  dIn = Destinations[2][2];
  //  GoToDice(xIn, yIn, dIn);
  //  approachDice();
  //  GoToBin(type);
  //  approachBin();
  //
  //  xIn = Destinations[3][0];
  //  yIn = Destinations[3][1];
  //  dIn = Destinations[3][2];
  //  GoToDice(xIn, yIn, dIn);
  //  approachDice();
  //  GoToBin(type);
  //  approachBin();
  //
  //  xIn = Destinations[4][0];
  //  yIn = Destinations[4][1];
  //  dIn = Destinations[4][2];
  //  GoToDice(xIn, yIn, dIn);
  //  approachDice();
  //  GoToBin(type);
  //  approachBin();

  xIn = 2;
  yIn = 5;
  dIn = 0;
  GoToDice(xIn, yIn, dIn);
  approachDice();
  GoToBin(type);
  approachBin();


  xIn = 1;
  yIn = 5;
  dIn = 0;
  GoToDice(xIn, yIn, dIn);
  approachDice();
  GoToBin(type);
  approachBin();
  xIn = 5;
  yIn = 4;
  dIn = 1;
  GoToDice(xIn, yIn, dIn);
  approachDice();
  GoToBin(type);
  approachBin();
  xIn = 1;
  yIn = 2;
  dIn = 3;
  GoToDice(xIn, yIn, dIn);
  approachDice();
  GoToBin(type);
  approachBin();
  xIn = 1;
  yIn = 3;
  dIn = 3;
  GoToDice(xIn, yIn, dIn);
  approachDice();
  GoToBin(type);
  approachBin();
  exit(0);
}

void GetIR() {
  Serial.begin(115200);
  char val = -1;

  while (Destinations[0][0] == 0) {
    val = myIRserial.receive(200);
    Serial.println(val);

    if (val == Start1) {
      Serial.println("Start Location 1");
      for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
          Destinations[i][j] = arrayLeft[i][j];
          Serial.println(Destinations[i][j]);
        }
      }
    }

    else if (val == Start2) {
      Serial.println("Start Location 2");
      for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
          Destinations[i][j] = arrayCentre[i][j];
          Serial.println(Destinations[i][j]);
        }
      }
    }

    else if (val == Start3) {
      Serial.println("Start Location 3");
      for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
          Destinations[i][j] = arrayRight[i][j];
          Serial.println(Destinations[i][j]);
        }
      }
    }

    else {
      Serial.println("Invalid transmitted value.");
    }
  }
}

//Function for robot to move to a specified ball's location
void GoToDice(int xIn1, int yIn1, int dIn1)
{
  x = xIn1;
  y = yIn1;
  d = dIn1;
  cx = type + 2;
  cy = 0;
  if (cy < y) { //if current y coordinate is less than the objective y then move forward until current y is equal to that of the objective
    forward(y - cy);
    cy = y;

  }
  if (cx != x) { //if the objective is not directly infront of the robot then turn in the direction of the ball and go forward until the ball is in front of the robot
    if (cx < x) {
      turn(0);
      forward(x - cx);
      cx = x;
    }
    else if (cx > x) {
      turn(1);
      forward(cx - x);
      cx = x;
    }

  }
  if (cd != d) { //if the robot is not facing the ball, then turn towards the ball
    if (abs(cd - d) == 2) {
      turn(1);
      turn(1);
    }
    else if (cd - d == -3) {
      turn (1);
    }
    else if (cd - d == 3) {
      turn (0);
    }
    else if (cd - d > 0)
    {
      turn(1);
    }
    else if (cd - d < 0)
    {
      turn(0);
    }
  }
  analogWrite(leftSpeed, lSP);
  analogWrite(rightSpeed, rSP);
  Serial.print("cd:" + (String)cd);
  Serial.print("cx:" + (String)cx);
  Serial.print("cy:" + (String)cy);
}

void GoToBin(int typeIn)//left-0, middle-1 or right-2
{
  if ( dIn == 3 ) {
    cx = cx - 1;
  }
  else if ( dIn == 1 ) {
    cx = cx + 1;
  }
  y = 0;
  x = typeIn + 2; //gives location of bin depending on starting position
  Serial.println("Cx:" + (String)cx);
  Serial.println("Cd:" + (String)cd);

  if (cd == 2)
  {
    Serial.println("direction fix");
    if (cx < x) {
      forward(1);
      turn(1);
      Serial.println("Cx:" + (String)cx);
      Serial.println("Cd:" + (String)cd);

      cd = 3;
    }
    else if (cx > x) {

      forward(1);
      turn(0);
      cd = 1;
    }
  }

  if (cx != x) { //if the objective is not directly infront of the robot then turn in the direction of the ball and go forward until the ball is in front of the robot
    if (cx < x) {
      Serial.println("Going forward");
      forward(x - cx);
      cx = x;
      turn(0);//turn right

      Serial.println("turning");

    }
    else if (cx > x) {
      Serial.println("Going forward");

      forward(cx - x);
      cx = x;
      turn(1);//turn left
    }

  }
  if (cy != y) { //if current y coordinate is less than the objective y then move forward until current y is equal to that of the objective
    forward(cy - y - 1);
    cy = y;
  }
  analogWrite(leftSpeed, lSP - 40);
  analogWrite(rightSpeed, rSP - 40);

  //drop into bin function
}

void followLineF(int speedMod)//speedMod adds on to speed;
{
  lVal = analogRead(lIRPin);
  cVal = analogRead(cIRPin);
  rVal = analogRead(rIRPin);
  IRVal = analogRead(IRpin);
  digitalWrite(leftDirection, HIGH); //Set left motor direction to forward
  digitalWrite(rightDirection, HIGH); //Set right motor direction to forward

//    Serial.print(lVal);
//    Serial.print(" || ");
//    Serial.print(cVal);
//    Serial.print(" || ");
//    Serial.println(rVal);
  //  if (IRVal > fIRThresh) {
  //    analogWrite(leftSpeed, 0);
  //    analogWrite(rightSpeed, 0);} else
  if ((lVal < thresh) && (cVal > thresh) && (rVal < thresh)) { //SET MOTORS TO DRIVE FORWARD
    analogWrite(leftSpeed, lSP + speedMod);
    analogWrite(rightSpeed, rSP + speedMod);
  } else if ((lVal > thresh) && (cVal < thresh) && (rVal < thresh)) { //LEANING INTO THE RIGHT...SPEED UP RIGHT MOTOR (CALIBRATE)
    analogWrite(leftSpeed, lSP - 80 + speedMod);
    analogWrite(rightSpeed, rSP + speedMod);
  } else if ((lVal < thresh) && (cVal < thresh) && (rVal > thresh)) { //LEANING INTO THE LEFT...SPEED UP RIGHT MOTOR (CALIBRATE)
    analogWrite(leftSpeed, lSP + speedMod);
    analogWrite(rightSpeed, rSP - 80 + speedMod);
  }
  else {
    analogWrite(leftSpeed, lSP - 30 + speedMod);
    analogWrite(rightSpeed, rSP - 30 + speedMod);
  }
}


//Function to move robot forward a specified number of intersections
void forward(int numOfIntersections) {
  int intersectionCount = 0;
  digitalWrite(leftDirection, HIGH); //Set left motor direction to forward
  digitalWrite(rightDirection, HIGH); //Set right motor direction to forward
  while (intersectionCount < numOfIntersections) {//While not at the desired intersection, keep moving forward
    followLineF(10);
    int count = 0;
    Serial.println("intersection loop");
    while (count < 10) {
      followLineF(20);
      //      Serial.println("count loop");
      if ((analogRead(lIRPin) > thresh) && (analogRead(rIRPin) > thresh)) count++;
      else count = 0;
      delay(1);
    }
    int temp = intersectionCount;
    count = 0;
    while (intersectionCount < temp + 1) {
      while (count < 12) {
        followLineF(20);
        if ((analogRead(lIRPin) < thresh) || (analogRead(rIRPin) < thresh)) count++;
        else count = 0;
        delay(1);
      }
      intersectionCount++;
      Serial.println("Intersections" + (String) intersectionCount);
    }

  }
  analogWrite(leftSpeed, 0);
  analogWrite(rightSpeed, 0);
  delay(100);
}

//Function to turn in a specified direction until a black line is hit
void turn(int dir) {
  //drive a little past the intersection
  delay(50);
  followLineF(20);
  delay(delayBeforeT);

  if (dir == 1) { //Begin turning counter-clockwise to ensure that center line sensor is not scaning the black tape
    analogWrite(leftSpeed, lSP - turnMod);
    analogWrite(rightSpeed, rSP - turnMod);
    digitalWrite(leftDirection, LOW);
    digitalWrite(rightDirection, HIGH);
    delay(delayTLeft);
    cVal = analogRead(cIRPin);
    pcVal = 0;
    while (cVal < thresh && pcVal < thresh) {
      pcVal = cVal;
      delay(20);
      cVal = analogRead(cIRPin);
    }
    analogWrite(leftSpeed, 0);
    analogWrite(rightSpeed, 0);
    delay(50);
    if (cd == 0) { //Update direction robot is facing
      cd = 3;
    } else {
      cd = cd - 1;
    }
  }

  else { //Begin turning clockwise to ensure that center line sensor is not scaning the black tape
    analogWrite(leftSpeed, lSP - turnMod);
    analogWrite(rightSpeed, rSP - turnMod);
    digitalWrite(leftDirection, HIGH);
    digitalWrite(rightDirection, LOW);
    delay(delayTRight);
    cVal = analogRead(cIRPin);
    pcVal = 0;
    while (cVal < thresh && pcVal < thresh) {
      pcVal = cVal;
      delay(20);
      cVal = analogRead(cIRPin);
    }
    analogWrite(leftSpeed, 0);
    analogWrite(rightSpeed, 0);
    delay(50);
    cd = (cd + 1) % 4; //Update direction robot is facing
  }
  Serial.println("sweep");
  lVal = analogRead(lIRPin);
  cVal = analogRead(cIRPin);
  rVal = analogRead(rIRPin);
  delay(50);
  if (cVal < thresh) {
    sweep(dir);
  }
  analogWrite(leftSpeed, 0);
  analogWrite(rightSpeed, 0);
}

void sweep(int lastSide) {
  if (lastSide == 0)//left
  {
    digitalWrite(leftDirection, LOW);
    digitalWrite(rightDirection, HIGH);
    analogWrite(leftSpeed, lSP - turnMod - 40);
    analogWrite(rightSpeed, rSP - turnMod - 40);
    cVal = analogRead(cIRPin);
    while (cVal < thresh) { //Continue rotating in specified direction until the center line sensor reads the black tape value
      cVal = analogRead(cIRPin);
    }
  }
  else {
    digitalWrite(leftDirection, HIGH);
    digitalWrite(rightDirection, LOW);
    analogWrite(leftSpeed, lSP - turnMod - 40);
    analogWrite(rightSpeed, rSP - turnMod - 40);
    cVal = analogRead(cIRPin);
    while (cVal < thresh) { //Continue rotating in specified direction until the center line sensor reads the black tape value
      cVal = analogRead(cIRPin);
    }
  }
  analogWrite(leftSpeed, 0);
  analogWrite(rightSpeed, 0);
  delay(50);
}

void turnWithDice()
{
  followLineF(-30);
  delay(200);
  turn(1);
  if (dIn == 0) { //Update direction robot is facing
    cd = 2;
  }
  else if (dIn == 1) {
    cd = 3;
  }
  else if (dIn == 3)
  {
    cd = 1;
  }

  //  analogWrite(leftSpeed, 0);
  //  analogWrite(rightSpeed, 0);
  //  delay(50);
  followLineF(20);
  delay(100);
}

void closeGrip() {
  int i = 0;
  int x = 190;
  while (x > 65) {
    tilt.write(x);
    x--;
    delay(15);
  }

  forceReading = analogRead(forceSensor);


  while (forceReading < gripThresh) {
    forceReading = analogRead(forceSensor);

    i++;
    int j = i % 110;

    grip.write(j);
    delay(15);

    if (j == 0) {
      delay(500);
    }
  }
  tilt.write(190);
  Serial.println("OBJECT GRABBED");
}

void dropDice() {
  analogWrite(leftSpeed, 0);
  analogWrite(rightSpeed, 0);
  int x = 190;
  while (x > 65) {
    tilt.write(x);
    x--;
    if (x == 80) {
      grip.write(0);
      Serial.println("Dice Dropped");
    }
  }
}


void approachDice() {
  //  if (dIn == 3)
  //  {
  //    cx--;
  //  }
  //  else if (dIn == 0)
  //  {
  //    cy++;
  //  }
  //  else if (dIn == 1)
  //  {
  //    cx++;
  //  }

  IRVal = analogRead(IRpin);
  leftBumper = digitalRead(lBump);
  rightBumper = digitalRead(rBump);
  while (leftBumper && rightBumper)
  {
    leftBumper = digitalRead(lBump);
    rightBumper = digitalRead(rBump);
    digitalWrite(leftDirection, HIGH);
    digitalWrite(rightDirection, HIGH);
    fIRThresh = fIRThresh + 500;
    followLineF(0);
  }
  fIRThresh = fIRThresh - 500;
  digitalWrite(leftDirection, LOW);
  digitalWrite(rightDirection, LOW);
  analogWrite(leftSpeed, lSP - turnMod);
  analogWrite(rightSpeed, rSP - turnMod);
  delay(200);
  analogWrite(leftSpeed, 0);
  analogWrite(rightSpeed, 0);
  closeGrip();

  turnWithDice();
}

void approachBin() {
  IRVal = analogRead(IRpin);
  leftBumper = digitalRead(lBump);
  rightBumper = digitalRead(rBump);
  while (leftBumper && rightBumper)
  {
    leftBumper = digitalRead(lBump);
    rightBumper = digitalRead(rBump);
    digitalWrite(leftDirection, HIGH);
    digitalWrite(rightDirection, HIGH);
    fIRThresh = fIRThresh + 500;
    followLineF(0);
  }
  fIRThresh = fIRThresh - 500;
  dropDice();
  Serial.println("dice dropped");
  digitalWrite(leftDirection, LOW);
  digitalWrite(rightDirection, LOW);
  analogWrite(leftSpeed, lSP);
  analogWrite(rightSpeed, rSP);
  delay(400);
  Serial.println("went back");
  analogWrite(leftSpeed, lSP - turnMod + resetTMod);
  analogWrite(rightSpeed, rSP - turnMod + resetTMod);
  digitalWrite(leftDirection, LOW);
  digitalWrite(rightDirection, HIGH);
  turn(1);
  followLineF(-20);
  delay(300);
  analogWrite(leftSpeed, 0);
  analogWrite(rightSpeed, 0);
  cd = 0;
  delay(50);
  tilt.write(190);
  delay(50);
}
