#pragma once
#include "v5.h"
#include "Drive.h"
#include "TTracker.h"

namespace Jath{

  class SmarterDrive{
    public:

      SmarterDrive(TTracker* tracker, Drive* holodrive);

      void cartesianArcade(double x, double y, double rot);
      void cartesianControl(double x, double y, double rot);
      
      void translateRobot(double x, double y);
      void translateField(double x, double y);

      void setRot(double angle);
      void setRot(double x, double y);
      void setRot();

      void update();

      double getTargetRot(){return m_targetRot;}

      bool atTarget(double posRange, double angleRange);

      double kp;

    private:

      enum modes{
        CONTROL,
        AUTO
      };
      modes m_mode;

      double rotAngle;
      struct{ double x; double y;} rotPoint;

      enum RotModes{
        //CONTROL,
        FR_LOCKED,
        LOCKED_TO_POINT,
        UNLOCKED
      };
      RotModes m_rotMode;
      

      double m_targetX{0};    
      double m_targetY{0};
      double m_targetRot{0};


      double m_cmdX{0};
      double m_cmdY{0};
      double m_cmdRot{0};
      

      TTracker* m_tracker;
      Drive* m_drive;
  };

}