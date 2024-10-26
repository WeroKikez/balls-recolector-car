#include <Servo.h>

Servo ballSorter;
int home = 95;
int left = home + 60;
int right = home - 55;

bool sortingActivated = false;
int sortDelay = 1000;

void setup() {
  Serial.begin(9600);
  pinMode(5 , INPUT);

  ballSorter.attach(8);
  ballSorter.write(home);
  delay(5000);
}

void loop() {
  if(Serial.available() == 0) {
    int activate = Serial.parseInt();
    switch (activate) {
      case 1:
        sortingActivated = true;
        Serial.println("Active");
        break;

      case 2:
        sortingActivated = false;
        ballSorter.write(home);
        break;
    }
  }

  if(sortingActivated) {
    int isBlack = 0;
    isBlack = digitalRead(5);

    if(isBlack) {
      ballSorter.write(left);
      Serial.print("Servo at: ");
      Serial.println(left);
    } else {
      ballSorter.write(right);
      Serial.print("Servo at: ");
      Serial.println(right);
    }

    delay(sortDelay);

    ballSorter.write(home);
  }

  delay(2000);
}
