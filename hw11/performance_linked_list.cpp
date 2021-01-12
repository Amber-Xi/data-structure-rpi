#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;

// defined in performance.cpp
void usage();


void list_test(const std::string* input_data, int input_count, const std::string &operation, std::string *output_data, int &output_count) {

  // HINT: declare your list like this:
  std::list<std::string> lst;
  for (int i = 0; i < input_count; i++) 
    lst.push_back(input_data[i]);
 

  if (operation == "sort") 
  {
    //sort and read the sorted data into the output
    lst.sort();
    output_count = input_count;
    std::list<string>::iterator index = lst.begin();

    for (int i = 0; i < output_count; i++)
    {
      output_data[i] = *index;
      index++;
    }
    
  } 
  else if (operation == "remove_dups_same_order") 
  {
    //deleting the repeated strings
    lst.unique();
    output_count = 0;
    std::list<std::string>::iterator itr = lst.begin();

    for(; itr!= lst.end(); itr++)
    {
      //checking whether the output has the same string
      bool A = true;
      for(int i = 0; i< output_count; i++)
      {
        if(*itr == output_data[i])
        {
          A = false;
          break;
        }
      }
      // if the output does not has the same string, just put into the output
      if (A)
      {
        output_data[output_count] = *itr;
        output_count++;
      }
    }

  }
  else if (operation == "remove_dups_any_order") 
  {
    //sorting and deleting the repeated strings
    lst.sort();
    lst.unique();
    std::list<string>::iterator index = lst.begin();
    output_count = 0;
    //reading into the ouput
    for (;index != lst.end(); index++ )
    {
      output_data[output_count] = *index;
      output_count++;
    }
  } 
  else if (operation == "mode") 
  {
    lst.sort();
    int current_count = 1;
    std::string mode;
    int mode_count = 0;
    // keep track of two pointers into the structure
    list<std::string>::iterator current = lst.begin();
    ++current;
    list<std::string>::iterator previous = lst.begin();
    for (; current != lst.end(); ++current, ++previous) {
      if (*current == *previous) {
  // if they are the same increment the count
        current_count++;
      } else if (current_count >= mode_count) {
        // found a new mode!
        mode = *previous;
        mode_count = current_count;
        current_count = 1;
      } else {
        current_count = 1;
      }
    }
    if (current_count >= mode_count) {
      // last entry is a new mode!
      mode = *previous;
      mode_count = current_count;
    }
    // save the mode to the output vector
    output_count = 1;
    output_data[0] = mode;
    

  } 
  else 
  {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
