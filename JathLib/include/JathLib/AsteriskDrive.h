#pragma once
#include "vex.h"
#include "subsystems/Drive.h"

namespace Jath{

  class AsteriskDrive : public Drive{
    public:
      AsteriskDrive(
        vex::motor LF, vex::motor LM, vex::motor LB,
        vex::motor RF, vex::motor RM, vex::motor RB
      );

      void update() override;

      vex::motor m_LF;
      vex::motor m_LM;
      vex::motor m_LB;
      vex::motor m_RF;
      vex::motor m_RM;
      vex::motor m_RB;
    private:
    
  };
}