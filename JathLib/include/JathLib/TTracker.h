#pragma once
#include "vex.h"
#include "Tracker.h"
#include "MathUtils.h"

namespace Jath{

  class TTracker : public Tracker {
    public:

      TTracker(vex::inertial inert, vex::rotation xRot, vex::rotation yRot);
      TTracker(vex::inertial inert, vex::rotation xRot, vex::rotation yRot, double xOffset, double yOffset, double wheelSize);

      void track() override;

      double m_xOffset{0};
      double m_yOffset{0};

      double m_wheelSize{2.75};

      vex::inertial m_inert;
      vex::rotation m_rotX;
      vex::rotation m_rotY;

    private:

      double m_prevRot{0};
      double m_prevX{0};
      double m_prevY{0};

  };

}