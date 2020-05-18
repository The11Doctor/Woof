//
//  fonctions.hpp
//  Woof
//
//  Created by John Levy on 20/03/2020.
//  Copyright © 2020 John Levy. All rights reserved.
//

#ifndef fonctions_hpp
#define fonctions_hpp

#include <stdio.h>
#include "Arduino.h"
#include <Servo.h>

/*  ////   Fonctions concernant le mouvement des moteurs \\\\ */

void forward(int carSpeed);
void backward(int carSpeed);
void right(int carSpeed);
void left(int carSpeed);
void stop();

/* //// Fonctions utilisées pour éviter les obstacles \\\\ */
int testDistance();
void eviterObstacle(int middleDistance, int leftDistance, int rightDistance);


#endif /* fonctions_hpp */
