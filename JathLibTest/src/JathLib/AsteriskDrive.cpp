#include "JathLib/AsteriskDrive.h"

namespace Jath{

  AsteriskDrive::AsteriskDrive(
    vex::motor LF, vex::motor LM, vex::motor LB,
    vex::motor RF, vex::motor RM, vex::motor RB
  ):
    m_LF(LF),
    m_LM(LM),
    m_LB(LB),
    m_RF(RF),
    m_RM(RM),
    m_RB(RB)
  {
    m_driveType = DriveType::AsteriskDrive;
  };

  void AsteriskDrive::update(){
    m_LF.spin(vex::fwd, ( (m_cmdX * m_xScale) + (m_cmdY * m_yScale) + (m_cmdRot * m_rotScale)), vex::pct);
    m_LM.spin(vex::fwd, (                     + (m_cmdY * m_yScale) + (m_cmdRot * m_rotScale)), vex::pct);
    m_LB.spin(vex::fwd, (-(m_cmdX * m_xScale) + (m_cmdY * m_yScale) + (m_cmdRot * m_rotScale)), vex::pct);

    m_RF.spin(vex::fwd, ( (m_cmdX * m_xScale) - (m_cmdY * m_yScale) + (m_cmdRot * m_rotScale)), vex::pct);
    m_RM.spin(vex::fwd, (                     - (m_cmdY * m_yScale) + (m_cmdRot * m_rotScale)), vex::pct);
    m_RB.spin(vex::fwd, (-(m_cmdX * m_xScale) - (m_cmdY * m_yScale) + (m_cmdRot * m_rotScale)), vex::pct);
  }
}