#include "JathLib/SmartDrive.h"
#include "math.h"

namespace Jath{

  SmartDrive::SmartDrive(TTracker* tracker, Drive* holodrive):
    m_tracker(tracker),
    m_drive(holodrive)
    {}

  void SmartDrive::cartesianControl(double cmdX, double cmdY, double cmdRot){
    double angle = rad(m_tracker->m_rot);
    double newCmdX =  cmdX*cosf(angle) - cmdY*sinf(angle);
    double newCmdY =  cmdX*sinf(angle) + cmdY*cosf(angle);
    m_drive->arcade(newCmdX, newCmdY, cmdRot);
  }
  void SmartDrive::cartesianArcade(double cmdX, double cmdY, double cmdRot){
    m_mode = CONTROL;
    m_cmdX = cmdX;
    m_cmdY = cmdY;  
    m_cmdRot = cmdRot;
  }
      
  void SmartDrive::translateRobot(double x, double y){
    m_mode = AUTO;
    m_targetX = m_tracker->m_x + x;
    m_targetY = m_tracker->m_y + y;
  }

  void SmartDrive::translateField(double x, double y){
    m_mode = AUTO;
    m_targetX = x;
    m_targetY = y;
  }

  void SmartDrive::update(){

    double xDist;
    double yDist;
    switch(m_rotMode){
      case FR_LOCKED:
        m_targetRot = rotAngle;
        break;
      case LOCKED_TO_POINT:
        xDist = rotPoint.x - m_tracker->m_x;
        yDist = rotPoint.y - m_tracker->m_y;
        if(xDist == 0 && yDist == 0){
          m_targetRot = 0;
          break;
        }
        if(yDist < 0){
          m_targetRot = degreees( -atan(yDist/xDist)) - 90 ;
        }else{
          m_targetRot = degreees ( -atan(yDist/xDist) )+ 90 ;
        }
        if(yDist*xDist<0){
          m_targetRot += 180;
        }
        break;
      case UNLOCKED:
        m_targetRot = 0;
        break;
    }

    switch(m_mode){
      case CONTROL:
          
        break;
      case AUTO:
        double errorX = m_targetX - m_tracker->m_x;
        double errorY = m_targetY - m_tracker->m_y;
        double errorRot = m_targetRot - m_tracker->m_rot;
        m_cmdX = errorX * kp;
        m_cmdY = errorY * kp;
        m_cmdRot = errorRot * kp/4;

        if(m_rotMode == UNLOCKED){
          m_cmdRot = 0;
        }
        break;
    } 
    
    cartesianControl(m_cmdX, m_cmdY, m_cmdRot);
  }

  void SmartDrive::setRot(double angle){
    m_rotMode = FR_LOCKED;
    rotAngle = angle;
  }
  void SmartDrive::setRot(double x, double y){
    m_rotMode = LOCKED_TO_POINT;
    rotPoint = {x,y};
  }
  void SmartDrive::setRot(){
    m_rotMode = UNLOCKED;
  }

  bool SmartDrive::atTarget(double posRange, double angleRange){
    double errorX = m_targetX - m_tracker->m_x;
    double errorY = m_targetY - m_tracker->m_y;
    double errorRot = m_targetRot - m_tracker->m_rot;
    return (fabs(errorX) < posRange) && (fabs(errorY) < posRange) && (fabs(errorRot) < angleRange);
  }
}