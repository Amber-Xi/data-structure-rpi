#include <iostream>
#include<cstdlib>
#include "lab2.h"
#include <string>
#include<cstring>
#include<vector>

using namespace std;
bool Earlier(const Time& t1, const Time& t2);

bool Earlier(const Time& t1, const Time& t2)
{
    return t1.getHour() < t2.getHour() || (t1.getHour() == t2.getHour() && t1.getMinute() < t2.getMinute()) || (t1.getHour() == t2.getHour() && t1.getMinute() == t2.getMinute() && t1.getSecond() < t2.getSecond());
}
int main()
{
    vector<Time> t;
    
    Time now(14,5,6);
    t.push_back(now);
    
    Time later(9,4,5);
    t.push_back(later);
    
    sort(t.begin(), t.end(), Earlier);
    for(int i =0; i< t.size(); i++)
    {
        t[i].print();
    }
    
    return 0;
}
