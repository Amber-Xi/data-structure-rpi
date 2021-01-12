using namespace std;
#include<vector>
#include "utilities.h"
class Polygon
{
     public:
       Polygon(string name_,std::vector<Point> points) 
       {
        name = name_;
        points = points;
        for(int i= 0; i< points.size(); i++)
        {
          unsigned int index = i+1;
          if(index == points.size()){
            index = 0;
          }
          Vector v(points[i], points[index]);
          slids.push_back(v);
        }
       }

       virtual const string &getName() const
       {
        return name;
       }

       virtual bool HasAllEqualSides()
       {
        for(int i = 0; i<slids.size()-1; i++)
        {
          if(!EqualSides(slids[i].Length(), slids[i+1].Length()))
          {
           return false;
          }
        }

        if(!EqualSides(slids[0].Length(), slids[slids.size()-1].Length()))
        {
          return false;
        }
        return true;
       }

     protected:
       vector<Point> points;
       vector<Vector> slids;
       string name;
};


class Triangle : public Polygon 
{
     public:
       Triangle(string name,std::vector<Point> points):Polygon(name, points)
       {
        if(points.size() != 3)
        {
          throw 1;
        }
       } 
};
     
class Quadrilateral : public Polygon 
{
     public:
       Quadrilateral(string name,std::vector<Point> points):Polygon(name, points)
       {
        if(points.size() != 4)
        {
          throw 1;
        }
       }
};

class IsoscelesTriangle: public Triangle
{
  public:
       IsoscelesTriangle(string name,std::vector<Point> points):Triangle(name, points)
       {
        int count = 0;
        for(int i = 0; i< slids.size()-1; i++)
        {
          if(EqualSides(slids[i].Length(), slids[i+1].Length()))
          {
            count ++;
          }
        }
        if(EqualSides(slids[0].Length(), slids[slids.size()-1].Length()))
        {
          count ++;
        }

        if(count == 0)
        {
          throw 1;
        }
       }

};

class EquilateralTriangle: public IsoscelesTriangle
{
  public:
       EquilateralTriangle(string name,std::vector<Point> points):IsoscelesTriangle(name, points)
       {
        if(!HasAllEqualSides())
        {
          throw 1;
        }
       }
  
};

class Rectangle: public Quadrilateral
{

  public:
       Rectangle(string name,std::vector<Point> points):Quadrilateral(name, points)
       {

        int count = 0;
        for(int i = 0; i< points.size()-2; i++)
        {
          if(RightAngle(Angle(points[i], points[i+1], points[i+2])))
          {
            count ++;
          }
        }
        if(RightAngle(Angle(points[2], points[3], points[0])))
        {
          count ++;
        }
        if(RightAngle(Angle(points[3], points[0], points[1])))
        {
          count ++;
        }

        if(count != 4)
        {
          throw 1;
        }
       }
  
};

class Square: public Rectangle
{
  public:
       Square(string name,std::vector<Point> points):Rectangle(name, points)
       {
        if(!HasAllEqualSides())
        {
          throw 1;
        }
       }
};

