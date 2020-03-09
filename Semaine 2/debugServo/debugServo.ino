#include <Servo.h>

//Déclaration des variables 
Servo leServo;
int pinServo = 3;
int minAngle = 700;
int maxAngle = 2400; 

void setup() {
  leServo.attach(pinServo, minAngle, maxAngle);
  leServo.write(90); 
}

void loop() {

}
