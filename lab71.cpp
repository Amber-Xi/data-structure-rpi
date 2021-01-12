#include<iostream>
#include<math.h>
int find_path(unsigned int x, unsigned int y);


int find_path(unsigned int x, unsigned int y)
{
    double d = sqrt(x*x + y*y);
    
    if(x == 0 && y ==0)
    {
        return 1;
    }
    else
    {
        return find_path(x, y-1) + find_path(x-1, y);
    }
    /*
     if(sqrt((x+1)*(x+1) + y*y) < d)
     {
     return find_path(x+1, y);
     }
     else if(sqrt((x-1)*(x-1) + y*y) < d)
     {
     return find_path(x+1, y);
     }
     if(sqrt(x*x + (y+1)*(y+1)) < d)
     {
     return find_path(x, y+1);
     }
     if(sqrt(x*x + (y-1)*(y-1)) < d)
     {
     return find_path(x, y-1);
     }
     */
    return 0;
}
