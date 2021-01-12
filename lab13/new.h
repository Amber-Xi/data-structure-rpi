using namespace std;
#include<vector>
#include "utilities.h"
class Polygon
{
     public:
       Polygon(const string& name_,const std::vector<Point> &points_) 
       {
        name = name_;
        points = points_;
        for(int i= 0; i< points_.size(); i++)
        {
          unsigned int index = i+1;
          if(index == points_.size()){
            index = 0;
          }
          Vector v(points_[i], points_[index]);
          slids.push_back(v);
        }
       }

       virtual ~Polygon() {}

       const string &getName() const
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

       
       virtual bool HasAllEqualAngles()
       {
        int count = 0;
  
        for(int i =0; i< slids.size()-1; i++)
        {
          if(!EqualAngles(slids[i].Length(), slids[i+1].Length()))
          {
            return false;
          }
        }
        if(!EqualAngles(slids[0].Length(), slids[slids.size()-1].Length()))
        {
          return false;
        }

        return true;
       }

       virtual bool HasARightAngle()
       {
        for(int i = 0; i<points.size()-2; i++)
        {
         if(RightAngle(Angle(points[i], points[i+1], points[i+2])))
         {
           return true;
         }
        }

        if(RightAngle(Angle(points[0], points[points.size()-1], points[points.size()-2])))
        {
          return true;
        }

        if(RightAngle(Angle(points[1], points[0], points[points.size()-1])))
        {
          return true;
        }
        return false;


      }
       

     protected:
       vector<Point> points;
       vector<Vector> slids;
       string name;
};


class Triangle : public Polygon 
{
     public:
       Triangle(const string& name,const std::vector<Point> &points):Polygon(name, points)
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
       Quadrilateral(const string& name,const std::vector<Point> &points):Polygon(name, points)
       {
        if(points.size() != 4)
        {
          throw 1;
        }
       }
};

class IsoscelesTriangle: virtual public Triangle
{
  public:
       IsoscelesTriangle(const string& name,const std::vector<Point> &points):Triangle(name, points)
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
       EquilateralTriangle(const string& name,const std::vector<Point> &points):Triangle(name, points),IsoscelesTriangle(name, points)
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
       Rectangle(const string& name,const std::vector<Point> &points):Quadrilateral(name, points)
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
       Square(const string& name,const std::vector<Point> &points):Rectangle(name, points)
       {
        if(!HasAllEqualSides())
        {
          throw 1;
        }
       }
};


class Kite:public Quadrilateral 
{
   public:
       Kite(const string& name,const std::vector<Point> &points):Quadrilateral(name, points)
       {
         int count = 0;
         for(int i = 0 ; i< slids.size(); i++)
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

          if(count<2)
          {
            throw 1;
          }

       }

};

class Trapezoid:public Quadrilateral
{
public:
  Trapezoid(const string& name, const std::vector<Point> &points):Quadrilateral(name, points)
  {
    if(points.size() != 4)
        {
          throw 1;
        }
  }  
};

class Parallelogram:public Trapezoid
{
  public:
  Parallelogram(const string& name,const std::vector<Point> &points):Trapezoid(name, points)
  {
    int count = 0;
    for(int i = 0 ; i< slids.size(); i++)
    {
      for(int j = i+1 ; j< slids.size(); j++)
      {
        if(Parallel(slids[i], slids[j]))
        {
          count ++;
        }
      }
    }

    if(count < 2)
    {
      throw 1;
    }
  }

};

class Rhombus:public Parallelogram
{
  public:
  Rhombus(const string& name,const std::vector<Point> &points):Parallelogram(name, points)
  {
    if(!HasAllEqualSides())
        {
          throw 1;
        }
  }  
};

class RightTriangle:virtual public Triangle
{
  public:
  RightTriangle(const string& name,const std::vector<Point> &points):Triangle(name, points)
  {

    if(!HasARightAngle())
    {
      throw 1;
    }
  } 
};


class IsoscelesRightTriangle:public RightTriangle, public IsoscelesTriangle
{
  public:
  IsoscelesRightTriangle(const string& name,const std::vector<Point> &points):Triangle(name, points), RightTriangle(name, points), IsoscelesTriangle(name, points)
  {}
};






