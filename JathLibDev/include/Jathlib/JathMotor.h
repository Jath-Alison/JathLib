#pragma once

#include "vex.h"
#include "Jathlib/PID.h"
#include "Jathlib/Logger.h"
#include "Jathlib/MathUtils.h"
#include <vector>
#include <string>
#include <map>
#include <memory>

namespace Jath{
  class JathMotor : public vex::motor{
    public:

      enum ControlMode{
        DutyCycle,
        Position,
        Velocity,
        Follower,
        None
      };

      JathMotor(const JathMotor& mot): 
        vex::motor(mot), 
        m_logFile(mot.m_logFile),
        m_followMotor(mot.m_followMotor),
        m_pid(mot.m_pid),
        m_cmd(mot.m_cmd),m_output(mot.m_output),
        m_controlMode(mot.m_controlMode)
      {
        
        m_logFile->addLogItem("time", [this]{ return Jath::timePassed(); });
        m_logFile->addLogItem("cmdType", [this]{return getControlMode(); });
        m_logFile->addLogItem("cmd", [this]{return get(); });
        m_logFile->addLogItem("velocity", [this]{ return velocity(vex::rpm); });
        m_logFile->addLogItem("torque", [this]{ return torque(); });
        m_logFile->addLogItem("temprature", [this]{return temperature(); });
        m_logFile->addLogItem("output%", [this]{return getOutput()*100/12.f; });
        m_logFile->addLogItem("pos", [this]{ return position(vex::degrees); });
        
        JathMotors.push_back(this);
      }

      JathMotor(std::string name,vex::motor mot): motor(mot), m_logFile(nullptr)
      {
        m_logFile = std::make_shared<Logger>(name);
        JathMotors.push_back(this);
      }

      ~JathMotor(){
        for(int i = 0;i<JathMotors.size();i++){
          if(JathMotors[i] == this){
            JathMotors.erase(JathMotors.begin() + i);
          }
        }
        m_logFile = nullptr;
      }

      JathMotor& withConstants(double p, double i, double d){
        m_pid.setConstants(p, i, d);
        return *this;
      }

      JathMotor& withControlMode(ControlMode mode){
        m_controlMode = mode;
        return *this;
      }

      JathMotor& withLeader(vex::motor* leader){
        m_followMotor = leader;
        return *this;
      }

      ControlMode getControlMode(){
        return m_controlMode;
      }
      std::string getControlModeStr(){
        return ModeToString[m_controlMode];
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
            }
            m_output = m_cmd;
            spin(vex::fwd, m_output, vex::volt);
            break;
          case None:
            break;
        }
      }

      static inline std::vector<JathMotor*> JathMotors;

      Jath::PID m_pid;
    private:
      std::shared_ptr<Jath::Logger> m_logFile;
      friend void logAllMotorHeaders();
      friend void logAllMotors();

      std::map<ControlMode, std::string> ModeToString{
        {DutyCycle, "DutyCycle"},
        {Position, "Position"},
        {Velocity, "Velocity"},
        {Follower, "Follower"},
        {None, "None"},
      };

      ControlMode m_controlMode{None};

      vex::motor* m_followMotor{nullptr};

      double m_cmd{0};
      double m_output{0};
  };

  inline void logAllMotorHeaders(){
    for(int i = 0; i < JathMotor::JathMotors.size(); i++){
      JathMotor::JathMotors[i]->m_logFile->logHeader();
    }
  }

  inline void logAllMotors(){
    for(int i = 0; i < JathMotor::JathMotors.size(); i++){
      JathMotor::JathMotors[i]->m_logFile->log();
    }
  }

  inline int logAllMotorsTask(){
    logAllMotorHeaders();
    while(true){
      logAllMotors();
      vex::wait(25, vex::msec);
    }
    return 0;
  }

  inline void updateAllMotors(){
    for(int i = 0; i<JathMotor::JathMotors.size(); i++){
      JathMotor::JathMotors[i]->update();
    }
  }


}