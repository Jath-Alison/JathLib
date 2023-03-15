#pragma once
#include "vex.h"
#include <map>
#include <vector>

namespace Jath{
  class CustomController{
      public:
        enum buttons{
            pUp, pDown, pLeft, pRright,
            pA, pB, pX, pY,
            pLUp, pLDown, pRUp, pRDown,
            
            sUp, sDown, sLeft, sRright,
            sA, sB, sX, sY,
            sLUp, sLDown, sRUp, sRDown
        };

        CustomController(vex::controller* primaryControllerPtr) :
            m_pC(primaryControllerPtr), m_sC(nullptr){}
        CustomController(vex::controller* primaryControllerPtr, vex::controller* secondaryControllerPtr) : 
            m_pC(primaryControllerPtr), m_sC(secondaryControllerPtr){}

        bool checkInput(CustomController::buttons buttonToCheck){
          return enumToButton[buttonToCheck].pressing();
        }
        bool checkInput(std::vector<CustomController::buttons> buttonsToCheck){
          for(int i=0; i<buttonsToCheck.size(); i++){
              if(!enumToButton[buttonsToCheck[i]].pressing()){
                return false;
            }
          }
          return true;
        }
      private:
        vex::controller* m_pC;//Primary Controller
        vex::controller* m_sC;//Secondary Controller

        std::map <CustomController::buttons, vex::controller::button> enumToButton{            
            {pUp , m_pC->ButtonUp}, {pDown ,m_pC->ButtonDown}, {pLeft ,m_pC->ButtonLeft}, {pRright ,m_pC->ButtonRight},
            {pA ,m_pC->ButtonA}, {pB ,m_pC->ButtonB}, {pX ,m_pC->ButtonX}, {pY ,m_pC->ButtonY},
            {pLUp ,m_pC->ButtonL1}, {pLDown ,m_pC->ButtonL2}, {pRUp ,m_pC->ButtonR1}, {pRDown ,m_pC->ButtonR2},
            
            {sUp , m_pC->ButtonUp},  {sDown ,m_pC->ButtonDown},  {sLeft ,m_pC->ButtonLeft},  {sRright ,m_pC->ButtonRight},
            {sA ,m_pC->ButtonA},  {sB ,m_pC->ButtonB},  {sX ,m_pC->ButtonX},  {sY ,m_pC->ButtonY},
            {sLUp ,m_pC->ButtonL1},  {sLDown ,m_pC->ButtonL2},  {sRUp ,m_pC->ButtonR1},  {sRDown ,m_pC->ButtonR2},
          };
  };

  class buttonMapping{
    public:
      buttonMapping(const char* name) {
          strcpy(m_name,name);
      }
      buttonMapping(const char* name, CustomController::buttons button) {
          m_buttons.push_back(button);
          strcpy(m_name,name);
      }
      buttonMapping(const char* name,std::vector<CustomController::buttons> buttons) : m_buttons(buttons){
        strcpy(m_name,name);
      }

      void addButton(CustomController::buttons button) {
        m_buttons.push_back(button);
      }
      char* getName(){return m_name;}
      std::vector<CustomController::buttons> getButtons(){return m_buttons;}
    private:
      char* m_name;
      std::vector<CustomController::buttons> m_buttons;
};
}