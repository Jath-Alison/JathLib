#include "vex.h"
#include "JathLib/JathLib.h"

// A global instance of brain used for printing to the V5 brain screen
vex::brain Brain;

vex::controller cont(vex::primary);

vex::rotation testRot(vex::PORT4);
vex::motor tempMotor(vex::PORT3);
Jath::CustomMotor testMotor(tempMotor, &testRot);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}