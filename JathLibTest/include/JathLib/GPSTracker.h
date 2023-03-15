#pragma once
#include "vex.h"
#include "Tracker.h"
#include "MathUtils.h"

namespace Jath{

  class GPSTracker : public Tracker {
    public:

      GPSTracker(vex::gps GPS);

      void track() override;

      vex::gps m_gps;

  };
}