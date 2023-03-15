#pragma once
#include "Vector2.h"
#include "Macro.h"

namespace Jath{

  struct Point{
    Point(Vector2 coord, std::vector<Macro> macs) : coords(coord), macros(macs){}
    Point(double x, double y, std::vector<Macro> macs) : coords(x,y), macros(macs){}
    Point(Vector2 coord) : coords(coord){}
    Point(double x, double y) : coords(x,y){}

    Vector2 coords{0,0};
    double distAlongPath{0};
    double maxVelocity{0};
    double targetRobotVel{0};
    double curveOfPath{0};
    std::vector<Macro> macros;
  };
}