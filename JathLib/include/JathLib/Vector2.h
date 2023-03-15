#pragma once

#include "math.h"
#include <vector>

namespace Jath{

    struct Vector2{
        Vector2() : x(0.0f), y(0.0f){}
        Vector2(double x1, double y1) : x(x1), y(y1){}

        Vector2 operator + (const Vector2& vec){
            Vector2 temp;
            temp.x = x + vec.x;
            temp.y = y + vec.y;
            return temp;
        }

        Vector2 operator - (const Vector2& vec){
            Vector2 temp;
            temp.x = (x - vec.x);
            temp.y = (y - vec.y);
            return temp;
        }

        Vector2 operator * (double num){
            Vector2 temp(x,y);
            temp.x *= num;
            temp.y *= num;
            return temp;
        }

        double mag(){
            Vector2 temp;
            return distTo(temp);
        }

        double distTo(Vector2 &vec){
            double dist;

            dist = pow(x - vec.x, 2) + pow(y - vec.y, 2);

            dist = sqrt(dist);
            
            return dist;
        }

        Vector2 normalize(){
            double factor = (1 / mag ());
            Vector2 temp (x, y);
            return  temp * factor;
        }
        
        double x;
        double y;

    };
}