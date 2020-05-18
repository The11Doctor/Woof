
/**
        Instructions pré-processeur 
**/

/*Définition des PIN pour les moteurs */
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11 
#define carSpeed 225 

/*Définitons pour le line tracking*/
#define LT_R 10
#define LT_M 4
#define LT_L 2
#define LT_Right !digitalRead(10)
#define LT_Middle !digitalRead(4)
#define LT_Left !digitalRead(2)
/**

      Fonctions Mouvement 

**/

void forward(){ 
  //Puissance
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

void setup() {
  /*Setup des pins pour le mouvement*/
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  /*Setup des pins pour le line tracking*/
  pinMode(LT_R, INPUT); 
  pinMode(LT_M, INPUT);
  pinMode(LT_L, INPUT); 
}

void loop() {
  if(LT_Middle)
  {
    forward();
    }
  else if(LT_Right)
  {
    right();
    while(LT_Right);
    }
  else if(LT_Left)
  {
    left();
    while(LT_Left);
    }
}
