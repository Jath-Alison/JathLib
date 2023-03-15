#pragma once
#include "vex.h"
#include "MathUtils.h"

namespace Jath{

  class Tracker {
    public:

      virtual void track() = 0;

      double m_x{0};
      double m_y{0};
      double m_rot{0};

  };
}