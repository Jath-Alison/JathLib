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


Jath::RotationSensor testRot(vex::PORT8);
Jath::PotV2 testPot(Brain.ThreeWirePort.A);
Jath::Encoder testEncoder = Jath::Encoder(Brain.ThreeWirePort.C);

Jath::JathMotor test = Jath::JathMotor("Logs/AngleTestMotor",vex::motor(vex::PORT2,false))
  .withSensor(&testRot)
  .withConstants(1, 0, 0)
  .withControlMode(Jath::JathMotor::ControlMode::Angle);

Jath::JathMotor follower = Jath::JathMotor("Logs/FollowerMotor",vex::motor(vex::PORT8))
  .withControlMode(Jath::JathMotor::ControlMode::Follower)
  .withLeader(&test);


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  vex::task t1 = vex::task(Jath::logAllMotorsTask);

  while(true){

    if(Brain.Screen.pressing()){
      test.set(0);//
    }else {
      test.set(180);
    }

    // Brain.Screen.setCursor(1, 1);
    // Brain.Screen.print("position %f", test.get() - testRot.getAngle()) ; //Jath::JathMotor::JathMotors[0]->m_sensor->getAngle());
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("Angle: %f", testRot.getAngle());
    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print("Angle to 180: %f", Jath::angleTo180Range(testRot.getAngle()) );
    Brain.Screen.setCursor(4, 1);
    Brain.Screen.print("Shortest angle: %f", Jath::bestTurnPath( Jath::angleTo180Range(testRot.getAngle())  ));
    Brain.Screen.setCursor(5, 1);
    Brain.Screen.print("act output: %f", test.getOutput());

    Jath::updateAllMotors();
    
    vex::wait(24, vex::msec);
  }
  
}
