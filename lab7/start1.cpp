// Starting code for Checkpoints 2 and 3.  This includes
// functions to read the grid and to output it.

#include <fstream>
#include <iostream>
#include <list>
#include <vector>
using namespace std;


// A simple class to represent a point location.  It only has a
// constructor and a two public member variables.  This is one of the
// few times that you are allowed to use non-private member variables.

class Point {
public:
  Point(int x0, int y0) : x(x0), y(y0) {}
  int x,y;
};


// Input the grid and the start location.  The input is a sequence of
// x y locations, terminated by x==0 and y==0.  The last input, which
// follows 0 0 input, is the start location.
//
// The grid is represented as a 2d vector of bools, with each location
// that is blocked --- meaning that no path can go through --- being
// represented by the value "true".  The grid is large enough to
// include all blocked points and include the starting location.  The
// first coordinate of the vector of vectors is the x coordinate, and
// the second is the y coordinate.  The format of the input is
// specified in the lab handout.

void read_grid(istream& istr, vector<vector<bool> > & blocked_grid,
	       int & start_x, int & start_y) {

  // Read the x y locations into a list of Points.  Keep track of the
  // max x and max y values so that the size of the grid can be
  // determined.
  int x, y;
  int max_x = 0, max_y = 0;  // keep track of the max coordinate values
  list<Point> blocked_points;
  while ((istr >> x >> y) && ! (x==0 && y==0)) {
    blocked_points.push_back(Point(x,y));
    if (x > max_x) max_x = x;
    if (y > max_y) max_y = y;
  }

  // Now that a 0 0 location has been read, read the start location.
  // If this is beyond the max x or y value then update these values.
  istr >> start_x >> start_y;
  if (start_x > max_x) max_x = start_x;
  if (start_y > max_y) max_y = start_y;

  // Make a vector of vectors with all entries marked false.   
  vector<bool> one_row_of_ys(max_y+1, false);
  vector<vector<bool> > empty_grid(max_x+1, one_row_of_ys);
  blocked_grid = empty_grid;

  // For Point in the list, mark the location in the list as blocked.
  list<Point>::iterator p;
  for (p = blocked_points.begin(); p != blocked_points.end(); ++p) {
    blocked_grid[p->x][p->y] = true;
  }
}


// Output the grid to cout.  The form of the output is explained in
// the cout statement below.

void print_grid(vector<vector<bool> > const& blocked_grid, int start_x, int start_y) {

  cout << "Here is the grid with the origin in the upper left corner, x increasing \n"
       << "horizontally and y increasing down the screen.  An 'X' represents a blocked\n"
       << "location and the 'S' represents the starting location.\n\n";

  for (int y=0; y<blocked_grid[0].size(); ++y) {
    for (int x=0; x<blocked_grid.size(); ++x) {
      if (x == start_x && y == start_y)
	cout << " S";
      else if (blocked_grid[x][y])
	cout << " X";
      else 
	cout << " .";
    }
    cout << '\n';
  }
}

bool check_blocked(const Point& p, vector<vector<bool> > const& blocked_grid) {
    if(blocked_grid[p.x][p.y] == true) {
        return false;
    }
    return true;
}

int count_number(const Point& p, vector<vector<bool> > const& blocked_grid, bool blocked) {
    //cout << "1";
    int out = 0;
    Point point = p;
    if(p.x == 0 && p.y == 0) {    // base case
        if(blocked == false) {
            return 1;
        }
        if(blocked == true) {    // a blocked path does not count
            return 0;
        }
    }
    if(point.x == 0 && point.y > 0) {
        if(check_blocked(Point(point.x, point.y-1), blocked_grid) == false) {
            blocked = true;
        }
        point.y -= 1;
        out += count_number(point, blocked_grid, blocked);
    }
    if (point.y == 0 && point.x > 0) {
        if(check_blocked(Point(point.x-1, point.y), blocked_grid) == false) {
            blocked = true;
        }
            point.x -= 1;
            out += count_number(point, blocked_grid, blocked);
    }
    if(point.x - 1 >= 0 && point.y - 1 >= 0) {
        bool block = blocked;
        bool block2 = blocked;   // make sure that the upper condition does not affect the lower one
        if(check_blocked(Point(p.x-1, p.y), blocked_grid) == false) {
            block = true;
        }
        point.x -= 1;
        out += count_number(point, blocked_grid, block);
        
        Point point2 = p;
        if(check_blocked(Point(p.x, p.y-1), blocked_grid) == false) {
            block2 = true;
        }
        point2.y -= 1;
        out += count_number(point2, blocked_grid, block2);
    }
    return out;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " grid-file\n";
    return 1;
  }
  ifstream istr(argv[1]);
  if (!istr) {
    cerr << "Could not open " << argv[1] << endl;
    return 1;
  }
  
  vector<vector<bool> > blocked_grid;
  int start_x, start_y;
  read_grid(istr, blocked_grid, start_x, start_y);
  print_grid(blocked_grid, start_x, start_y);

  // Start here with your code...
    bool blocked = false;     // mark if it was blocked
    Point p = Point(start_x,start_y);
    int num = count_number(p, blocked_grid, blocked);
    cout<<"paths for point:"<<start_x<<","<< start_y<<" is "<< num << endl;
    
    /*Point p2 = Point(9,6);
    num = count_number(p2, blocked_grid, blocked);
    cout<<"paths for test point "<<" is "<< num << endl;*/
    /*for(unsigned int i=0; i < blocked_grid.size(); i++) {
        for(unsigned int j=0; j < blocked_grid.size(); j++) {
            cout << blocked_grid[j][i] << " ";
        }
        cout<< "\n";
    }*/
    
  return 0;
}
      
