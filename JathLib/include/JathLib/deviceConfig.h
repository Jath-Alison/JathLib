#pragma once
#include "PID.h"
#include "subsystems/TTracker.h"
#include "subsystems/GPSTracker.h"
#include "subsystems/AsteriskDrive.h"
#include "subsystems/SmartDrive.h"

extern vex::brain Brain;
extern vex::controller controlP;
extern vex::controller controlS;

extern vex::controller control;

extern vex::motor frontL;
extern vex::motor frontR;
extern vex::motor midL;
extern vex::motor midR;
extern vex::motor backL;
extern vex::motor backR;

extern vex::motor intake;
extern vex::motor flywheel;
extern Jath::PID flywheelPID;

//Pnuematics:
extern vex::pneumatics angler;

//sensors:
extern vex::inertial gero;
extern vex::rotation evert;
extern vex::rotation eside;
extern vex::gps GPS;

extern Jath::TTracker testTracker;
extern Jath::AsteriskDrive testAsterisk;
extern Jath::SmartDrive testDrive;
extern Jath::GPSTracker testGPS;