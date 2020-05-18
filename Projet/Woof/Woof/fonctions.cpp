//
//  fonctions.cpp
//  Woof
//
//  Created by John Levy on 20/03/2020.
//  Copyright © 2020 John Levy. All rights reserved.
//

#include "fonctions.hpp"

/* //// Définitons des Pins de la carte \\\\ */

// Pins Moteurs

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

//Pin Ultra Sons
int Echo = A4;
int Trig = A5;



/* //// Fonctions concernant le mouvement des moteurs \\\\ */

void forward(int carSpeed)
{
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

void backward(int carSpeed)
{
    analogWrite(ENA, carSpeed);
    analogWrite(ENB, carSpeed);
    //Reculer les moteurs gauches
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    //Reculer les moteurs droits
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void right(int carSpeed)
{
    analogWrite(ENA, carSpeed);
    analogWrite(ENB, carSpeed);
    //Avancer les moteurs gauches
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    //Reculer les moteurs droits
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void left(int carSpeed)
{
    analogWrite(ENA, carSpeed);
    analogWrite(ENB, carSpeed);
    //Avancer les moteurs droits
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    //Reculer les moteurs gauches
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
}

void stop()
{
    digitalWrite(ENA, LOW);
    digitalWrite(ENB, LOW);
}

/* //// Fonctions utilisées pour éviter les obstacles \\\\ */

//Variables utilisées
int rightDistance = 0, leftDistance = 0, middleDistance = 0;

int testDistance()
{
    digitalWrite(Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(20);
    digitalWrite(Trig, LOW);
    float Distance = pulseIn(Echo, HIGH);
    Distance = Distance / 58;
    return(int)Distance;
}

void eviterObstacle(int middleDistance, int leftDistance, int rightDistance)
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
    
    if(rightDistance < leftDistance)
    {
        left();
        delay(280);
    }
    else if(leftDistance < rightDistance)
    {
        right();
        delay(280);
    }
    else if((rightDistance <= 50) || (leftDistance <= 50))
    {
        backward();
        delay(200);
    }
    else
    {
        forward();
    }
}
