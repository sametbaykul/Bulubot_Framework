//--------------------------------------------------
// Bulubot Framework
// v.1.0.0
// by Samet Baykul
//--------------------------------------------------

//--------------------------------------------------
// DEFINITIONS
//--------------------------------------------------

// Properties
// --------------------------------------------------

double SPEED;
int STEP;
std::string SELF_DEF;

// Fundamental Methods
// --------------------------------------------------

void INIT();
void UPDATE();

// Trace Methods
// --------------------------------------------------

void TRACE(const std::string &Message);
void TRACE_INT(const std::string &Label, int Value);
void TRACE_POINT_INT(const std::string &Label_1, const std::string &Label_2, int Value_1, int Value_2);
void TRACE_DOUBLE(const std::string &Label, double Value);
void TRACE_POINT_DOUBLE(const std::string &Label_1, const std::string &Label_2, double Value_1, double Value_2);
void TRACE_END();

// Sensor Methods
// --------------------------------------------------

double READ_SENSOR_DS_L();
double READ_SENSOR_DS_R();
double READ_SENSOR_LS();

// Motion Methods
// --------------------------------------------------

void SET_MOTOR_FL_SPEED(double Speed);
void SET_MOTOR_FR_SPEED(double Speed);
void SET_MOTOR_BL_SPEED(double Speed);
void SET_MOTOR_BR_SPEED(double Speed);

// Supervisor Methods
// --------------------------------------------------

double GET_POSITION_X(int Robot_Index);
double GET_POSITION_Z(int Robot_Index);
double GET_ROTATION_DEGREE(int Robot_Index);
double GET_ROTATION_RADIAN(int Robot_Index);
double GET_SPEED_X(int Robot_Index);
double GET_SPEED_Z(int Robot_Index);
double GET_SPEED(int Robot_Index);

//--------------------------------------------------
// METHODS
//--------------------------------------------------

// Trace Methods

void TRACE_END()
{
  if (DIAGNOSIS && SELF_DEF == TRACER)
  {
    printf("\n");
  }
}
void TRACE(const std::string &Message)
{
  if (DIAGNOSIS && SELF_DEF == TRACER)
  {
    printf(" | %s \n", Message.c_str());
  }
}
void TRACE_INT(const std::string &Label, int Value)
{
  if (DIAGNOSIS && SELF_DEF == TRACER)
  {
    printf(" | %s : %d", Label.c_str(), Value);
  }
}
void TRACE_DOUBLE(const std::string &Label, double Value)
{
  if (DIAGNOSIS && SELF_DEF == TRACER)
  {
    printf(" | %s : %f", Label.c_str(), Value);
  }
}
void TRACE_POINT_INT(const std::string &Label_1, const std::string &Label_2, int Value_1, int Value_2)
{
  if (DIAGNOSIS && SELF_DEF == TRACER)
  {
    printf(" | (%s, %s) : (%d, %d)", Label_1.c_str(), Label_2.c_str(), Value_1, Value_2);
  }
}
void TRACE_POINT_DOUBLE(const std::string &Label_1, const std::string &Label_2, double Value_1, double Value_2)
{
  if (DIAGNOSIS && SELF_DEF == TRACER)
  {
    printf(" | (%s, %s) : (%f, %f)", Label_1.c_str(), Label_2.c_str(), Value_1, Value_2);
  }
}

// Sensor Methods

double READ_SENSOR_DS_L()
{
  return LIST_DS_VALUES[0];
}
double READ_SENSOR_DS_R()
{
  return LIST_DS_VALUES[1];
}
double READ_SENSOR_LS()
{
  return LIST_LS_VALUES[0];
}

// Motor Methods

void SET_MOTOR_FL_SPEED(double Speed)
{
  LIST_MOTOR[0] -> setVelocity(Speed);
}
void SET_MOTOR_FR_SPEED(double Speed)
{
  LIST_MOTOR[1] -> setVelocity(Speed);
}
void SET_MOTOR_BL_SPEED(double Speed)
{
  LIST_MOTOR[2] -> setVelocity(Speed);
}
void SET_MOTOR_BR_SPEED(double Speed)
{
  LIST_MOTOR[3] -> setVelocity(Speed);
}

// Supervisor Methods

double GET_POSITION_X(int Robot_Index)
{
  const double *_pos = NODE_LIST[Robot_Index] -> getPosition();
  
  return _pos[0];
}
double GET_POSITION_Z(int Robot_Index)
{
  const double *_pos = NODE_LIST[Robot_Index] -> getPosition();
  
  return _pos[2];
}
double GET_ROTATION_DEGREE(int Robot_Index)
{
  const double *_rot = NODE_LIST[Robot_Index] -> getOrientation();
  
  return atan2(_rot[6], _rot[8]) * 180.0 / PI;
}
double GET_ROTATION_RADIAN(int Robot_Index)
{
  const double *_rot = NODE_LIST[Robot_Index] -> getOrientation();

  return atan2(_rot[6], _rot[8]);
}
double GET_SPEED_X(int Robot_Index)
{
  const double *_speed = NODE_LIST[Robot_Index] -> getVelocity();
  
  return _speed[0];
}
double GET_SPEED_Z(int Robot_Index)
{
  const double *_speed = NODE_LIST[Robot_Index] -> getVelocity();
  
  return _speed[2];
}
double GET_SPEED(int Robot_Index)
{
  const double *_speed = NODE_LIST[Robot_Index] -> getVelocity();
  
  double _speed_x = _speed[0];
  double _speed_z = _speed[2];
  
  return sqrt(_speed_x * _speed_x + _speed_z * _speed_z);
}
