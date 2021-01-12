#include <iostream>
#include<cstdlib>
#include <string>
#include<cstring>
using namespace std;
class Time
{
public:
    Time();
    Time(int hour, int minute, int second);
    
    int getHour() const;
    int getMinute() const;
    int getSecond() const;
    
    void setHour(const int aHour);
    void setMinute(int aMinute);
    void setSecond(int aSecond);

    bool IsAmPm(const Time& t);
    void print();
    
private:
    int hour;
    int minute;
    int second;
    
    
    
};

