#pragma once

#include "vex.h"
#include "PID.h"
#include "MathUtils.h"

namespace Jath{
    
  class CustomMotor : public vex::motor{
    public:

      enum ControlMode{
        DutyCycle,
        Position,
        Angle,
        Velocity,
        Follower,
        None
      };

      CustomMotor(vex::motor mot, vex::rotation* rot): motor(mot), m_rot(rot){
        m_rot->setPosition(0, vex::degrees);
      }

      ControlMode getControlMode(){
        return m_controlMode;
      }
      void setControlMode(ControlMode mode){

        m_controlMode = mode;
      }

      double get(){
        return m_cmd;
      }

      double getOutput(){
        return m_output;
      }

      void set(double input){
        m_cmd = input;
      }

      void update(){
        switch(m_controlMode){
          case DutyCycle:
            m_output = m_cmd * 12/100.f;
            spin(vex::fwd, m_output, vex::volt);
            break;
          case Position:
            m_output = m_pid.calculateValue(m_cmd, m_rot->position(vex::degrees)) * 12/100.f;
            spin(vex::fwd, m_output, vex::volt);
            break;
          case Angle:
            m_output = m_pid.calculateValue(m_cmd, Jath::angleTo180Range(m_rot->angle()) ) * 12/100.f;
            spin(vex::fwd, m_output, vex::volt);
            break;
          case Velocity:
            m_output += m_pid.calculateValue(m_cmd, m_rot->velocity(vex::rpm)) * 12/100.f;
            spin(vex::fwd, m_output, vex::volt);
            break;
          case Follower:
            m_cmd = m_followMotor->voltage();
            m_output = m_cmd;
            spin(vex::fwd, m_output, vex::volt);
            break;
          case None:

            break;
        }
      }

      Jath::PID m_pid;
    private:

      ControlMode m_controlMode{None};

      vex::rotation* m_rot{nullptr};
      vex::motor* m_followMotor{nullptr};

      double m_cmd{0};
      double m_output{0};
  };
}