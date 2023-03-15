#include "GPSTracker.h"

namespace Jath{

  GPSTracker::GPSTracker(vex::gps GPS):
    m_gps(GPS)
  {}

  void GPSTracker::track(){
    m_x = m_gps.xPosition();
    m_y = m_gps.yPosition();
    m_rot = m_gps.yaw();
  }
}