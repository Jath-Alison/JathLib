#pragma once
#include <cmath>

namespace Jath{

  const double PI = 3.1415;

  template<typename T>
  inline T abs(T input){
    if(input > 0){
      return input;
    }else if(input < 0) {
      return -input;
    }else {
      return 0;
    }
  }


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

  inline double bestTurnPath(double degree){

    double opDegree;
  
    if(degree < 0){
      opDegree = 360 + degree;  
    } else {
      opDegree = degree - 360;
    }
    if(abs(degree) > abs(opDegree)){
      return opDegree;
    }else if (abs(degree) < abs(opDegree)) {
      return degree;
    }
    return degree;
  }

  double oppositeAngle(double degree){
    if(degree > 0){
      return degree - 180;
    }else {
      return degree + 180;
    }
  }

}