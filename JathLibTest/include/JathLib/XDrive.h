#pragma once
#include "vex.h"
#include "Drive.h"

namespace Jath{

  class XDrive : public Drive{
    public:
      XDrive(
        vex::motor LF, vex::motor LB,
        vex::motor RF, vex::motor RB
      );

      void update() override;

      vex::motor m_LF;
      vex::motor m_LB;
      vex::motor m_RF;
      vex::motor m_RB;
    private:
    
  };
}