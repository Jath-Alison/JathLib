#pragma once
#include "Path.h" 
#include "Point.h"
#include "Macros.h"

//create macro steps

std::vector<Jath::Point> points{
  Jath::Point(0, 0)
};

Jath::Point* lookPoint = nullptr;
Jath::Point* closestOriginalPoint = nullptr;