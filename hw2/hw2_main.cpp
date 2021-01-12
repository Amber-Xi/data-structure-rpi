#include <iostream>
#include <fstream>
#include<vector>
#include<string>
#include "hw2.h"
#include<cstdlib>
#include<cstring>
#include <algorithm>

using namespace std;
vector<string> check_days(string s);
int convert_day(string a);
int convert_time(string a);
bool earlier_course_room(const Schedule s1, const Schedule s2);
bool earlier_course_dep(const Schedule s1, const Schedule s2);
int max(vector<string> s);

vector<string> check_days(string s)
{
    /*
     This function is for converting the day char to the full name;
     */
    vector<string> day_group;
    for(int i = 0; i<s.size(); i++)
    {
        if(s[i] == 'M')
        {
            day_group.push_back("Monday");
        }
        else if(s[i] == 'T')
        {
            day_group.push_back("Tuesday");
        }
        else if(s[i] == 'W')
        {
            day_group.push_back("Wednesday");
        }
        else if(s[i] == 'R')
        {
            day_group.push_back("Thursday");
        }
        else if(s[i] == 'F')
        {
            day_group.push_back("Friday");
        }
    }
    return day_group;
}

int convert_day(string a)
{
    /*
     This function is for converting the weekday to number;
     */
    if(a == "Monday")
    {
        return 0;
    }
    else if(a == "Tuesday")
    {
        return 1;
    }
    else if(a == "Wednesday")
    {
        return 2;
    }
    else if(a == "Thursday")
    {
        return 3;
    }
    else if(a == "Friday")
    {
        return 4;
    }
    return 0;
}
int convert_time(string a)
{
    /*
     This function is for convering the time to 24-hour scale.
     */
    if((a[a.size()-2] =='P' && a.substr(0,2) == "12") || (a[a.size()-2] == 'A'))
    {
        return stoi(a.substr(0,2));
    }
    else if(a[a.size()-2] == 'P')
    {
        return stoi(a.substr(0,2))+12;
    }
    return 0;
 
}
bool earlier_course_room(const Schedule s1, const Schedule s2)
{
    /*
     This function is for comparing the course's time when the command is "room".
     */
    int day1 = convert_day(s1.getDay());
    int day2 = convert_day(s2.getDay());
    int time1 = convert_time(s1.getStartTime());
    int time2 = convert_time(s2.getStartTime());
    return (s1.getRoom() < s2.getRoom()) ||
    (s1.getRoom() == s2.getRoom() && day1<day2) ||
    (s1.getRoom() == s2.getRoom() && day1 == day2 && time1 < time2) ||
    (s1.getRoom() == s2.getRoom() && day1 == day2 && time1 == time2 && s1.getCouCode() < s2.getCouCode()) ||
    (s1.getRoom() == s2.getRoom() && day1 == day2 && time1 == time2 && s1.getCouCode() == s2.getCouCode() && s1.getDepCode() < s2.getDepCode());
}

bool earlier_course_dep(const Schedule s1, const Schedule s2)
{
    /*
     This function is for comparing the course's time when the command is "dept".
     */
    int day1 = convert_day(s1.getDay());
    int day2 = convert_day(s2.getDay());
    int time1 = convert_time(s1.getStartTime());
    int time2 = convert_time(s2.getStartTime());
    return (s1.getCouCode() < s2.getCouCode()) || (s1.getCouCode() == s2.getCouCode() && day1 < day2) || (s1.getCouCode() == s2.getCouCode() && day1 == day2 && time1 < time2);
}

int max_length(vector<string> s)
{
    /*
     This function is for checking the max length when printing the time grid.
     */
    int max_l = 0;
    for(int i =0; i<s.size(); i++)
    {
        if(max_l<s[i].size())
            max_l = s[i].size();
    }
    return max_l;
}


