#include "TankDrive.h"

namespace Jath{

  TankDrive::TankDrive(
    vex::motor_group Left, vex::motor_group Right
  ):
    m_left(Left),
    m_right(Right)
  {
    m_driveType = DriveType::TankDrive;
  };

  void TankDrive::update(){
    m_left.spin(vex::fwd, (  (m_cmdY * m_yScale) + (m_cmdRot * m_rotScale)), vex::pct);
    m_right.spin(vex::fwd, (-(m_cmdY * m_yScale) + (m_cmdRot * m_rotScale)), vex::pct);
  }
}