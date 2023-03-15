#include "JathLib/HDrive.h"

namespace Jath{

  HDrive::HDrive(
    vex::motor_group Left, vex::motor_group Right, vex::motor Strafe
  ):
    m_left(Left),
    m_right(Right),
    m_strafe(Strafe)
  {
    m_driveType = DriveType::HDrive;
  };

  void HDrive::update(){
    m_left.spin(vex::fwd, (  (m_cmdY * m_yScale) + (m_cmdRot * m_rotScale)), vex::pct);
    m_right.spin(vex::fwd, (-(m_cmdY * m_yScale) + (m_cmdRot * m_rotScale)), vex::pct);
    m_strafe.spin(vex::fwd, (m_cmdX * m_xScale), vex::pct);
  }
}