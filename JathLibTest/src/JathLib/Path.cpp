#include "JathLib/Path.h"
#include<string>
#include <cmath>

namespace Jath{

  void Path::fillWithPoints (double space){
      std::vector<Point> temp;
      temp.push_back (m_points.front ());

      for(size_t j = 0; j < m_points.size () - 1; j++){


          Vector2 vector = m_points[j + 1].coords - m_points[j].coords;
          int maxPoints = ceil (( vector.mag () ) / space);

          vector = vector.normalize () * space;

          for(time_t i = 1; i < maxPoints; i++){
              Vector2 tempVector = vector * i;

              Point next (m_points[j].coords + tempVector);
              temp.push_back (next);
          }

      }

      m_points = temp;
  };

  void Path::smoothPath (double weight_data, double weight_smooth, double tolerance, double factor){
      for(size_t j = 0; j < factor; j++){
          std::vector<Point> temp = m_points;

          double change = tolerance;
          while(change >= tolerance){
              change = 0.0;
              for(int i = 1; i < m_points.size () - 1; i++){
                  Vector2 aux = temp[i].coords;
                  temp[i].coords = temp[i].coords +
                      ( m_points[i].coords - temp[i].coords ) * weight_data +
                      ( temp[i - 1].coords + temp[i + 1].coords - ( temp[i].coords * 2.0 ) ) * weight_smooth;
                  change += (aux - temp[i].coords).x + (aux - temp[i].coords).y; 
              }
          }
          m_points = temp;
      }
  }

  void Path::calculateDistAlongPath (){
      for(size_t i = 1; i < m_points.size (); i++){

          Vector2 dist = m_points[i].coords - m_points[i - 1].coords;

          m_points[i].distAlongPath = dist.mag () + m_points[i - 1].distAlongPath;
      }
  };

  void Path::calculateCurvature (){

      Vector2 coord1;
      Vector2 coord2;
      Vector2 coord3;

      double k1;
      double k2;
      double b;
      double a;
      double r;
      double curvature;

      for(size_t i = 1; i < m_points.size () - 1; i++){
          coord1 = m_points[i - 1].coords;
          coord1.x += 0.0001;
          coord1.y += 0.0001;

          coord2 = m_points[i].coords;
          coord3 = m_points[i + 1].coords;

          k1 = 0.5 * ( pow (coord1.x, 2) + pow (coord1.y, 2) - pow (coord2.x, 2) - pow (coord2.y, 2) ) /
              ( coord1.x - coord2.x );
          k2 = ( coord1.y - coord2.y ) / ( coord1.x - coord2.x );
          b = 0.5 * ( pow (coord2.x, 2) - 2 * coord2.x * k1 + pow (coord2.y, 2) - pow (coord3.x, 2) + 2 * coord3.x * k1 - pow (coord3.y, 2) ) /
              ( coord3.x * k2 - coord3.y + coord2.y - coord2.x * k2 );
          a = k1 - k2 * b;
          r = sqrt (pow (coord1.x - a, 2) + pow (coord1.y - b, 2));
          curvature = 1 / r;

          //curvature *= 1000;

          //if(curvature < 1){
          //    curvature = .0001;
          //}

          m_points[i].curveOfPath = curvature + .000001;

      }

  }

  void Path::calculateSpeeds (double maxVelocity, double slowAtCurveWeight){

      for(size_t i = 0; i < m_points.size (); i++){
          double maxVel = fmin (slowAtCurveWeight / m_points[i].curveOfPath, maxVelocity);

          m_points[i].maxVelocity = maxVel;
      }

      m_points.back ().targetRobotVel = 0;

      for(size_t i = m_points.size () - 2; i > 0; i--){

          double dist = Vector2 (m_points[i].coords - m_points[i + 1].coords).mag ();

          double v1 = sqrt (pow (m_points[i + 1].targetRobotVel, 2) + 2 * 10 * dist);

          m_points[i].targetRobotVel = std::fmin (m_points[i + 1].maxVelocity, v1);

      }
  }

  Point* Path::getClosestPoint (Vector2 pos){

      Vector2 shortest = m_points.front().coords - pos;
      size_t shortedId = 0;

      for(size_t i = 0; i < m_points.size(); i++){
          if((m_points[i].coords - pos).mag() < shortest.mag ()){
              shortest = ( m_points[i].coords - pos );
              shortedId = i;
          }
      }

      return &m_points[shortedId];
  }

  Point* Path::getLookAheadPoint (Vector2 pos, double lookAheadDist){

      Point* lastInRange = nullptr;

      for(size_t i = 0; i < m_points.size(); i++){
          if(pos.distTo(m_points[i].coords) < lookAheadDist){
              lastInRange = &m_points[i];
          }
      }

      if(lastInRange == nullptr){
          Point* closest = getClosestPoint (pos);

          if(closest == &m_points[m_points.size () - 1]){
              return closest;
          }
          return closest + 1;
      }

      return lastInRange;
  }

  Point* Path::getClosestOriginalPoint (Vector2 pos){

      Vector2 shortest = m_originalPoints.front ().coords - pos;
      size_t shortedId = 0;

      for(size_t i = 0; i < m_originalPoints.size (); i++){
          if(( m_originalPoints[i].coords - pos ).mag () < shortest.mag ()){
              shortest = ( m_originalPoints[i].coords - pos );
              shortedId = i;
          }
      }

      return &m_originalPoints[shortedId];
  }


