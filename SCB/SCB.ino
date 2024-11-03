#include <Servo.h>

Servo ballSorter;
Servo gate;

// Servo Base Positions
int home = 95;
int left = home + 60;
int right = home - 52;

// Gate Servo Base Positions
int closed = 83;
int openedLeft = 98;
int openedRight = 68;

// Activators & Pins
int infraredSensorPin = 12;
int gateOpenLeftActivatorPin = 4;
int gateOpenRightActivatorPin = 5;
int sortingActivatorPin = 10;

// Gate Movement
int gatePos;
int gateSpeed = 30;
int gateClosingSpeed = 40;

// Sorting movement
int sortPos;
int sortDelay = 300;
int waitForNextDelay = 400;


// Global State and General Settings
int gateState = 0; // 0: Closed; 1: Open Left; 2: Open Right
bool sortingActivated = false;
int iteration = 2;
int delayTime = 300;
// TODO: When receiving a signal, keep the circuit working. 
// Connect power between boards and use a transistor to send signal from ESP32

void setup() {
  Serial.begin(9600);
  pinMode(1, OUTPUT);
  pinMode(infraredSensorPin, INPUT); // Infrared sensor

  // Sorter Setup
  ballSorter.attach(8);
  ballSorter.write(home);
  sortPos = home;

  // Gate Setup
  gate.attach(7);
  gate.write(closed);
  gatePos = closed;

  Serial.println("===================");
  delay(4000);
}

void loop() {
  digitalWrite(1, HIGH);

  Serial.print("Sort Activator: ");
  Serial.println(digitalRead(sortingActivatorPin));
  Serial.print("Left Activator: ");
  Serial.println(digitalRead(gateOpenLeftActivatorPin));
  Serial.print("Right Activator: ");
  Serial.println(digitalRead(gateOpenRightActivatorPin));
  Serial.println("---------------------");
  
  
  
  sortingActivated = digitalRead(sortingActivatorPin);

  if(sortingActivated) { // Sorting Logic
    int isBlack;
    isBlack = digitalRead(infraredSensorPin);

    /* Serial.println();
    Serial.print("Black: ");
    Serial.print(isBlack);
    Serial.println(); */

    if(isBlack) {
      ballSorter.write(left);
      sortPos = left;
      Serial.print("Servo at: ");
      Serial.println(sortPos);
    } else {
      ballSorter.write(right);
      sortPos = right;
      Serial.print("Servo at: ");
      Serial.println(sortPos);
    }

    delay(sortDelay);
    ballSorter.write(home);
    delay(waitForNextDelay);
  } else { // Gate Logic
    if(digitalRead(gateOpenLeftActivatorPin)) {
      gateState = 1;
    } else if(digitalRead(gateOpenRightActivatorPin)) {
      gateState = 2;
    } else {
      gateState = 0;
    }

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
  }

  delay(delayTime);
}

void moveGate(int target, int speed) {
  if(gatePos == target) {
    Serial.println("We're here, not moving");
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