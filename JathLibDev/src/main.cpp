/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\jatha                                            */
/*    Created:      Mon Mar 20 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

#include "Jathlib/Jathlib.h"

Jath::JathController testController(&cont,&contS);


Jath::RotationSensor testRot(vex::PORT14);
Jath::PotV2 testPot(Brain.ThreeWirePort.A);
Jath::Encoder testEncoder = Jath::Encoder(Brain.ThreeWirePort.C);

Jath::JathMotor test = Jath::JathMotor("Logs/AngleTestMotor",vex::motor(vex::PORT2,false))
  // .withSensor(&testRot)
  .withConstants(1, 0, 0)
  .withControlMode(Jath::JathMotor::ControlMode::Angle)
  .withFollower(vex::motor(vex::PORT3));


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  vex::task t1(Jath::logAllMotorsTask);

  while(true){
    if(testController.getInputPressed(Jath::JathController::buttons::pA)){
      test.set(100);
    }
    if(testController.getInput(Jath::JathController::buttons::pA) && test.getOutput() < 20){
      test.set(50);
    }
    if(testController.getInputReleased(Jath::JathController::buttons::pA)){
      test.set(0);
    }

    // Brain.Screen.setCursor(1, 1);
    // Brain.Screen.print("position %f", test.get() - testRot.getAngle()) ; //Jath::JathMotor::JathMotors[0]->m_sensor->getAngle());
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("Num Motors: %d", Jath::JathMotor::JathMotors.size());
    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print("Motor 0: %f", Jath::JathMotor::JathMotors[0]->getLeader()->position(vex::degrees));
    Brain.Screen.setCursor(4, 1);
    Brain.Screen.print("Motor 1: %f", Jath::JathMotor::JathMotors[1]->position(vex::degrees));

    Jath::updateAllMotors();
    
    vex::wait(24, vex::msec);
  }
  
}
