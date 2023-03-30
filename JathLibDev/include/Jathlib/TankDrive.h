#pragma once
#include "vex.h"
#include "JathMotor.h"
#include "JathLib/Drive.h"

namespace Jath{

  class TankDrive : public Drive{
    public:
      TankDrive(std::string name, vex::motor Left, vex::motor Right):
        m_left(name + "LeftMotor",Left),
        m_right(name + "RightMotor",Right)
      {

        m_left.setControlMode(JathMotor::ControlMode::Velocity);
        m_right.setControlMode(JathMotor::ControlMode::Velocity);

        m_driveType = DriveType::TankDrive;
      };

      void update() override{
        m_left.set(  (m_cmdY * m_yScale) + (m_cmdRot * m_rotScale));
        m_right.set(-(m_cmdY * m_yScale) + (m_cmdRot * m_rotScale));
      }

      JathMotor m_left;
      JathMotor m_right;
    private:
    
  };
}
