#pragma once
#include "vex.h"

namespace Jath{

  class Drive{
    public:

      enum DriveType{
        TankDrive,
        HDrive,
        XDrive,
        AsteriskDrive,      
      };

      void arcade(double x, double y, double rot){
        m_cmdX = x;
        m_cmdY = y;
        m_cmdRot = rot;
      };

      virtual void update() = 0;

      double m_cmdX{0};
      double m_cmdY{0};
      double m_cmdRot{0};

      void setScales(double x, double y, double rot){
        m_xScale = x; m_yScale = y; m_rotScale = rot;
      }
      double m_xScale{1};
      double m_yScale{1};
      double m_rotScale{1};

      DriveType m_driveType;

  };
}