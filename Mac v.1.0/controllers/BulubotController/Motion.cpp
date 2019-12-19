// --------------------------------------------------
// Motion
// v.1.0.0
// by Samet Baykul
// --------------------------------------------------

// ...

// --------------------------------------------------
// CLASS DEFINITIONS
// --------------------------------------------------

class Motion
{
  public:
    // Constructor
    Motion(bool Activate);
    // Objects
  private:
    struct FRAME
    {
      bool Motor_FL;
      bool Motor_FR;
      bool Motor_BL;
      bool Motor_BR;
    };
    struct MOTION
    {
      bool Active;
      int Total_Frame;
      int Frame_Interval;
      double Speed;
      FRAME FRAME_LIST[TOTAL_MOTION_FRAME];
    };
    // Data
    MOTION MOTION_LIST[TOTAL_MOTION_TYPES];
    // Fundemental
    bool _active;
    bool _run;
    int _current_motion_index;
    int _current_frame_index;
    int _step_counter;
    int _step_A;
    int _step_B;
    void (*_call_back)();
    // Functions
    bool check_run();
    void set_run();
    void finish_motion();
    void reset();
    void trace();
  public:  
    // Methods
    void NEW_MOTION(int Motion_Index, int Total_Frame, int Frame_Interval, double Speed);
    FRAME NEW_FRAME(bool Motor_FL, bool Motor_FR, bool Motor_BL, bool Motor_BR);
    void SET_MOTION_FRAME(int Motion_Index, int Frame_Index, FRAME Frame);
    void SET_AFTER_MOTION(void (*CallBack)());
    void START(int Motion_Index);
    void STOP();
    void UPDATE();
};

// --------------------------------------------------
// CONSTRUCTOR
// --------------------------------------------------

Motion::Motion(bool Activate)
{
  _active = Activate;
  
  reset();
}

// --------------------------------------------------
// METHODS
// --------------------------------------------------

void Motion::NEW_MOTION(int Motion_Index, int Total_Frame, int Frame_Interval, double Speed)
{
  bool _ok = true;
  
  if (Motion_Index >= TOTAL_MOTION_TYPES)
  {
    _ok = false;
    
    TRACE("X - ERROR 001: NEW_MOTION() method parameter 'Motion_Index' should be less than FineTuning parameter 'TOTAL_MOTION_TYPES'");
  }
  
  if (Total_Frame >= TOTAL_MOTION_FRAME)
  {
    _ok = false;
    
    TRACE("X - ERROR 002: NEW_MOTION() method parameter 'Total_Frame' should be less than FineTuning parameter 'TOTAL_MOTION_FRAME'");
  }
  
  if (_ok)
  {
    MOTION_LIST[Motion_Index].Active = true;
    MOTION_LIST[Motion_Index].Total_Frame = Total_Frame;
    MOTION_LIST[Motion_Index].Frame_Interval = Frame_Interval;
    MOTION_LIST[Motion_Index].Speed = Speed;
  }
}

Motion::FRAME Motion::NEW_FRAME(bool Motor_FL, bool Motor_FR, bool Motor_BL, bool Motor_BR)
{
  FRAME _new_frame;
  
  _new_frame.Motor_FL = Motor_FL;
  _new_frame.Motor_FR = Motor_FR;
  _new_frame.Motor_BL = Motor_BL;
  _new_frame.Motor_BR = Motor_BR;
  
  return _new_frame;
}

void Motion::SET_MOTION_FRAME(int Motion_Index, int Frame_Index, FRAME Frame)
{
  bool _ok = true;
  
  if (Motion_Index >= TOTAL_MOTION_TYPES)
  {
    _ok = false;
    
    TRACE("X - ERROR 001: NEW_MOTION() method parameter 'Motion_Index' should be less than FineTuning parameter 'TOTAL_MOTION_TYPES'");
  }
  
  if (Frame_Index >= TOTAL_MOTION_FRAME)
  {
    _ok = false;
    
    TRACE("X - ERROR 002: NEW_MOTION() method parameter 'Frame_Index' should be less than FineTuning parameter 'TOTAL_MOTION_FRAME'");
  }
  
  if (_ok)
  {
    MOTION_LIST[Motion_Index].FRAME_LIST[Frame_Index] = Frame;
  }
}

void Motion::SET_AFTER_MOTION(void (*CallBack)())
{
  _call_back = (*CallBack);
}

void Motion::START(int Motion_Index)
{
  _current_motion_index = Motion_Index;
}

void Motion::STOP()
{
  reset();
}

void Motion::UPDATE()
{
  if (check_run())
  {
    set_run();
  }   
  
  if (_run)
  {
    double _speed = MOTION_LIST[_current_motion_index].Speed;
    bool _frame_data[4];

    _frame_data[0] = MOTION_LIST[_current_motion_index].FRAME_LIST[_current_frame_index].Motor_FL;
    _frame_data[1] = MOTION_LIST[_current_motion_index].FRAME_LIST[_current_frame_index].Motor_FR;
    _frame_data[2] = MOTION_LIST[_current_motion_index].FRAME_LIST[_current_frame_index].Motor_BL;
    _frame_data[3] = MOTION_LIST[_current_motion_index].FRAME_LIST[_current_frame_index].Motor_BR;
  
    for (int i = 0; i < 4; i ++)
    {
      LIST_MOTOR[i] -> setVelocity(_speed * _frame_data[i]);
    }
  }
  
  trace();
  
  _step_counter ++;
}

// --------------------------------------------------
// FUNCTIONS
// --------------------------------------------------

bool Motion::check_run()
{
  bool _result = true;

  if (_current_motion_index > -1)
  {
    if (_current_frame_index > -1 && _current_frame_index >= MOTION_LIST[_current_motion_index].Total_Frame)
    {
      _result = false;
      
      finish_motion();
    }
  }
  else
  {
    _result = false;
  }
 
  return _result; 
}
void Motion::set_run()
{
  bool _new_frame_run = false;

  if (_current_frame_index == -1)
  {
    _current_frame_index = 0;
    
    _new_frame_run = true;
  }
  
  if (_new_frame_run)
  {
    if (_step_counter <= 0)
    {
      _step_counter = STEP;
    }
    
    if (_step_A == -1)
    {
      _step_A = STEP;
    }
    
    if (_step_B == -1)
    {
      _step_B = STEP + MOTION_LIST[_current_motion_index].Frame_Interval;
    }
  }
  
  if (_step_counter >= _step_B)
  {
    _new_frame_run = true;
    _current_frame_index ++;
    _step_counter = STEP;
    _step_A = STEP;
    _step_B = STEP + MOTION_LIST[_current_motion_index].Frame_Interval;
  }
  
  _run = _new_frame_run;
}
void Motion::finish_motion()
{
  reset();
  
  for (int i = 0; i < 4; i ++)
  {
    LIST_MOTOR[i] -> setVelocity(0);
  }
  
  _call_back();
}
void Motion::reset()
{
  _run = false;
  _current_motion_index = -1;
  _current_frame_index = -1;
  _step_counter = -1;
  _step_A = -1;
  _step_B = -1;
  
  TRACE("RESET!");
}
void Motion::trace()
{
  if (_run)
  {
    TRACE_INT("STEP", STEP);
    TRACE_INT("_current_motion_index", _current_motion_index);
    TRACE_INT("_current_frame_index", _current_frame_index);
    TRACE_INT("_step_counter", _step_counter);
    TRACE_INT("_step_A", _step_A);
    TRACE_INT("_step_B", _step_B);
    TRACE_END();
  }
}


