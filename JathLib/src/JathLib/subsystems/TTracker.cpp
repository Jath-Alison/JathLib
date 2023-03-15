#include "TTracker.h"

namespace Jath{

TTracker::TTracker(vex::inertial inert, vex::rotation xRot, vex::rotation yRot):
  m_inert(inert),
  m_rotX(xRot),
  m_rotY(yRot)  
{
  m_rotX.resetPosition();
  m_rotY.resetPosition();
}

TTracker::TTracker(vex::inertial inert, vex::rotation xRot, vex::rotation yRot, double xOffset, double yOffset, double wheelSize):
  m_xOffset(xOffset),
  m_yOffset(yOffset),
  m_wheelSize(wheelSize),
  m_inert(inert),
  m_rotX(xRot),
  m_rotY(yRot)
{
  m_rotX.resetPosition();
  m_rotY.resetPosition();
}

void TTracker::track(){

  m_rot = angleTo180Range(m_inert.rotation(vex::degrees));

  double delRot = m_prevRot - m_rot;

  double delX = rad(2.75 / 2 * (m_prevX - m_rotX.position(vex::degrees)) - (m_xOffset) * delRot * 1);
  double delY = rad(2.75 / 2 * (m_prevY - m_rotY.position(vex::degrees)) + (m_yOffset) *  delRot   * 1);

  m_x += (
    delX*cos(rad(m_rot))+
    delY*sin(rad(m_rot))
  );
  m_y += (
    -delX*sin(rad(m_rot))+
    delY*cos(rad(m_rot))
  ); 

  m_prevX = m_rotX.position(vex::degrees);
  m_prevY = m_rotY.position(vex::degrees);
  m_prevRot = m_rot;
}
}