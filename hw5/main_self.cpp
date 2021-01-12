#include "UnrolledLL.h"

#include <iostream>


template <class T>

void print(list_iterator<T> itr)

{
    
    std::cout << *itr << std::endl;
    
}

int main()

{
    UnrolledLL <int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    l.push_back(6);
    l.push_back(7);
    l.push_back(8);
    l.print(std::cout);

    l.push_front(1);
    l.push_front(2);
    l.push_front(3);
    l.push_front(4);
    l.push_front(5);
    l.push_front(6);
    l.push_front(7);
    l.push_front(8);
    l.push_front(9);
    l.push_front(10);
    l.push_front(11);
    l.print(std::cout);

    l.pop_front();
    l.pop_back();
    l.pop_back();
    l.print(std::cout);

    std::cout << "wo men kai shi la!" << std::endl;
    list_iterator<int> itr = l.begin();
    itr = l.insert(itr,5);
    itr = l.insert(itr,6);
    itr = l.insert(itr,1);
    itr = l.insert(itr,1);
    l.print(std::cout);


    itr = l.erase(itr);
    itr = l.erase(itr);
    l.print(std::cout);
}

