#include <Arduino.h>

// pins
int motorA = 5;
int motorB = 6;
int enablePin = 3;
int poti = A0;
int touch = A1;

int target = -1;
int faderMin = 1;
int faderMax = 1023;
int lastTouch = 0;
int currentTouch = 0;

int lastFaderVal = 0;
int curentFaderVal = 0;

void setup() {
  pinMode(enablePin, OUTPUT);
  Serial.begin(9600);
  Serial.flush();
  Serial.println("CONNECT");
}

void loop() {

  if(target == -1 && Serial.available() > 0){
    if (Serial.read() == 0x01){
      if (Serial.read() == 0x00){
        int value;
        value = (((int)Serial.read() << 8) + ((int)Serial.read()));
        Serial.println( (String)"target " + value + "");
        target = value;
      }
    }
  }

  // currentTouch = analogRead(touch);
  // if(false){
  //   analogWrite(motorA, 0);
  //   analogWrite(motorB, 0);
  //   digitalWrite(enablePin, LOW);

  //   Serial.println("touch");
  //   target = -1;
  // }

  curentFaderVal = analogRead(poti);

  if (target != -1) {
    digitalWrite(enablePin, HIGH);
    if (curentFaderVal > target ) {
      analogWrite(motorA, 255);
      analogWrite(motorB, 0);
    } else if (curentFaderVal < target ) {
      analogWrite(motorA, 0);
      analogWrite(motorB, 255);
    } else {
      analogWrite(motorA, 0);
      analogWrite(motorB, 0);
      target = -1;
      Serial.println("end");
    }
  } else {
    digitalWrite(enablePin, LOW);

    if(abs(curentFaderVal - lastFaderVal) > 2){
      lastFaderVal = curentFaderVal;
      Serial.println( (String)"MOVE    FADER    0    " + lastFaderVal + "");
    }
  }

}
