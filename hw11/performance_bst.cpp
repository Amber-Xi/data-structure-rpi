#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
using namespace std;

// defined in performance.cpp
void usage();


void bst_test(const std::string* input_data, int input_count, const std::string &operation, std::string *output_data, int &output_count) {

  // HINT: declare your binary search tree (BST) like this:
  // std::set<std::string> st;
  // OR 
  std::map<std::string,int> mp;

  for(int i = 0; i < input_count; i++)
  {
    //reading the input data
    std::map<std::string,int>::iterator itr = mp.find(input_data[i]);
    if(itr != mp.end())
    {
      mp[input_data[i]]++;
    }
    else
    {
       mp[input_data[i]] = 1;
    }
  }

  if (operation == "sort") 
  {
    output_count = 0;
    std::map<std::string,int>::iterator itr;
    //based on the map sort
    for(itr = mp.begin(); itr!= mp.end(); itr++)
    {
      for (int i = 0; i < itr->second; i++)
      {
        //read into output
        output_data[output_count] = itr->first;
        output_count++;

      }
    }
  } 
  else if (operation == "remove_dups_same_order") 
  {
    output_count = 0;
    for (int i = 0; i < input_count; i++)
    {
      //checking whether output has the same string
      std::map<std::string,int>::iterator itr = mp.find(input_data[i]);
      if(itr != mp.end())
      {
        output_data[output_count] = input_data[i];
        output_count++;
        mp.erase(itr);
      }
    }

  } 
  else if (operation == "remove_dups_any_order") 
  {
    output_count = 0;
    std::map<std::string,int>::iterator itr;
    //go over the mao and read into output
    for(itr = mp.begin(); itr!= mp.end(); itr++)
    {
      output_data[output_count] = itr->first;
      output_count++;
    }

  } 
  else if (operation == "mode")
  {
    int max = (mp.begin())->second;
    std::map<std::string,int>::iterator itr;
    for(itr = mp.begin(); itr!= mp.end(); itr++)
    {
      //finding the max occurence 
      if(itr->second > max)
      {
        //update the max
        max = itr->second;
      }
    }

    for(itr = mp.begin(); itr!= mp.end(); itr++)
    {
      //output the max occurence string
      if(max == itr->second)
      {
        output_count = 1;
        output_data[0] = itr->first;
        break;
      }
    }
  } 
  else 
  {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
