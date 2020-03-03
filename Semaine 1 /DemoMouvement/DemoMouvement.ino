
//Programme de démo pour la voiture :
//avancer pendant 2 sec
//reculer pendant 2 sec 
//tourner à gauche pendant 1 sec 
//avancer puis reculer (2sec)
//tourner à droite pendant 1 sec
//avancer puis reculer

//Définition des pins utilisés
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11 

//Fonctions avancer, reculer, tourner gauche/droite

void forward(){
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  //Avancer les moteurs gauches 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //Avancer les moteurs droits 
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 
}

void backward(){
  digitalWrite(ENA, HIGH); 
  digitalWrite(ENA, HIGH);
  //Reculer les moteurs gauches
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  //Reculer les moteurs droits
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 
}

void turnLeft(){
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH); 
  //Avancer moteurs droits
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 
  //Reculer les moteurs gauches
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void turnRight(){
  digitalWrite(ENA, HIGH); 
  digitalWrite(ENB, HIGH);
  //Avancer les moteurs gauches
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW); 
  //Reculer les moteurs droits 
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 
}

void setup(){
  //Setup des pins en OUTPUT 
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT); 
}

void loop(){
  forward(); //Avancer 
  delay(2000); //On laisse durer l'action pendant 2 secondes
  backward(); //Reculer
  delay(2000); 
  turnLeft(); //Tourner à droite
  delay(400); 
  forward();
  delay(2000);
  backward();
  delay(2000);
  turnRight();
  delay(400);
}
