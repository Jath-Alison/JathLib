#pragma once
#include <cmath>

namespace Jath{

const double PI = 3.1415;

  inline double rad(double degree){
    return PI/180 * degree;
  }

  inline double degreees(double radians){
    return 180/PI * radians;
  }

  inline double angleTo180Range(double angle) {
    while(!(angle >= -180 && angle < 180)) {
      if( angle < -180 ) { angle += 360; }
      if(angle >= 180) { angle -= 360; }
    }
    return(angle);
  }

}