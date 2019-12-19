// --------------------------------------------------
// Bulubot Controller
// v.1.0.0
// by Samet Baykul
// --------------------------------------------------

// --------------------------------------------------
// C++ PACK
// --------------------------------------------------

#include <stdio.h>
#include <string>
#include <iostream>
#include <math.h>

#define PI 3.14159265

// --------------------------------------------------
// WEBOTS PACK
// --------------------------------------------------

#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
#include <webots/LightSensor.hpp>
#include <webots/Supervisor.hpp>
#include <webots/Node.hpp>

using namespace webots;
using namespace std;

Supervisor *SUPER;
DistanceSensor *LIST_DS[2];
LightSensor *LIST_LS[1];
Motor *LIST_MOTOR[4];

// --------------------------------------------------
// BULUBOT FW PACK
// --------------------------------------------------

#include <FineTunning.cpp>
#include <Definitions.cpp>

Node *NODE_LIST[SWARM_WIDTH];
Node *SELF;
std::string SELF_DEF;

#include <Framework.cpp>
#include <Motion.cpp>

Motion MOTION(true);

#include <Main.cpp>

// --------------------------------------------------
// DECLARATIONS
// --------------------------------------------------

void init_sensors();
void init_motors();
void init_supervisor();
void read_sensors();

//--------------------------------------------------
// MAIN
//--------------------------------------------------

int main(int argc, char **argv)
{
  init_sensors();
  init_motors();
  init_supervisor();
  init();
    
  while (ROBOT -> step(UPDATE_DELAY) != -1) 
  {
    read_sensors();
    update();
    UPDATE(); 
  };

  delete ROBOT;
  return 0;
}

//--------------------------------------------------
// INITIALIZER
//--------------------------------------------------

void init_sensors()
{
  // Distance Sensors
  for (int i = 0; i < TOTAL_DS; i++) 
  {
    LIST_DS[i] = ROBOT -> getDistanceSensor(LIST_DS_NAMES[i]);
    LIST_DS[i] -> enable(UPDATE_DELAY);
  }
  // Light Sensors
  for (int i = 0; i < TOTAL_LS; i++) 
  {
    LIST_LS[i] = ROBOT -> getLightSensor(LIST_LS_NAMES[i]);
    LIST_LS[i] -> enable(UPDATE_DELAY);
  }
}

void init_motors()
{
  for (int i = 0; i < TOTAL_MOTOR; i++) 
  {
    LIST_MOTOR[i] = ROBOT -> getMotor(LIST_MOTOR_NAMES[i]);
    LIST_MOTOR[i] -> setVelocity(0);
    LIST_MOTOR[i] -> setPosition(INFINITY);
  }
}

void init_supervisor()
{
  SELF = SUPER -> getSelf();
  SELF_DEF = SELF -> getDef();

  for (int i = 0; i < SWARM_WIDTH; i++) 
  {
    NODE_LIST[i] = SUPER -> getFromDef(LIST_ROBOTS[i]);
  }
}

//--------------------------------------------------
// METHODS
//--------------------------------------------------

void init()
{
  SPEED = (MOTOR_RPM / 60) * 3.141592654;

  INIT();
}

void update()
{
  STEP++;
  
  MOTION.UPDATE();
}

//--------------------------------------------------
// FUNCTIONS
//--------------------------------------------------

void read_sensors()
{
  // Distance Sensors
  for (int i = 0; i < TOTAL_DS; i++)
  {
    LIST_DS_VALUES[i] = LIST_DS[i] -> getValue();
  }
}
