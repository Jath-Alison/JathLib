#pragma once
#include "Path.h" 
#include "Point.h"
#include "Macros.h"

std::vector<Jath::Macro> first = {face_45Macro, intakeInMacro};
std::vector<Jath::Macro> second = {flywheelTo8Macro, faceRedMacro};
std::vector<Jath::Macro> third = {angleUpMacro, wait1Macro};
std::vector<Jath::Macro> fourth = {intakeOutMacro, wait1Macro};

std::vector<Jath::Point> points{
  Jath::Point(0, 0),
  Jath::Point(33, -9, first),
  Jath::Point(-25, 48, second),
  Jath::Point(10, 56, third),
  Jath::Point(16, 56, fourth)
  };
//Path testPath(points);
Jath::Path testPath;

Jath::Point* lookPoint = nullptr;
Jath::Point* closestOriginalPoint = nullptr;