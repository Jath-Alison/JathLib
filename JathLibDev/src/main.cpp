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

  // vex::task t1 = vex::task(Jath::logAllMotorsTask);

  Jath::Logger testLogger("Logs/TestLogger");

  testLogger.addLogItem("time", []{ return Jath::timePassed(); });
  testLogger.addLogItem("cmdType", []{return test.get(); });

  testLogger.logHeader();

  while(true){

    if(cont.ButtonA.pressing()){
      test.set(100);
    }else {
      test.set(0);
    }

    testLogger.log();

    Jath::updateAllMotors();
    
    vex::wait(25, vex::msec);
  }
  
}
