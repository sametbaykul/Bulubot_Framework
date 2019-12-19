// --------------------------------------------------
// Controller
// v.1.0.0
// by Samet Baykul
// --------------------------------------------------

//--------------------------------------------------
// IMPORTS
//--------------------------------------------------

#include <stdio.h>
#include <string>
#include <iostream>
#include <math.h>
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>

//--------------------------------------------------
// NAMESPACES
//--------------------------------------------------

using namespace webots;

//--------------------------------------------------
// CONSTANTS
//--------------------------------------------------

// Fine Tunnings
// ...

// Constant Properties
#define UPDATE_DELAY 64
#define MAX_SPEED 3.14

// Class Instances
Robot *ROBOT = new Robot();
DistanceSensor *LIST_DS[2];
Motor *LIST_MOTOR[4];

//--------------------------------------------------
// VARIABLES
//--------------------------------------------------

char LIST_DS_NAMES[2][4] = 
{
  "LS", "DS_1"
};
char LIST_MOTOR_NAMES[2][7] = 
{
  "MOTOR_R", "MOTOR_L"
};

double LIST_DS_VALUES[2];
double LIST_MOTOR_VALUES[4];

bool OBSTACLE_L;
bool OBSTACLE_R;

//--------------------------------------------------
// DECLARATIONS
//--------------------------------------------------

void INIT_SENSORS(); 
void INIT_MOTORS();
void UPDATE(); 
void READ_SENSORS();
void CONTROL_MOTORS();

//--------------------------------------------------
// MAIN
//--------------------------------------------------

int main(int argc, char **argv)
{
  INIT_SENSORS();
  INIT_MOTORS();
    
  while (ROBOT -> step(UPDATE_DELAY) != -1) 
  {
    UPDATE(); 
  };

  delete ROBOT;
  return 0;
}

//--------------------------------------------------
// INITIALIZER
//--------------------------------------------------

void INIT_SENSORS()
{
  for (int i = 0; i < 2; i++) 
  {
    LIST_DS[i] = ROBOT -> getDistanceSensor(LIST_DS_NAMES[i]);
    LIST_DS[i] -> enable(UPDATE_DELAY);
  }
}

void INIT_MOTORS()
{
  for (int i = 0; i < 2; i++) 
  {
    LIST_MOTOR[i] = ROBOT -> getMotor(LIST_MOTOR_NAMES[i]);
    LIST_MOTOR[i] -> setVelocity(0);
    LIST_MOTOR[i] -> setPosition(INFINITY);
  }
}

//--------------------------------------------------
// UPDATE
//--------------------------------------------------

void UPDATE()
{
  //READ_SENSORS();
  //CONTROL_MOTORS();
}

void READ_SENSORS()
{
  for (int i = 0; i < 2 ; i++)
  {
    LIST_DS_VALUES[i] = LIST_DS[i] -> getValue();
  }
  
  OBSTACLE_L = LIST_DS_VALUES[0] < 980.0;
  OBSTACLE_R = LIST_DS_VALUES[1] < 980.0;
}
void CONTROL_MOTORS()
{
  double speed_l = MAX_SPEED;
  double speed_r = MAX_SPEED;

  if (OBSTACLE_L) 
  {
    speed_l  = MAX_SPEED;
    speed_r = -MAX_SPEED;
  }
  else if (OBSTACLE_R) 
  {
    speed_l  = -MAX_SPEED;
    speed_r = MAX_SPEED;
  }

  printf("Left: (%f, %f)| Right: (%f, %f)\n", LIST_DS_VALUES[0], speed_l, LIST_DS_VALUES[1], speed_r);
  LIST_MOTOR[0] -> setVelocity(speed_l);
  LIST_MOTOR[1] -> setVelocity(speed_r);
  LIST_MOTOR[2] -> setVelocity(speed_l);
  LIST_MOTOR[3] -> setVelocity(speed_r);
}
