#pragma once
#include "v5.h"
#include "Drive.h"

namespace Jath{

  class HDrive : public Drive{
    public:
      HDrive(
        vex::motor_group Left, vex::motor_group Right, vex::motor Strafe
      );

      void update() override;

      vex::motor_group m_left;
      vex::motor_group m_right;
      vex::motor m_strafe;
    private:
    
  };
}