  void Path::saveToXml (int autonNum) {
  }

  void Path::loadFromXml (int autonNum){
      const char* path = "PathPlanner\\Auton.xml";

      tinyxml2::XMLDocument doc;
      doc.LoadFile (path);

      if (doc.Error()){
        std::cout << "XML File not found" << std::endl;
        return;
      }

      tinyxml2::XMLElement* root = doc.FirstChildElement ();

      tinyxml2::XMLElement* auton = root->FirstChildElement ("auton");
      while(auton != nullptr){
          int id = 0;
          auton->QueryIntAttribute ("id", &id);
          if(id == autonNum){
              break;
          }

          auton = auton->NextSiblingElement ("auton");
      }
      if(auton == nullptr){
          std::cout << "No Auton Found For" << autonNum << std::endl;
          return;
      }

      std::vector<Point> tempPoints;

      tinyxml2::XMLElement* step = auton->FirstChildElement ("step");

      auton->QueryDoubleAttribute ("a", &m_a);
      auton->QueryDoubleAttribute ("b", &m_b);
      auton->QueryDoubleAttribute ("c", &m_c);
      auton->QueryDoubleAttribute ("d", &m_d);
      auton->QueryDoubleAttribute ("e", &m_e);
      auton->QueryDoubleAttribute ("f", &m_f);
      auton->QueryDoubleAttribute ("g", &m_g);

      while(step != nullptr){


          int id = 0;
          Vector2 pointCoords;

          step->QueryIntAttribute ("id", &id);
          step->QueryDoubleAttribute ("x", &pointCoords.x);
          step->QueryDoubleAttribute ("y", &pointCoords.y);

          std::vector <Macro> tempMacros;

          tinyxml2::XMLElement* Xmlmacro = step->FirstChildElement("macro");

          Macro tempMacro;

          while (Xmlmacro != nullptr)
          {
              const char* macroName;
              Xmlmacro->QueryStringAttribute("name", &macroName);

              tempMacros.push_back(Macro(macroName));

              Xmlmacro = Xmlmacro->NextSiblingElement("macro");
          }

          Point tempPoint = Point(pointCoords, tempMacros);

          tempPoints.push_back (tempPoint);

          step = step->NextSiblingElement ("step");
      }
      m_originalPoints = tempPoints;
      m_points = tempPoints;
  }

  #if USING_SFML == 1
      void Path::displayOriginal (sf::RenderWindow* window, sf::Color col){
          for(size_t i = 0; i < m_originalPoints.size (); i++){
              sf::CircleShape temp (10, 100);

              sf::Font font;
              font.loadFromFile ("Calibri Light.ttf");

              sf::Text text ("", font, 20);
              text.setString(std::to_string(i));
              text.setPosition (sf::Vector2f (m_originalPoints[i].coords.x, m_originalPoints[i].coords.y));
              text.setOrigin (sf::Vector2f (temp.getRadius (), temp.getRadius ()));

              temp.setOrigin (sf::Vector2f (temp.getRadius (), temp.getRadius ()));
              temp.setPosition (sf::Vector2f (m_originalPoints[i].coords.x, m_originalPoints[i].coords.y));

              
              temp.setFillColor (sf::Color(0,std::fmax((255 * (m_originalPoints.size ()-i)/m_originalPoints.size()),100), 0, 255));
              window->draw (temp);
              //window->draw (text);
          }
      }

      void Path::displayModified (sf::RenderWindow* window, sf::Color col){
          for(size_t i = 0; i < m_points.size (); i++){
              sf::CircleShape temp (4, 100);

              temp.setOrigin (sf::Vector2f (temp.getRadius (), temp.getRadius ()));
              temp.setPosition (sf::Vector2f (m_points[i].coords.x, m_points[i].coords.y));

              if(col == sf::Color::Green){
                  temp.setFillColor (sf::Color (50, m_points[i].targetRobotVel / 100 * 255, 50));
              } else if(col == sf::Color::Blue){
                  temp.setFillColor (sf::Color (50, 50, m_points[i].targetRobotVel / 100 * 255));
              }
              window->draw (temp);
          }
      }

  #endif // USING_SFML == 0



      //void macroSfmlLoop() {

      //    

      //    while (window.isOpen())
      //    {
      //        sf::Event event;
      //        while (window.pollEvent(event)) {
      //            if (event.type == sf::Event::Closed) {
      //                window.close();
      //            }
      //        }
      //        
      //        window.clear();

      //        mtx.lock();

      //        if (highLight != nullptr) {
      //            for (size_t i = 0; i < highLight->macros.size(); i++)
      //            {
      //                sf::Text tempText(highLight->macros[i].name, calibri, 100);
      //                tempText.setFillColor(sf::Color::Red);
      //                tempText.setPosition(sf::Vector2f(50, 50));
      //                window.draw(tempText);
      //                window.draw(sf::CircleShape(50, 50));

      //            }
      //        }
      //        window.display();


      //        mtx.unlock();
      //    }
      //}
}