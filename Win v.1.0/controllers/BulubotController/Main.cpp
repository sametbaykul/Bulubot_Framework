// --------------------------------------------------
// Bulubot Controller Manin
// v.1.0.0
// by ???
// --------------------------------------------------

//--------------------------------------------------
// DEFINITIONS
//--------------------------------------------------

// Define your functions here

void Set_Motion();
void Motion_Update();

//--------------------------------------------------
// MAIN
//--------------------------------------------------

void INIT()
{
  // This function is triggered once at the start

  // Motion Creation
  Set_Motion();
  MOTION.START(0);
}

void UPDATE()
{
  // This function is triggered at each step
  // In order to set execution frequency: Set "FineTunning -> UPDATE_DELAY"
  
  // These are example of using some important methods which includes TRACE and SUPERVISOR methods
  TRACE(SELF_DEF);
  TRACE_POINT_DOUBLE("BB_1 || POS_X", "POS_Z", GET_POSITION_X(0), GET_POSITION_Z(0));
  TRACE_DOUBLE("ROT", GET_ROTATION_DEGREE(0));
  TRACE_DOUBLE("SPEED", GET_SPEED(0));
  TRACE_END();
  TRACE_POINT_DOUBLE("BB_2 || POS_X", "POS_Z", GET_POSITION_X(1), GET_POSITION_Z(1));
  TRACE_DOUBLE("ROT", GET_ROTATION_DEGREE(1));
  TRACE_DOUBLE("SPEED", GET_SPEED(1));
  TRACE_END();
}

//--------------------------------------------------
// FUNCTIONS
//--------------------------------------------------

void Set_Motion()
{
  // Example for creation of a new motion
  // You can edit or define new motion like this
  
  MOTION.NEW_MOTION(0, 9, 16, SPEED);
  MOTION.SET_MOTION_FRAME(0, 0, MOTION.NEW_FRAME(0, 0, 1, 0));
  MOTION.SET_MOTION_FRAME(0, 1, MOTION.NEW_FRAME(1, 0, 1, 0));
  MOTION.SET_MOTION_FRAME(0, 2, MOTION.NEW_FRAME(1, 0, 1, 0));
  MOTION.SET_MOTION_FRAME(0, 3, MOTION.NEW_FRAME(1, 0, 0, 0));
  MOTION.SET_MOTION_FRAME(0, 4, MOTION.NEW_FRAME(0, 0, 0, 1));
  MOTION.SET_MOTION_FRAME(0, 5, MOTION.NEW_FRAME(0, 1, 0, 1));
  MOTION.SET_MOTION_FRAME(0, 6, MOTION.NEW_FRAME(0, 1, 0, 1));
  MOTION.SET_MOTION_FRAME(0, 7, MOTION.NEW_FRAME(0, 1, 0, 0));
  MOTION.SET_MOTION_FRAME(0, 8, MOTION.NEW_FRAME(1, 1, 1, 1));
  MOTION.SET_AFTER_MOTION(Motion_Update);
}

void Motion_Update()
{
  // This is a call-back function. It is triggered whenever a motion is completed
  
  MOTION.START(0);
}