int main(int argc, char *argv[])
{
    ifstream filein(argv[1]);
    ofstream fileout(argv[2]);
    string crn_num;
    string dep_code;
    string cou_code;
    string cou_title;
    string day;
    string start_time;
    string end_time;
    string room;
    
    vector<Schedule> all_courses;
    // When the file is good, open and read.
    if(filein.good())
    {
        
        while(filein >> crn_num >> dep_code >> cou_code >> cou_title >> day >> start_time >> end_time >> room)
        {
            vector<string> all_days = check_days(day);
            for(int i = 0; i<all_days.size(); i++)
            {
                // Constructing the Schduel class.
                string str_day = all_days[i];
                Schedule course(crn_num, dep_code, cou_code, cou_title, str_day, start_time, end_time, room);
                all_courses.push_back(course);
            }
        }
        if(all_courses.size()!= 0)
        {
            // Running when the third argument is "room".
            if(strcmp(argv[3],"room")==0)
            {
                vector<string> courses_num;
                vector<string> courses_title;
                vector<string> courses_day;
                vector<string> courses_dept;
                sort(all_courses.begin(), all_courses.end(), earlier_course_room);
                vector<string> all_kinds;
                
                int i = 0;
                while(i< all_courses.size())
                {
                    // Getting all courses into a collection.
                    if(all_courses[i].getRoom() != all_courses[i+1].getRoom())
                    {all_kinds.push_back(all_courses[i].getRoom());}
                    i++;
                  
                }
                sort(all_kinds.begin(), all_kinds.end());
                
                for(int i = 0; i<all_kinds.size(); i++)
                {
                    vector<string> courses_num;
                    vector<string> courses_title;
                    vector<string> courses_day;
                    vector<string> courses_dept;
                    vector<Schedule> selected_courses;
                    fileout << "Room " << all_kinds[i]<< endl;
                    
                    for(int j = 0; j<all_courses.size(); j++)
                    {
                        if(all_kinds[i] == all_courses[j].getRoom())
                        {
                            selected_courses.push_back(all_courses[j]);
                        }

                    }
                    for(int a = 0; a<selected_courses.size(); a++)
                    {
                        courses_num.push_back(selected_courses[a].getCouCode());
                        courses_title.push_back(selected_courses[a].getCouTitle());
                        courses_day.push_back(selected_courses[a].getDay());
                        courses_dept.push_back(selected_courses[a].getDepCode());
                    }
                    // finding the max length of course number, title, day and dept.
                    int max_courses_num = max_length(courses_num);
                    int max_courses_title = max_length(courses_title);
                    int max_courses_day = max_length(courses_day);
                    int max_courses_dept = max_length(courses_dept);
                    
                    string s1, s2, s3;
                    // print the format.
                    if(max_courses_title < 11)
                    {s1 = "Class Title  "; s2 = "-----------";}
                    else
                    {s1 = "Class Title" + string(max_courses_title-9,' ');s2= string(max_courses_title, '-');}
                    
                    if(max_courses_num < 9 || max_courses_num == 9)
                    {
                        fileout << "Dept" << string((max_courses_dept - 2),' ') << "Coursenum" << string(2,' ') << s1 << "Day" << string(max_courses_day-1, ' ') << "Start Time  End Time" << endl;
                        fileout << string(max_courses_dept,'-')<< "  " << string(9,'-') << "  " << s2 << "  " << string(max_courses_day,'-') << "  " << "----------  --------" << endl;
                    }
                    else if(max_courses_num > 9)
                    {
                        fileout << "Dept" << string((max_courses_dept - 2),' ') << "Coursenum" << string((max_courses_num - 7),' ') << s1 << string(max_courses_title-9, ' ') << "Day" << string(max_courses_day-1, ' ') << "Start Time  End Time" << endl;
                        fileout << string(max_courses_dept,'-')<< "  " << string(max_courses_num,'-') << "  " <<s2 << "  " << string(max_courses_day,'-') << "  " << "----------  --------" << endl;
                    }
                    for(int j =0; j< selected_courses.size(); j++)
                    {
                        if(max_courses_title < 11)
                        {s3= string(13-max_courses_title, ' ');}
                        else
                        {s3= string(max_courses_title-selected_courses[j].getCouTitle().size()+2, ' ');}
                        if(max_courses_num < 9 || max_courses_num == 9)
                        {
                            fileout << selected_courses[j].getDepCode() << string(max_courses_dept- selected_courses[j].getDepCode().size()+2, ' ') << selected_courses[j].getCouCode() << string(11-selected_courses[j].getCouCode().size(), ' ') << selected_courses[j].getCouTitle() << s3 << selected_courses[j].getDay() << string(max_courses_day-selected_courses[j].getDay().size()+2, ' ') << selected_courses[j].getStartTime() << "     " << selected_courses[j].getEndTime() << ' ' <<endl;
                        }
                        else if(max_courses_num > 9)
                        {
                            fileout << selected_courses[j].getDepCode() << string(max_courses_dept- selected_courses[j].getDepCode().size()+2, ' ') << selected_courses[j].getCouCode() << string(max_courses_num-selected_courses[j].getCouCode().size()+2, ' ') << selected_courses[j].getCouTitle() << s3 << selected_courses[j].getDay() << string(max_courses_day-selected_courses[j].getDay().size()+2, ' ') << selected_courses[j].getStartTime() << "     " << selected_courses[j].getEndTime() << ' ' << endl;
                        }
                    }
                    fileout << selected_courses.size() << " entries" << endl << endl;
                }
            }
            // Running when the third argument is "dept".
            else if(strcmp(argv[3],"dept")== 0)
            {
                vector<Schedule> selected_courses;
                vector<string> courses_num;
                vector<string> courses_title;
                vector<string> courses_day;
                vector<string> courses_dept;
                int max_courses_num;
                int max_courses_title;
                int max_courses_day;
                int max_courses_dept;
                
                // putting all the courses satisfying the input commend.
                for(int i = 0; i< all_courses.size(); i++)
                {
                    if(all_courses[i].getDepCode()== argv[4])
                    {
                        selected_courses.push_back(all_courses[i]);
                    }
                }
                if(selected_courses.size()!=0)
                {
                    fileout << "Dept " << argv[4] << endl;
                    for(int j = 0; j<selected_courses.size(); j++)
                    {
                        courses_num.push_back(selected_courses[j].getCouCode());
                        courses_title.push_back(selected_courses[j].getCouTitle());
                        courses_day.push_back(selected_courses[j].getDay());
                        courses_dept.push_back(selected_courses[j].getDepCode());
                    }
                    // finding the max length of course number, title, day and dept.
                    max_courses_num = max_length(courses_num);
                    max_courses_title = max_length(courses_title);
                    max_courses_day = max_length(courses_day);
                    max_courses_dept = max_length(courses_dept);
                    sort(selected_courses.begin(), selected_courses.end(), earlier_course_dep);
                    string s1, s2;
                    
                    // print the format.
                    if(max_courses_title < 11)
                    {s1 = "Class Title  "; s2 = "-----------";}
                    else if (max_courses_title > 11)
                    {s1 = "Class Title" + string(max_courses_title-9,' ');s2= string(max_courses_title, '-');}
                    if(max_courses_num < 9 || max_courses_num == 9)
                    {
                        fileout <<"Coursenum" << string(2,' ') << s1 << "Day" << string(max_courses_day-1, ' ') << "Start Time  End Time" << endl;
                        fileout << string(9,'-') << "  " << s2 << "  " << string(max_courses_day, '-') << "  " << "----------  --------" << endl;
                        for(int i =0; i< selected_courses.size(); i++)
                        {
                            fileout << selected_courses[i].getCouCode() << string(11-selected_courses[i].getCouCode().size(), ' ') << selected_courses[i].getCouTitle() << string(max_courses_title-selected_courses[i].getCouTitle().size()+2, ' ') << selected_courses[i].getDay() << string(max_courses_day-selected_courses[i].getDay().size()+2, ' ') << selected_courses[i].getStartTime() << "     " << selected_courses[i].getEndTime() << ' ' << endl;
                        }
                    }
                    else if(max_courses_num > 9)
                    {
                        fileout << "Coursenum" << string((max_courses_num - 7),' ') << s1 << string(max_courses_title-9, ' ') << "Day" << string(max_courses_day-1, ' ') << "Start Time  End Time" << endl;
                        fileout << string(max_courses_num,'-') << "  " << s2 << "  " << string(max_courses_day,'-') << "  " << "----------  --------" << endl;
                        for(int i =0; i< selected_courses.size(); i++)
                        {
                            fileout <<selected_courses[i].getCouCode() << string(max_courses_num-selected_courses[i].getCouCode().size()+2, ' ') << selected_courses[i].getCouTitle() << string(max_courses_title-selected_courses[i].getCouTitle().size()+2, ' ')<< selected_courses[i].getDay() << string(max_courses_day-selected_courses[i].getDay().size()+2, ' ') << selected_courses[i].getStartTime() << "     " << selected_courses[i].getEndTime() << ' ' <<endl;
                        }
                    }
                    fileout << selected_courses.size() << " entries" << endl << endl;
                }
                else
                {
                    fileout << "No data available.";
                }
            }
            else if(strcmp(argv[3],"custom")== 0)
            {
                // when the command is custom, there should print the category of weekday.
                sort(all_courses.begin(), all_courses.end(), earlier_course_room);
                vector<string> all_kinds;
                all_kinds.push_back("Monday");
                all_kinds.push_back("Tuesday");
                all_kinds.push_back("Wednesday");
                all_kinds.push_back("Thursday");
                all_kinds.push_back("Friday");
                
                for(int i = 0; i<all_kinds.size(); i++)
                {
                    vector<string> courses_num;
                    vector<string> courses_title;
                    vector<string> courses_room;
                    vector<string> courses_dept;

                    vector<Schedule> selected_courses;
                    fileout << "Day " << all_kinds[i]<< endl;
                    for(int j = 0; j<all_courses.size(); j++)
                    {
                        if(all_kinds[i] == all_courses[j].getDay())
                        {
                            selected_courses.push_back(all_courses[j]);
                        }
                        
                    }
                    for(int j = 0; j<selected_courses.size(); j++)
                    {
                        courses_num.push_back(selected_courses[j].getCouCode());
                        courses_title.push_back(selected_courses[j].getCouTitle());
                        courses_room.push_back(selected_courses[j].getRoom());
                        courses_dept.push_back(selected_courses[j].getDepCode());
                    }
                    
                    // finding the max length of course number, title, day and dept.
                    int max_courses_num = max_length(courses_num);
                    int max_courses_title = max_length(courses_title);
                    int max_courses_room = max_length(courses_room);
                    int max_courses_dept = max_length(courses_dept);
                    
                    // print the format
                    string s1, s2, s3;
                    if(max_courses_title < 11)
                    {s1 = "Class Title  "; s2 = "-----------";s3= string(13-max_courses_title, ' ');}
                    else
                    {s1 = "Class Title" + string(max_courses_title-9,' ');s2= string(max_courses_title, '-');s3= string(max_courses_title-selected_courses[i].getCouTitle().size()+2, ' ');}
                    if(max_courses_num < 9 || max_courses_num == 9)
                    {
                        fileout << "Dept" << string((max_courses_dept - 2),' ') << "Coursenum" << string(2,' ') << s1 << string(max_courses_title-9, ' ') << "Start Time  End Time" << "  "<< "Room" << endl;
                        fileout << string(max_courses_dept,'-')<< "  " << string(9,'-') << "  " << s2 << "  " << "----------  --------" << "  " << string(max_courses_room,'-') << endl;
                    }
                    else if(max_courses_num > 9)
                    {
                        fileout << "Dept" << string((max_courses_dept - 2),' ') << "Coursenum" << string((max_courses_num - 7),' ') << s1 << string(max_courses_title-9, ' ') << "Start Time  End Time" << "Room" << endl;
                        fileout << string(max_courses_dept,'-')<< "  " << string(max_courses_num,'-') << "  " << s2 << "  " << "----------  --------" << "  " << string(max_courses_room,'-') << endl;
                    }
                    for(int a =0; a< selected_courses.size(); a++)
                    {
                        if(max_courses_title < 11)
                        {s3= string(13-max_courses_title, ' ');}
                        else
                        {s3= string(max_courses_title-selected_courses[a].getCouTitle().size()+2, ' ');}
                        if(max_courses_num < 9 || max_courses_num == 9)
                        {
                            fileout << selected_courses[a].getDepCode() << string(max_courses_dept- selected_courses[a].getDepCode().size()+2, ' ') << selected_courses[a].getCouCode() << string(11-selected_courses[a].getCouCode().size(), ' ') << selected_courses[a].getCouTitle() << s3 << selected_courses[a].getStartTime() << "     " << selected_courses[a].getEndTime() << "   " << selected_courses[a].getRoom() <<endl;
                        }
                        else if(max_courses_num > 9)
                        {
                            fileout << selected_courses[a].getDepCode() << string(max_courses_dept- selected_courses[a].getDepCode().size()+2, ' ') << selected_courses[a].getCouCode() << string(max_courses_num-selected_courses[a].getCouCode().size()+2, ' ') << selected_courses[a].getCouTitle() << s3 << selected_courses[a].getStartTime() << "     " << selected_courses[a].getEndTime() << "   " << selected_courses[a].getRoom() <<endl;
                        }
                    }
                    fileout << selected_courses.size() << " entries"<< endl;
                    fileout << endl;
                }
            }
        }
        else
            {
                // If there are no courses in the documnet, write the "No data" statement in the file.
                fileout << "No data available.";
            }
        }
    else
        {
            // If the file can't open, print the wrong statement.
            cerr << "Can not open the grades file " << argv[1] << "\n";
        }
    return 0;
    fileout.close();
}
