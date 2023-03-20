#pragma once
#include "math.h"

namespace Jath{
  class PID{
    public:
      PID(){}
      PID(double kp, double ki, double kd): m_kp(kp), m_ki(kd), m_kd(kd){}

      void clear(){
        m_error = 0;
        m_prevError = 0;
        m_derivative = 0;
        m_maxDerivative = 0;
        m_integral = 0;
        m_output = 0;
      }

      void setConstants(double kp, double ki, double kd){
        m_kp= kp;
        m_ki= ki;
        m_kd= kd;
      }

      void setIntegralZone(double min){
        m_integralZone = min;
      }
      
      double calculateValue(double target, double currentValue){
        
        m_error = target - currentValue;

        m_derivative = m_prevError - m_error; 
        if (fabs(m_derivative) > m_maxDerivative){
          m_maxDerivative = fabs(m_derivative);
        }

        if(fabs(m_error) < m_integralZone){
          m_integral += m_error;   
        }else {
          m_integral = 0;
        }
        if ((m_error > 0 && m_prevError < 0) || (m_error < 0 && m_prevError > 0)){
          m_integral = 0; 
        }

        m_output = (m_kp * m_error) + (m_kd * m_derivative) + (m_ki * m_integral);

        m_prevError = m_error;      
        return m_output;
      }

    private:

      double m_error{0};
      double m_prevError{0};

      double m_derivative{0};
      double m_maxDerivative{0};

      double m_integral{0};
      double m_integralZone{0};

      double m_output{0};

      double m_kp{0};
      double m_ki{0};
      double m_kd{0};

  };
}