#include <Servo.h>

Servo gate;

// Gate Servo Base Positions
int closed = 83;
int openedLeft = 96;
int openedRight = 70;
int delayTime = 4000;

// Movement
int gatePos;
int speed = 250;
int stepsAmount = 4; 

// Global State
int gateState = 0; // 0: Closed; 1: Open Left; 2: Open Right
int iteration = 2;

void setup() {
  Serial.begin(9600);

  gate.attach(7);
  gate.write(closed);
  gatePos = closed;
  Serial.println("===================");
  Serial.print("Servo Gate At: ");
  Serial.println(gatePos);
}

void loop() {
  Serial.print("Gate State: ");
  Serial.println(gateState);
  Serial.print("Servo Gate At: ");
  Serial.println(gatePos);
  Serial.println("--------------------");

  switch (gateState) {
    case 0: 
      moveGate(closed, 60);
      break;
    case 1: 
      moveGate(openedLeft, 40);
      break;
    case 2: 
      moveGate(openedRight, 40);
      break;
  }

  delay(delayTime);
}

void moveGate(int target, int speed) {
  if(gatePos == target) {
    return;
  }

  if(target > gatePos) { // left
    for(int pos = gatePos; pos <= target; pos++) {
      gate.write(pos);
      delay(speed);
    }
  } else { // right
    for(int pos = gatePos; pos >= target; pos--) {
      gate.write(pos);
      delay(speed);
    }
  }

  gatePos = target;
}
