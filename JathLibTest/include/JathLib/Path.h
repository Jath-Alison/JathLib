#pragma once

#include "Point.h"

#include "tinyxml2.h"

#include <math.h>
#include <vector>
#include <iostream>

namespace Jath{

    class Path{
    public:

        Path (std::vector<Point> points) : m_originalPoints(points), m_points (points){}
        Path () : m_originalPoints(), m_points(){


            m_originalPoints.push_back (Point (Vector2 (0, 0)));
            m_points.push_back (Point (Vector2 (0, 0)));
            m_originalPoints.push_back (Point (Vector2 (10, 0)));
            m_points.push_back (Point (Vector2 (10, 0)));

            m_originalPoints.push_back (Point (Vector2 (10, 10)));
            m_points.push_back (Point (Vector2 (10, 10)));
        }

        void initPathConfig (double &a, double &b, double &c, double &d, double &e, double &f, double &g){
            a = m_a;
            b = m_b;
            c = m_c;
            d = m_d;
            e = m_e;
            f = m_f;
            g = m_g;
        }
        void computePathConfig(double a, double b, double c, double d, double e, double f, double g){
            m_a = a;
            m_b = b;
            m_c = c;
            m_d = d;
            m_e = e;
            m_f = f;
            m_g = g;
        }
        void computePath (double a, double b, double c, double d, double e, double f, double g){
            computePathConfig (a, b, c, d, e, f, g);

            m_points = m_originalPoints;

            fillWithPoints (m_a * (72.f / 500.f));
            smoothPath (m_b, m_c, m_d, m_e);
            calculateDistAlongPath ();
            calculateCurvature ();
            //calculateSpeeds (m_f, m_g);
        }
        void computePath (){
            //computePathConfig (a, b, c, d, e, f, g);

            m_points = m_originalPoints;

            fillWithPoints (m_a * (72.f / 500.f));
            smoothPath (m_b, m_c, m_d, m_e);
            calculateDistAlongPath ();
            calculateCurvature ();
            calculateSpeeds (m_f, m_g);
        }

        void fillWithPoints (double space);
        void smoothPath (double weight_data, double weight_smooth, double tolerance, double factor);

        void calculateDistAlongPath ();
        void calculateCurvature ();

        void calculateSpeeds (double maxVelocity, double slowAtCurveWeight);

        Point* getClosestPoint (Vector2 pos);
        Point* getLookAheadPoint (Vector2 pos, double lookAheadDist);
        
        Point* getClosestOriginalPoint (Vector2 pos);

        void addPoint (Point* pointAfter,Point point){
            int id = 0;
            for(size_t i = 0; i < m_originalPoints.size (); i++){
                if(&m_originalPoints[i] == pointAfter){
                    id = i;
                    break;
                }
            }
            
            m_originalPoints.insert (m_originalPoints.begin () + id,point);
        }
        void delPoint (Point* point){
            if(m_originalPoints.size () <= 2){
                return;
            }
            int id = 0;
            for(size_t i = 0; i < m_originalPoints.size(); i++){
                if(&m_originalPoints[i] == point){
                    id = i;
                    break;
                }
            }
            m_originalPoints.erase (m_originalPoints.begin()+id);
        }

        void saveToXml (int autonNum);
        void loadFromXml (int autonNum);

        std::vector<Point> getOriginalPoints(){return m_originalPoints;}
        std::vector<Point> getPoints(){return m_points;}

    private:
        std::vector<Point> m_originalPoints;
        std::vector<Point> m_points;

        double m_a;
        double m_b;
        double m_c;
        double m_d;
        double m_e;
        double m_f;
        double m_g;

    };
}