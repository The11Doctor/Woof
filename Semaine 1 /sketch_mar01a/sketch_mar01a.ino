//Define Pins 
#define ENA 5
#define IN1 7
#define IN2 8 

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT); 
  digitalWrite(ENA, HIGH); 
}

void loop() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(500);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW); 
  delay(500);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  delay(500);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH); 
  delay(500); 
}
