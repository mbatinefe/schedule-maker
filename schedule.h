// MUSTAFA BATIN EFE - 29272

#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <string>
using namespace std;

enum Days {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};

class Schedule
{
private:
    int time_slots;
    string** data;
public:

    int getNum() const; // for free members to get private time_slot values
    string** getData() const;// for free members to get private data values
    void clearVector (); // It will clear the content of the matrix vector

    Schedule (); // default constructor
    Schedule(int timeSlots); // paramedic constructor
    Schedule(const Schedule & copy); // deepcopy constructor
    ~Schedule();   // destructor

    const Schedule & operator = (const Schedule & rhs); // It will assign right to left side
    Schedule operator+(const Days & rhs) const; // It will get Days object as rhs, Schedule object as lhs
    Schedule operator+(int rhs) const; // It will take int rhs, Schedule object as lhs; and it will return Schedule object
    Schedule operator+(const Schedule & rhs) const; // It will take both rhs and lhs as Schedule object; create and return Schedule object
    Schedule operator*(const Schedule &rhs) const; // It will create and return Schedule object
    string* operator[](Days day) const; //It will give the dayTH row

};
string enumToString(Days day); // It will convert enum to string
bool operator< (const Schedule &lhs, const Schedule &rhs); // It will compare rhs and lhs
ostream & operator<<(ostream &os, const Schedule &schedule); // It will give to the os if rhs is Schedule object
ostream & operator<<(ostream &os, const Days &day); // It will give to the os if rhs is Days object

#endif //SCHEDULE_H
