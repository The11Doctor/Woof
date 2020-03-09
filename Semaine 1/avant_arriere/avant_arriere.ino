#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11 

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT); 
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
}

void loop() {
  //Avancer les moteurs gauches 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //Avancer les moteurs droits 
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(2000);
  digitalWrite(IN1, LOW);      
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);      
  digitalWrite(IN4, LOW); 
  delay(500); 
  //Reculer les moteurs gauches
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  //Reculer les moteurs droits
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 
  delay(2000); 
  digitalWrite(IN1, LOW);      
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, HIGH);      
  digitalWrite(IN4, HIGH);  //stop
  delay(500); 
  

}
