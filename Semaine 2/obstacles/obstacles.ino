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
  digitalWrite(Trig, LOW); 
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig, LOW); 
  float Distance = pulseIn(Echo, HIGH);
  Distance = Distance / 58; 
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
  stop();
}

void loop() {
  leServo.write(90);
  delay(500);
  middleDistance = testDistance(); //Distance d'un potentiel objet devant lui

  if (middleDistance <=50) //Dans le cas où il y a un objet
  {
    stop();
    delay(500);
    leServo.write(10); //On tourne les yeux à droite
    delay(1000);
    rightDistance = testDistance();
    
    delay(500); 
    leServo.write(90); //On remet les yeux au milieu
    delay(1000);
    leServo.write(180); //On tourne les yeux à gauche 
    delay(1000);
    leftDistance = testDistance(); 

    delay(500);
    leServo.write(90); //On remet les yeux aux milieu
    delay(1000);

    if(rightDistance < leftDistance){
      left(); 
      delay(280); 
      }
    else if(leftDistance < rightDistance){
      right();
      delay(280); 
      }
    else if((rightDistance <= 50) || (leftDistance <= 50)) {
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
