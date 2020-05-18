#include <Servo.h>
Servo leServo;

//Setup du Sensor 
int Echo = A4;
int Trig = A5; 
int rightDistance = 0, leftDistance = 0, middleDistance = 0; 

//Pins pour les moteurs 
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define carSpeed 175

//// Fonctions pour le mouvement
void forward(){ 
  //Puissance et vitesse
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  //Avancer les moteurs gauches
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //Avancer les moteurs droits
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


void backward(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  //Reculer les moteurs gauches
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  //Reculer les moteurs droits
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 
  }
  
void right(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  //Avancer les moteurs gauches 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //Reculer les moteurs droits
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 
  }

void left(){

  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  //Avancer les moteurs droits 
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //Reculer les moteurs gauches
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  }

void stop(){
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  }

/////// Fin Fonctions du Mouvement

  

int testDistance() {
  float Distance;
  digitalWrite(Trig, LOW); 
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig, LOW); 
  float retard = pulseIn(Echo, HIGH);
  Serial.println(retard);
  Distance = ((retard*340)/10000)/2; 
  Serial.println(Distance);
  return(int)Distance;   
}

void setup() {
  leServo.attach(3,700,2400); 
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT); 
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(13, OUTPUT);
  stop();
}

void loop() {
  leServo.write(90);
  delay(500);
  forward();
  delay(500);
  middleDistance = testDistance;
  leServo.write(1);
  delay(145);
  rightDistance = testDistance(); //Distance d'un potentiel objet devant lui
  leServo.write(179);
  delay(290);
  leftDistance = testDistance();
  if(middleDistance<50 || leftDistance < 50 || rightDistance < 50) {
    leServo.write(90);
    stop();
    delay(500);
    
    if(rightDistance < leftDistance){
      left();
      delay(240);
      }
    else if(leftDistance < rightDistance){
      right();
      delay(240); 
      }
    else if((rightDistance <= 50) && (leftDistance <= 50)){
      backward();
      delay(200); 
      }
    else{
      forward();
      }
  }
  else{
    forward();
    }
  }
