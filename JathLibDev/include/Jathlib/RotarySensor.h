#pragma once

#include "vex.h"

namespace Jath{

  class Sensor{
    public:
      enum Type{
        RotationSensor,
        Encoder,
        Pot,
        PotV2,
        Null
      };
      Type getType(){return m_type;}
      //void setType(Type typ){ m_type = typ;}
      virtual double getPosition() {return 0;};
      virtual double getVelocity() {return 0;}; 
      virtual double getAngle() {return 0;};
    protected:
      Type m_type{Null};
  };

  class RotationSensor : public Sensor, public vex::rotation{
    public:
      RotationSensor(vex::rotation port) : vex::rotation(port) {
        m_type = Type::RotationSensor;
      };
      double getAngle() override {return angle();}
      double getPosition() override {return position(vex::degrees);}
      double getVelocity() override {return velocity(vex::rpm);}
  };

  class Encoder : public Sensor, public vex::encoder{
    public:
      Encoder(vex::triport::port& t) : vex::encoder(t){
        m_type = Type::Encoder;
      }; 
      double getPosition() override {return position(vex::degrees);}
      double getVelocity() override {return velocity(vex::rpm);}
  };

  class Pot : public Sensor, public vex::pot{
    public:
      Pot(vex::triport::port& t) : vex::pot(t){
        m_type = Type::Pot;
      }; 
      double getPosition() override {return angle(vex::degrees);}
      double getAngle() override {return angle(vex::degrees);};
  };  
  class PotV2 : public Sensor, public vex::potV2{
    public:
      PotV2(vex::triport::port& t) : vex::potV2(t){
        m_type = Type::PotV2;
      }; 
      double getPosition() override {return angle(vex::degrees);}
      double getAngle() override {return angle(vex::degrees);};
  };  
}