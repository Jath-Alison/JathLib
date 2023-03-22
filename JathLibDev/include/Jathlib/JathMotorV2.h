#pragma once

#include "vex.h"
#include "Jathlib/PID.h"
#include "Jathlib/Logger.h"
#include "Jathlib/RotarySensor.h"
#include "Jathlib/MathUtils.h"
#include <vector>
#include <string>
#include <map>
#include <memory>

namespace Jath{

  class JathMotorV2 : public vex::motor{
    public:

      enum ControlMode{
        DutyCycle,
        Position,
        Velocity,
        Follower,
        None
      };

      JathMotorV2(vex::motor mot): motor(mot){      
        JathMotorV2s.push_back(this);
      }

      void addSensor(Sensor* sens){
        m_sensor = sens;
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

      void setLeader(vex::motor* leader){
        m_followMotor = leader;
      }

      void update(){
        
        // switch(m_sensor->getType()){
        //   case Sensor::Type::RotationSensor:
        //     RotationSensor* rot = dynamic_cast<RotationSensor*>(m_sensor);
        //     break;          
        //   case Sensor::Type::Encoder:
        //     Encoder* enco = dynamic_cast<Encoder*>(m_sensor);
        //     break;          
        // }
        switch(m_controlMode){
          case DutyCycle:
            m_output = m_cmd * 12/100.f;
            spin(vex::fwd, m_output, vex::volt);
            break;
          case Position:
            m_output = m_pid.calculateValue(m_cmd, position(vex::degrees)) * 12/100.f;
            spin(vex::fwd, m_output, vex::volt);
            break;
          case Velocity:
            m_output += m_pid.calculateValue(m_cmd, velocity(vex::rpm)) * 12/100.f;
            spin(vex::fwd, m_output, vex::volt);
            break;
          case Follower:
            if(m_followMotor){
              m_cmd = m_followMotor->voltage();
            }else {
              m_cmd = 0;
            }
            m_output = m_cmd;
            spin(vex::fwd, m_output, vex::volt);
            break;
          case None:

            break;
        }
      }

      Jath::PID m_pid;
      static inline std::vector<JathMotorV2*> JathMotorV2s;

    private:

      std::map<ControlMode, std::string> ModeToString{
        {DutyCycle, "DutyCycle"},
        {Position, "Position"},
        {Velocity, "Velocity"},
        {Follower, "Follower"},
        {None, "None"},
      };

      ControlMode m_controlMode{None};
      Sensor::Type m_sensorType{Sensor::Type::Null};

      vex::motor* m_followMotor{nullptr};
      Sensor* m_sensor{nullptr};

      double m_cmd{0};
      double m_output{0};
  };

  inline void updateAllMotorss(){
    for(int i = 0; i<JathMotorV2::JathMotorV2s.size(); i++){
      JathMotorV2::JathMotorV2s[i]->update();
    }
  }
}