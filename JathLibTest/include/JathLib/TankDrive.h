#pragma once
#include "vex.h"
#include "Drive.h"

namespace Jath{

  class TankDrive : public Drive{
    public:
      TankDrive(
        vex::motor_group Left, vex::motor_group Right
      );

      void update() override;

      vex::motor_group m_left;
      vex::motor_group m_right;
    private:
    
  };
}