#include <iostream>
#include "hw2.h"
#include <fstream>
#include<vector>
#include<cstring>

using namespace std;

Schedule::Schedule(string crn_num, string depCode, string couCode, string couTitle, string days, string startTime, string endTime, string room_num)
{
    crn_num = crn_num;
    dep_code = depCode,
    cou_code = couCode,
    cou_title = couTitle;
    day = days;
    start_time = startTime;
    end_time = endTime;
    room = room_num;
}

string Schedule::getCrn() const
{
    return crn_num;
}

string Schedule::getDepCode() const
{
    return dep_code;
}

string Schedule::getCouCode() const
{
    return cou_code;
}

string Schedule::getCouTitle() const
{
    return cou_title;
}

string Schedule::getDay() const
{
    return day;
}

string Schedule::getStartTime() const
{
    return start_time;
}

string Schedule::getEndTime() const
{
    return end_time;
}

string Schedule::getRoom() const
{
    return room;
}
