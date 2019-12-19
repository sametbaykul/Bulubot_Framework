//--------------------------------------------------
// Definitions
// v.1.0.0
// by Samet Baykul
//--------------------------------------------------

// --------------------------------------------------
// CLASSES
// --------------------------------------------------

Robot *ROBOT = new Robot();

// --------------------------------------------------
// HARDWARE
// --------------------------------------------------

// Hardware Definitions

char LIST_DS_NAMES[TOTAL_DS][8] = {"DS_L", "DS_R"};
char LIST_LS_NAMES[TOTAL_LS][8] = {"LS_1"};
char LIST_MOTOR_NAMES[TOTAL_MOTOR][8] = {"DC_FL", "DC_FR", "DC_BL", "DC_BR"};
char LIST_LED_NAMES[TOTAL_LED][8] = {};

// Hardware Values

double LIST_DS_VALUES[2];
double LIST_LS_VALUES[1];
int LIST_MOTOR_VALUES[0];
int LIST_LED_VALUES[0];

// --------------------------------------------------
// SUPERVISOR
// --------------------------------------------------

char LIST_ROBOTS[SWARM_WIDTH][8] = {"BB_1", "BB_2"};

// --------------------------------------------------
// FUNDEMENTAL
// --------------------------------------------------

double SPEED;
int STEP;

// --------------------------------------------------
// DECLARATIONS
// --------------------------------------------------

// Fundemental

void init();
void update();

// Framework

void INIT();
void UPDATE();

