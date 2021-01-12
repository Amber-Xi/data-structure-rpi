#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

// defined in performance.cpp
void usage();


void priority_queue_test(const std::string* input_data, int input_count, const std::string &operation, std::string *output_data, int &output_count) {

  // HINT: declare your priority_queue like this:
  std::priority_queue<std::string,std::vector<std::string> > pq(input_data,input_data+input_count);

  if (operation == "sort") 
  {
    for(int i = input_count-1; i>=0; i--)
   {
    //each time put the top in output 
     output_data[i] = pq.top();
     output_count++;
     // and then pop the top one
     pq.pop();
   }

  } 
  else if (operation == "remove_dups_same_order") 
  {
  } 
  else if (operation == "remove_dups_any_order")
  {
      output_count = 0;
      // go over the input data
      while(!pq.empty())
      {
        bool A = true;
        string s = pq.top();
        pq.pop();
        //checking whether the repated word in output
        for(int i = 0; i< output_count; i++)
        { 
          if(output_data[i] == s)
          {
            A = false;
            break;
          }
        }
        // if ok, read in.
       if(A)
       {
          output_data[output_count] = s;
          output_count++;
        }
       }


  }
  else if (operation == "mode")
  {
    int current_count = 1;
    std::string mode;
    int mode_count = 0;
    // keep track of two pointers into the structure
    string previous = pq.top();
    pq.pop();
    string current = pq.top();
    while(!pq.empty())
    {
      current = pq.top();
      if (current == previous) 
      {
  // if they are the same increment the count
        current_count++;
      } 
      else if (current_count >= mode_count) 
      {
        // found a new mode!
        mode = previous;
        mode_count = current_count;
        current_count = 1;
      } 
      else 
      {
        current_count = 1;
      }
      previous = pq.top();
      pq.pop();
    }
    if (current_count >= mode_count) 
    {
      // last entry is a new mode!
      mode = previous;
      mode_count = current_count;
    }
    // save the mode to the output vector
    output_count = 1;
    output_data[0] = mode;


  } 
  else {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
