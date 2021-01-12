
using namespace std;
class Schedule
{
public:
    Schedule();
    Schedule(string crn_num, string depCode, string couCode, string couTitle, string day, string startTime, string endTime, string room_num);
    string getCrn() const;
    string getDepCode() const;
    string getCouCode() const;
    string getCouTitle() const;
    string getDay() const;
    string getStartTime() const;
    string getEndTime() const;
    string getRoom() const;

private:
    string crn_num;
    string dep_code;
    string cou_code;
    string cou_title;
    string day;
    string start_time;
    string end_time;
    string room;
};
