#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

// add a number, name pair to the phonebook
void add(map<int, string> &phonebook, int number, string const& name) {
  phonebook[number] = name;
}

// given a phone number, determine who is calling
void identify(const map<int, string> & phonebook, int number) 
{
  if (phonebook.count(number) == 0) 
    cout << "unknown caller!" << endl;
  else 
    cout << phonebook.at(number) << " is calling!" << endl;
}


int main() {
  // create the phonebook; initially all numbers are unassigned
  map<int, string> phonebook;

  // add several names to the phonebook
  add(phonebook, 1111111, "fred");
  add(phonebook, 2222222, "sally");
  add(phonebook, 3333333, "george");

  // test the phonebook
  identify(phonebook, 2222222);
  identify(phonebook, 4444444);
}