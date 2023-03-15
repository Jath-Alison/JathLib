#include "XDrive.h"

namespace Jath{

  XDrive::XDrive(
    vex::motor LF, vex::motor LB,
    vex::motor RF, vex::motor RB
  ):
    m_LF(LF),
    m_LB(LB),
    m_RF(RF),
    m_RB(RB)
  {
    m_driveType = DriveType::XDrive;
  };

  void XDrive::update(){

    m_LF.spin(vex::fwd, ( (m_cmdX * m_xScale) + (m_cmdY * m_yScale) + (m_cmdRot * m_rotScale)), vex::pct);
    m_LB.spin(vex::fwd, (-(m_cmdX * m_xScale) + (m_cmdY * m_yScale) + (m_cmdRot * m_rotScale)), vex::pct);

    m_RF.spin(vex::fwd, (-(m_cmdX * m_xScale) - (m_cmdY * m_yScale) + (m_cmdRot * m_rotScale)), vex::pct);
    m_RB.spin(vex::fwd, ( (m_cmdX * m_xScale) - (m_cmdY * m_yScale) + (m_cmdRot * m_rotScale)), vex::pct);
  }
}