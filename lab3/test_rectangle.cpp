#include "Point2D.h"
#include "Rectangle.h"
#include <iostream>
int main()
{
    Point2D p1(8,10);
    Point2D p2(9,3.5);
    Point2D p3(0,0);

    Rectangle r(Point2D(4,3), Point2D(17,9));
    Rectangle r1(Point2D(4,4), Point2D(9,9));
    
    std::cout << r.is_point_within(p1) << std::endl;
    std::cout << r.is_point_within(p2) << std::endl;
    
    std::cout << r1.is_point_within(p1) << std::endl;
    std::cout << r1.is_point_within(p3) << std::endl;
    
    std::cout << r.add_point(p1) << std::endl;
    std::cout << r.add_point(p2) << std::endl;
    
    print_rectangle(r);
    return 0;
}
