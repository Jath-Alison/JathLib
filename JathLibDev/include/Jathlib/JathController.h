#pragma once
#include "vex.h"
#include <map>
#include <vector>

namespace Jath{
  class JathController{
      public:
        enum buttons{
            pUp, pDown, pLeft, pRright,
            pA, pB, pX, pY,
            pLUp, pLDown, pRUp, pRDown,
            
            sUp, sDown, sLeft, sRright,
            sA, sB, sX, sY,
            sLUp, sLDown, sRUp, sRDown
        };

        JathController(vex::controller* primaryControllerPtr) :
            m_pC(primaryControllerPtr), m_sC(nullptr){}
        JathController(vex::controller* primaryControllerPtr, vex::controller* secondaryControllerPtr) : 
            m_pC(primaryControllerPtr), m_sC(secondaryControllerPtr){}

        bool getInput(JathController::buttons buttonToCheck){
          return enumToButton[buttonToCheck].pressing();
        }
        bool getInputPressed(JathController::buttons buttonToCheck){
          return enumToButton[buttonToCheck].PRESSED;
        }
        bool getInputReleased(JathController::buttons buttonToCheck){
          return enumToButton[buttonToCheck].RELEASED;
        }
      private:
        vex::controller* m_pC;//Primary Controller
        vex::controller* m_sC;//Secondary Controller

        std::map <JathController::buttons, vex::controller::button> enumToButton{            
            {pUp , m_pC->ButtonUp}, {pDown ,m_pC->ButtonDown}, {pLeft ,m_pC->ButtonLeft}, {pRright ,m_pC->ButtonRight},
            {pA ,m_pC->ButtonA}, {pB ,m_pC->ButtonB}, {pX ,m_pC->ButtonX}, {pY ,m_pC->ButtonY},
            {pLUp ,m_pC->ButtonL1}, {pLDown ,m_pC->ButtonL2}, {pRUp ,m_pC->ButtonR1}, {pRDown ,m_pC->ButtonR2},
            
            {sUp , m_pC->ButtonUp},  {sDown ,m_pC->ButtonDown},  {sLeft ,m_pC->ButtonLeft},  {sRright ,m_pC->ButtonRight},
            {sA ,m_pC->ButtonA},  {sB ,m_pC->ButtonB},  {sX ,m_pC->ButtonX},  {sY ,m_pC->ButtonY},
            {sLUp ,m_pC->ButtonL1},  {sLDown ,m_pC->ButtonL2},  {sRUp ,m_pC->ButtonR1},  {sRDown ,m_pC->ButtonR2},
          };
  };
}