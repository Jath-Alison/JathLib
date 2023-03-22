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


Jath::RotationSensor testRot(vex::PORT10);
Jath::Encoder testEncoder = Jath::Encoder(Brain.ThreeWirePort.C);

Jath::JathMotor test = Jath::JathMotor("Logs/TestMotor",vex::motor(vex::PORT2))
  .withConstants(1, 0.1, 0.2)
  .withControlMode(Jath::JathMotor::ControlMode::Position);

Jath::JathMotor follower = Jath::JathMotor("Logs/FollowerMotor",vex::motor(vex::PORT8))
  .withControlMode(Jath::JathMotor::ControlMode::Follower)
  .withLeader(&test);


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  vex::task t1 = vex::task(Jath::logAllMotorsTask);


  while(true){

    if(Brain.Screen.pressing()){
      test.set(100);
    }else {
      test.set(0);
    }

    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Number of motors %d", Jath::JathMotor::JathMotors.size());

    Jath::updateAllMotors();
    
    vex::wait(25, vex::msec);
  }
  
}
