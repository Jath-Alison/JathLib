#pragma once

#include "deviceConfig.h"
#include "Auton/Macro.h"

void wait1(){
  wait(1, vex::seconds);
}
Jath::MacroFunc wait1Func("wait1", wait1);
Jath::Macro wait1Macro("wait1");

void faceRed(){
  testDrive.setRot(54,54);
}
Jath::MacroFunc faceRedFunc("faceRed", faceRed);
Jath::Macro faceRedMacro("faceRed");

void faceBlue(){
  testDrive.setRot(-54,-54);
}
Jath::MacroFunc faceBlueFunc("faceBlue", faceBlue);
Jath::Macro faceBlueMacro("faceBlue");

void face0(){
  testDrive.setRot(0);
}
Jath::MacroFunc face0Func("face0", face0);
Jath::Macro face0Macro("face0");

void face45(){
  testDrive.setRot(45);
}
Jath::MacroFunc face45Func("face45", face45);
Jath::Macro face45Macro("face45");

void face90(){
  testDrive.setRot(90);
}
Jath::MacroFunc face90Func("face90", face90);
Jath::Macro face90Macro("face90");

void face135(){
  testDrive.setRot(135);
}
Jath::MacroFunc face135Func("face135", face135);
Jath::Macro face135Macro("face135");

void face180(){
  testDrive.setRot(180);
}
Jath::MacroFunc face180Func("face180", face180);
Jath::Macro face180Macro("face180");

void face_45(){
  testDrive.setRot(-45);
}
Jath::MacroFunc face_45Func("face_45", face_45);
Jath::Macro face_45Macro("face_45");

void face_90(){
  testDrive.setRot(-90);
}
Jath::MacroFunc face_90Func("face_90", face_90);
Jath::Macro face_90Macro("face_90");

void face_135(){
  testDrive.setRot(-135);
}
Jath::MacroFunc face_135Func("face_135", face_135);
Jath::Macro face_135Macro("face_135");

void flywheelTo8(){
  flywheel.spin(vex::fwd,8,vex::volt);
}
Jath::MacroFunc flywheelTo8Func("flywheelTo8", flywheelTo8);
Jath::Macro flywheelTo8Macro("flywheelTo8");

void intakeIn(){
  intake.spin(vex::fwd,8,vex::volt);
}
Jath::MacroFunc intakeInFunc("intakeIn", intakeIn);
Jath::Macro intakeInMacro("intakeIn");

void intakeOut(){
  intake.spin(vex::fwd,-4,vex::volt);
}
Jath::MacroFunc intakeOutFunc("intakeOut", intakeOut);
Jath::Macro intakeOutMacro("intakeOut");

void intakeStop(){
  intake.spin(vex::fwd,0,vex::volt);
}
Jath::MacroFunc intakeStopFunc("intakeStop", intakeStop);
Jath::Macro intakeStopMacro("intakeStop");

void angleUp(){
  angler.open();
}
Jath::MacroFunc angleUpFunc("angleUp", angleUp);
Jath::Macro angleUpMacro("angleUp");

void angleDown(){
  angler.close();
}
Jath::MacroFunc angleDownFunc("angleDown", angleDown);
Jath::Macro angleDownMacro("angleDown");

std::vector<Jath::MacroFunc> macroFuncs{
  faceRedFunc,
  faceBlueFunc,
  face0Func,
  face45Func,
  face90Func,
  face135Func,
  face180Func,
  face_45Func,
  face_90Func,
  face_135Func,
  flywheelTo8Func,
  intakeInFunc,
  intakeOutFunc,
  intakeStopFunc,
  angleUpFunc,
  angleDownFunc,
};