#pragma once

#include "vex.h"
#include "Jathlib/PID.h"
#include "Jathlib/Logger.h"
#include "Jathlib/MathUtils.h"
#include "Jathlib/RotarySensor.h"
#include <vector>
#include <string>
#include <cstring>
#include <map>
#include <memory>

namespace Jath{
  class JathMotor : public vex::motor{
    public:

      enum ControlMode{
        DutyCycle,
        Position,
        Angle,
        Velocity,
        Follower,
        None
      };

      JathMotor(const JathMotor& mot): 
        vex::motor(mot), 
        m_logFile(mot.m_logFile),
        m_sensor(mot.m_sensor),
        m_followMotor(mot.m_followMotor),
        m_pid(mot.m_pid),
        m_cmd(mot.m_cmd),m_output(mot.m_output),
        m_controlMode(mot.m_controlMode),
        m_followingMotors(mot.m_followingMotors)
      {

        for(int i = 0;i<m_followingMotors.size();i++){
          m_followingMotors[i]->setLeader(this);
        }
        
        m_logFile->addLogItemD("time", [this]{ return Jath::timePassed(); });
        m_logFile->addLogItemS("cmdType", [this]{return ModeToString[getControlMode()]; });
        m_logFile->addLogItemD("cmd", [this]{return get(); });
        m_logFile->addLogItemD("velocity", [this]{ return velocity(vex::rpm); });
        m_logFile->addLogItemD("torque", [this]{ return torque(); });
        m_logFile->addLogItemD("temprature", [this]{return temperature(); });
        m_logFile->addLogItemD("output%", [this]{return getOutput()*100/12.f; });
        m_logFile->addLogItemD("pos", [this]{ return position(vex::degrees); });
        
        JathMotors.push_back(this);
      }

      JathMotor(std::string name,vex::motor mot): motor(mot), m_followMotor(nullptr), m_logFile(nullptr), m_sensor(nullptr)
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

      JathMotor& withSensor(Sensor* sensorPointer){
        m_sensor = sensorPointer;
        m_logFile->addLogItemD("sensorPos", [this]{return m_sensor->getPosition();});
        m_logFile->addLogItemD("sensorVelocity", [this]{return m_sensor->getVelocity();});
        m_logFile->addLogItemD("sensorAngle", [this]{ return m_sensor->getAngle();});
        
        return *this;
      }
      
      JathMotor& withConstants(double p, double i, double d){
        m_pid.setConstants(p, i, d);
        return *this;
      }

      JathMotor& withControlMode(ControlMode mode){
        m_controlMode = mode;
        return *this;
      }

      JathMotor& withLeader(JathMotor* leader){
        m_followMotor = leader;
        return *this;
      }
      JathMotor& withFollower(vex::motor mot){
        int count = ((int)JathMotors.size());
        char countStr[4] = "";
        sprintf(countStr, "%d",count);

        JathMotor* temp = new JathMotor (m_name + "follower" + countStr ,mot);
        temp->setControlMode(Follower);
        temp->setLeader(this);

        m_followingMotors.push_back(temp);

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
      void addFollower(vex::motor mot){
        int count = ((int)JathMotors.size());
        char countStr[4] = "";
        sprintf(countStr, "%d",count);

        JathMotor* temp = new JathMotor (m_name + "follower" + countStr ,mot);
        temp->setControlMode(Follower);
        temp->setLeader(this);

        m_followingMotors.push_back(temp);
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

      void setLeader(JathMotor* leader){
        m_followMotor = leader;
      }
      JathMotor* getLeader(){
        return m_followMotor;
      }

      void update(){

        double turnError = 0;

        switch(m_controlMode){
          case DutyCycle:
            m_output = m_cmd * 12/100.f;
            spin(vex::fwd, m_output, vex::volt);
            break;
          case Position:
            if(m_sensor){
              value = m_sensor->getPosition();
            }else {
              value = position(vex::degrees);
            }            
            m_output = m_pid.calculateValue(m_cmd, value) * 12/100.f;
            spin(vex::fwd, m_output, vex::volt);
            break;
          case Angle:
            if(m_sensor){
              value = m_sensor->getAngle();
              turnError = m_cmd - value;
              if(m_sensor->getType() != Sensor::Type::Pot && m_sensor->getType() != Sensor::Type::PotV2){
                turnError = bestTurnPath(turnError);
              }
            }else {
              value = angleTo180Range( position(vex::degrees) );
              turnError = bestTurnPath(m_cmd - value);
            }

            m_output = m_pid.calculateValue(turnError) * 12/100.f;

            spin(vex::fwd, m_output, vex::volt);
            break;
          case Velocity:
            if(m_sensor){
              value = m_sensor->getVelocity();
            }else {
              value = velocity(vex::rpm);
            }
              m_output += m_pid.calculateValue(m_cmd, value) * 12/100.f;
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

      double value = 0;
      Jath::PID m_pid;
      Jath::Sensor* m_sensor;
    private:
      std::shared_ptr<Jath::Logger> m_logFile;
      friend void logAllMotorHeaders();
      friend void logAllMotors();

      std::string m_name;

      std::map<ControlMode, std::string> ModeToString{
        {DutyCycle, "DutyCycle"},
        {Position, "Position"},
        {Angle, "Angle"},
        {Velocity, "Velocity"},
        {Follower, "Follower"},
        {None, "None"},
      };

      ControlMode m_controlMode{None};

      JathMotor* m_followMotor{nullptr};
      std::vector<JathMotor *> m_followingMotors;

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