#include <iostream>
#include<cstdlib>
#include "lab2.h"
#include <string>
#include<cstring>
using namespace std;
Time::Time()
{
    hour = 0;
    minute = 0;
    minute = 0;
}

Time::Time(int ahour, int aminute, int asecond)
{
    hour = ahour;
    minute = aminute;
    second = asecond;
}

int Time::getHour() const
{
    return hour;
}

int Time::getMinute() const
{
    return minute;
}

int Time::getSecond() const
{
    return second;
}

void Time::setHour(int aHour)
{
    hour = aHour;
}
void Time::setMinute(int aMinute)
{
    minute = aMinute;
}
void Time::setSecond(int aSecond)
{
    second = aSecond;
}

bool Time::IsAmPm(const Time& t)
{
    return t.getHour() > 12;
}

void Time::print()
{
    int s_h = 0;
    string s_m, s_s;
    if(getHour() > 12)
    {
        s_h = getHour() - 12;
    }
    else
    {
        s_h = getHour();
    }
    if(getMinute() < 10)
    {
        s_m = '0' + to_string(getMinute());
    }
    else
    {
        s_m = to_string(getMinute());
    }
    
    if(getSecond() < 10)
    {
        s_s = '0' + to_string(getSecond());
    }
    else
    {
        s_s = to_string(getSecond());
    }
    
    if(getHour() >11)
    {
        cout<< s_h << ':' << s_m << ':' << s_s << "PM" << endl;
    }
    else
    {
        cout<< s_h << ':' << s_m << ':' << s_s << "AM" << endl;
    }
}
/*
bool operator< (const Time& t1, const Time& t2)
{
    return t1.getHour() < t2.getHour() || (t1.getHour() == t2.getHour() && t1.getMinute() < t2.getMinute()) || (t1.getHour() == t2.getHour() && t1.getMinute() == t2.getMinute() && t1.getSecond() < t2.getSecond());
}
 */
