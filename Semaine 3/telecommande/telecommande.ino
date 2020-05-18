#include <IRremote.h>

//Définition des pins pour les moteurs 
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11 
#define carSpeed 225 

#define RECV_PIN 12

#define F 16736925
#define UNKNOWN_F 5316027
#define B 16754775
#define UNKNOWN_B 2747854299
#define L 16720605
#define UNKNOWN_L 1386468383
#define R 16761405
#define UNKNOWN_R 553536955
#define S 16712445
#define UNKNOWN_S 3622325019

IRrecv irrecv(RECV_PIN);
decode_results results; 
unsigned long val; 

/***

Definitions fonctions mouvement 

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

/***

Starting setup

**///

void setup() {
  //Setup des pins pour les moteurs 
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  irrecv.enableIRIn(); 
  stop(); 
}

void loop() {
  if(irrecv.decode(&results))
  {
    val = results.value; 
    irrecv.resume();
    switch (val)
    {
      case F:
      case UNKNOWN_F:
        forward();
        break;
      case B:
      case UNKNOWN_B:
        backward();
        break; 
      case L:
      case UNKNOWN_L:
        left();
        break;
      case R:
      case UNKNOWN_R:
        right();
        break; 
      case S:
      case UNKNOWN_S:
        stop();
        break;
      default:
        break; 
      }
    }
}
