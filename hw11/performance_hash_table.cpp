#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>


// defined in performance.cpp
void usage();


void hash_table_test(const std::string* input_data, int input_count, const std::string &operation, std::string *output_data, int &output_count) {

  // HINT: declare your hash table like this:
  // std::unordered_set<std::string> ht(input_count);
  // OR 
  std::unordered_map<std::string,int> ht(input_count);


  for(int i = 0; i < input_count; i++)
  {
    //reading the input data
    std::unordered_map<std::string,int>::iterator itr = ht.find(input_data[i]);
    if(itr != ht.end())
    {
      ht[input_data[i]]++;
    }
    else
    {
       ht[input_data[i]] = 1;
    }
  }


  if (operation == "sort") 
  {
  } 
  else if (operation == "remove_dups_same_order") 
  {
    output_count = 0;
    for (int i = 0; i < input_count; i++)
    {
      std::unordered_map<std::string,int>::iterator itr = ht.find(input_data[i]);
      if(itr != ht.end())
      {
        output_data[output_count] = input_data[i];
        output_count++;
        ht.erase(itr);
      }
    }
  } 
  else if (operation == "remove_dups_any_order") 
  {
    output_count = 0;
    std::unordered_map<std::string,int>::iterator itr;
    for(itr = ht.begin(); itr!= ht.end(); itr++)
    {
      //checking whether output has the same string
      output_data[output_count] = itr->first;
      output_count++;
    }
  } 
  else if (operation == "mode")
  {
    int max = (ht.begin())->second;
    std::unordered_map<std::string,int>::iterator itr;
    //go over the mao and read into output
    for(itr = ht.begin(); itr!= ht.end(); itr++)
    {
      if(itr->second > max)
      {
        //update the max
        max = itr->second;
      }
    }

    for(itr = ht.begin(); itr!= ht.end(); itr++)
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
  else {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
