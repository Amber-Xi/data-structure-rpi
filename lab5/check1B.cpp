#include <iostream>
#include <string>
#include <list>


template <class T>
void print(std::list<T> &data, const std::string &label) {
  std::cout << label << " ";
  typename std::list<T>::iterator itr;
  for (itr = data.begin(); itr != data.end(); itr++) {
    std::cout << " " << *itr;
  }
  std::cout << std::endl;
}


template <class T>
void reverse(std::list<T> &data) {
  typename std::list<T>::iterator itr = data.begin();
  typename std::list<T>::reverse_iterator itr2 = data.rbegin();
  for(unsigned int i = 0; i < data.size()/2; i++){
    T temp = *itr;
    *itr = *itr2;
    *itr2 = temp;
    itr++;
    itr2++;
  }
}
/*
template <class T>
void reverse(std::list<T> &data)
{
    typename std::list<T>::iterator itr2 = data.begin();
    for(unsigned int i=0; i< data.size(); i++)
    {
        T temp = data.back();
        data.insert(itr2, temp);
        data.pop_back();
    }
}
 */



int main() {
  std::list<int> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);
  data.push_back(5);
  data.push_back(6);
  data.push_back(7);

  print(data,"before:");
  reverse(data);
  print(data,"after: ");

  std::list<std::string> data2;
  data2.push_back("apple");
  data2.push_back("banana");
  data2.push_back("carrot");
  data2.push_back("date");

  print(data2,"before:");
  reverse(data2);
  print(data2,"after: ");

  std::list<std::string> data3;
  print(data3,"before:");
  reverse(data3);
  print(data3,"after: ");

  std::list<int> data4;
  data4.push_back(1);
  print(data4,"before:");
  reverse(data4);
  print(data4,"after: ");

  std::list<int> data5;
  data5.push_back(1);
  data5.push_back(2);
  print(data5,"before:");
  reverse(data5);
  print(data5,"after: ");
}
