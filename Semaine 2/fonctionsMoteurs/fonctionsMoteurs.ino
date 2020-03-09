//Fichier source des fonction moteurs 


//Définition des pins pour les moteurs 
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11 
#define carSpeed 225 

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
