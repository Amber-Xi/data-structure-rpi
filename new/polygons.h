#include "utilities.h"
using namespace std;
class Polygon{
public:
	Polygon(const string& name_, const vector<Point> &points_) : name(name_), points(points_) {}
	virtual string getName(){
		return name;
	}
	virtual bool HasAllEqualSides(){
		bool A = true;
		double d= DistanceBetween(points[0], points[points.size()-1]);
		for(int i =0; i < points.size()-1; i++){
			if(!EqualSides(DistanceBetween(points[i], points[i+1]),d)){
				A = false;
			}
		}
		return A;
	}
	virtual ~Polygon() {}

	virtual bool HasARightAngle(){
		bool A = false;
		if(points.size() >= 3){
		if(RightAngle(Angle(points[points.size()-2],points[points.size()-1], points[0])) ||
		 RightAngle(Angle(points[points.size()-1],points[0], points[1]))){
			A = true;
		}
		for(int i = 0; i < points.size()-2; i++){
			if(RightAngle(Angle(points[i],points[i+1], points[i+2]))){
				A = true;
			}
		}}
		return A;
	}
	virtual bool HasAllEqualAngles(){
		bool A = true;
		if(points.size() >= 3){
		double b = Angle(points[points.size()-2],points[points.size()-1], points[0]);
		double c = Angle(points[points.size()-1],points[0], points[1]);
		if(!EqualAngles(b, c)){
			A = false;
		}
		for(int i = 0; i < points.size()-2; i++){
			if(!EqualAngles(b, Angle(points[i],points[i+1], points[i+2]))){
				A = false;
			}
		}}
		return A;
	}
protected:
	string name;
	vector<Point> points;
};

class Quadrilateral : public Polygon{
public:
	Quadrilateral(const string& name, const vector<Point> &points) : Polygon(name, points) {
		if(points.size()!= 4){
			throw -1;
		}
	}

};

class Rectangle : public Quadrilateral{
public:
	Rectangle(const string& name, const vector<Point> &points) : Quadrilateral(name, points) {
		if(!(Angle(points[0], points[1], points[2]) == 90 && Angle(points[1], points[2], points[3]) == 90)){
			throw -1;
		}
		else if(DistanceBetween(points[0], points[1]) != DistanceBetween(points[2], points[3])){
			throw -1;
		}
	}
};

class Square : public Rectangle{
public:
	Square(const string& name, const vector<Point> &points) : Rectangle(name, points){
		if(DistanceBetween(points[0], points[1])!= DistanceBetween(points[1], points[2])){
			throw -1;
		}
	}

};

class Triangle : public Polygon{
public:
	Triangle(const string& name, const vector<Point> &points) : Polygon(name, points){
		if(points.size()!= 3){
			throw -1;
		}
	}
};

class IsoscelesTriangle : virtual public Triangle{
public:
	IsoscelesTriangle(const string& name, const vector<Point> &points) : Triangle(name, points){
		if(!(DistanceBetween(points[0], points[1]) == DistanceBetween(points[1], points[2])
			|| DistanceBetween(points[0], points[1]) == DistanceBetween(points[0], points[2])
			|| DistanceBetween(points[0], points[2]) == DistanceBetween(points[1], points[2]))){
			throw -1;
		}
	}
};

class EquilateralTriangle : public IsoscelesTriangle{
public:
	EquilateralTriangle(const string& name, const vector<Point> &points) : Triangle(name, points), IsoscelesTriangle(name, points){
		if(!HasAllEqualSides()){
			throw -1;
		}
	}
};

class RightTriangle : virtual public Triangle{
public:
	RightTriangle(const string& name, const vector<Point> &points) : Triangle(name, points){
		if(!HasARightAngle()){
			throw -1;
		}
	}
};

class IsoscelesRightTriangle : public RightTriangle, public IsoscelesTriangle{
public:
	IsoscelesRightTriangle(const string& name, const vector<Point> &points) : Triangle(name, points), RightTriangle(name, points), IsoscelesTriangle(name, points){}
};
