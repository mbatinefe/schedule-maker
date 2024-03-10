// MUSTAFA BATIN EFE - 29272

#include "schedule.h"
#include "string"
#include "vector"
#include <iostream>

/* Begin: code taken and update from ptrs_staticarrays.cpp*/
/* Following is "=" operator overloading returns de-ref updated LHS data pointer
 * It will get both as Schedule objects*/
const Schedule & Schedule::operator=(const Schedule &rhs) {
    if(this != &rhs) { // If its equal no need to assign rhs to lhs
        this->clearVector(); // clear lhs first to make sure its empty
        data = new string*[7]; // 7 rows
        for(int m = 0; m < 7; m++){
            /* For each row create col as number of time slots */
            data[m] = new string[rhs.time_slots];
            for (int q = 0; q < rhs.time_slots; q++){
                if(rhs.data[m][q] == "busy") { // if RHS busy
                    data[m][q] = "busy"; // assign as busy
                } else{
                    data[m][q] = "free"; // assign as free
                }
            }
        }
        this->time_slots = rhs.time_slots; // in the end get RHS time slot data to LHS
    }
    // return de-referenced data pointer
    return *this;
}
/* End: code taken and update from ptrs_staticarrays.cpp*/

// Following function clears the inside of the 2D dynamic array and reset time_slots
void Schedule::clearVector() {

    for(int y = 0; y < 7; y++){
        // Delete each row
        delete[] data[y];
    }
    delete[] data; // Delete itself
    time_slots = 0;
}

/* Begin: code taken and update from ptrs_staticarrays.cpp*/
Schedule::Schedule() { // default constructor
    time_slots = 0; // set time slot number

    data = new string*[7]; // 7 rows
    for(int m = 0; m < 7; m++){
        data[m] = nullptr; // set all elements to null
    }
}
/* End: code taken and update from ptrs_staticarrays.cpp*/

/* Begin: code taken and update from MathVector.cpp*/
Schedule::Schedule(int timeSlots) { // paramedic constructor
    time_slots = timeSlots; // set the number of slots going to be created

    data = new string*[7]; // 7 rows
    for(int m = 0; m < 7; m++){
        /* For each row create col as number of time slots */
        data[m] = new string[time_slots];
        for (int q = 0; q < time_slots; q++){
            // Set each one as "free"
            data[m][q] = "free";
        }
    }
}
/* End: code taken and update from MathVector.cpp*/

/* Begin: code taken and update from MathVector.cpp*/

Schedule::Schedule(const Schedule & copy) { // copy constructor
    time_slots = copy.time_slots; // set rhs time slot num to lhs
    data = new string*[7]; // 7 rows
    for(int m = 0; m < 7; m++){
        /* For each row create col as number of time slots */
        data[m] = new string[time_slots]; // columns
        for (int q = 0; q < time_slots; q++){
            if(copy.data[m][q] == "busy") {
                // If rhs is busy, this will be busy
                data[m][q] = "busy";
            } else{
                // If rhs is free, this will be free
                data[m][q] = "free";
            }
        }
    }
}
/* End: code taken and update from MathVector.cpp*/

/* Following de constructor deletes the 2D dynamic array and reset time_slots*/
Schedule::~Schedule() {
    for (int m = 0; m < 7; m++) {
        // delete each row
        delete[] data[m];
    }
    delete[] data; // delete itself
    time_slots = 0;
}

/* Following "[]" operator overloading will return dayTH row of this */
string* Schedule::operator[](Days day) const{
    return data[day];
}

/* Begin: code taken and update from MathVector.cpp*/
/* Following "+" operator overloading will return Schedule Object
 * It will get Days object as rhs, lhs as Schedule object*/
Schedule Schedule::operator+(const Days &rhs) const {
    Schedule temp(time_slots); // Create a new Schedule Object with all FREE slots
    for(int m =0; m < 7; m++){
        for(int y = 0; y < time_slots; y++) {
            if(Days(m) == rhs) { // If given day is equal to wanted day
                temp.data[m][y] = "busy"; // set as busy
            }
        }
    }
    return temp; // return schedule object
}
/* End: code taken and update from MathVector.cpp*/

/* Following "+" operator overloading will return Schedule Object
 * It will get rhs as integer, lhs as Schedule object*/
Schedule Schedule::operator+(int rhs) const {
    Schedule temp(time_slots); // create temp with "free" slots with lhs time slot num
    for(int m =0; m < 7; m++){
        for(int y = 0; y < time_slots; y++) {
            // If the day matches with rhs (asked), or lhs is busy
            if(y == rhs || this->data[m][y] == "busy") {
                temp.data[m][y] = "busy"; // change temp's [m][y] with busy
            }
        }
    }
    return temp; // return Schedule Object
}

/* Begin: code taken and update from MathVector.cpp*/
/* Following "+" operator overloading will return Schedule Object
 * It will take both rhs and lhs as Schedule object*/
Schedule Schedule::operator+(const Schedule &rhs) const {
    Schedule temp(time_slots); // create temp with "free" slots with lhs time slot num
    for(int m =0; m < 7; m++){
        for(int y = 0; y < time_slots; y++) {
            // If rhs is busy or lhs is busy
            if(rhs.data[m][y] != "free" || this->data[m][y] != "free") {
                temp.data[m][y] = "busy"; // set temp as busy as well
            }
        }
    }
    return temp;
}
/* End: code taken and update from MathVector.cpp*/

/* Following "*" operator overloading will return Schedule Object
 * It will get rhs as Schedule object, Schedule object as lhs*/
Schedule Schedule::operator*(const Schedule &rhs) const {
    Schedule temp(time_slots); // create temp with lhs time slot number
    for(int m =0; m < 7; m++){
        for(int y = 0; y < time_slots; y++) {
            if(rhs.data[m][y] == "busy" && this->data[m][y] == "busy") {
                // If both of them busy, common temp will be busy
                temp.data[m][y] = "busy";
            }
        }
    }
    return temp;
}

/* Following "<" FREE operator overloading function will return TRUE/FALSE
 * It will get rhs as Schedule object, lhs as Schedule object*/
bool operator<(const Schedule &lhs, const Schedule &rhs) {

    // getData will help to access private data
    // getNum will help to access private time_slot values
    int countLHS = 0; int countRHS =0;
    string** lhsDATA = lhs.getData(); // get lhs data
    int lhsSLOT = lhs.getNum(); // get lhs time slot
    string** rhsDATA = rhs.getData(); // get rhs data
    int rhsSLOT = rhs.getNum(); // get rhs time slot

    // Find number of busy days in LHS
    for(int m =0; m < 7; m++){
        for(int y = 0; y < lhsSLOT; y++) {
            if(lhsDATA[m][y] == "busy") {
                countLHS++;
            }
        }
    }
    // Find number of busy days in RHS
    for(int m =0; m < 7; m++){
        for(int y = 0; y < rhsSLOT; y++) {
            if(rhsDATA[m][y] == "busy" ) {
                countRHS++;
            }
        }
    }

    // Compare and return true if RHS is more busy than LHS
    if(countLHS < countRHS){
        return true;
    } else {
        return false;
    }
}
/* Begin: code taken and update from ComplexNumber.cpp*/
int Schedule::getNum() const {
    // access private time slot for free members
    return time_slots;
}

string **Schedule::getData() const {
    // access private data for free members
    return data;
}
/* End: code taken and update from ComplexNumber.cpp*/

/* Following "<<" FREE operator overloading function will return ostream
 * It will get Ostream and Days object  */
ostream & operator<<(ostream &os, const Days &day){
    if(day == Monday){
        os << "Monday";
    }
    else if(day == Tuesday) {
        os << "Tuesday";
    }
    else if(day == Wednesday) {
        os << "Wednesday";
    }
    else if(day == Thursday) {
        os << "Thursday";
    }
    else if(day == Friday) {
        os << "Friday";
    }
    else if(day == Saturday) {
        os << "Saturday";
    }
    else if(day == Sunday) {
        os << "Sunday";
    }

    return os;
}

/* Following function will return string, it helps to "<<" overloading to set abbreviation of Days day object
 * It will get Days object*/
string enumToString(Days day){
    if(day == Monday){
        return "Mo: ";
    }
    else if(day == Tuesday) {
        return "Tu: ";
    }
    else if(day == Wednesday) {
        return "We: ";
    }
    else if(day == Thursday) {
        return "Th: ";
    }
    else if(day == Friday) {
        return "Fr: ";
    }
    else if(day == Saturday) {
        return "Sa: ";
    }
    else {
        return "Su: ";
    }

}

/* Following "<<" FREE operator overloading function will return ostream
 * It will get ostream and Schedule object*/
ostream & operator << (ostream &os, const Schedule &schedule){
    string **data2 = schedule.getData(); // access private data
    int dataNum = schedule.getNum(); // access private slot number

    for (int j = 0; j < 7; j++) // assuming 7 days in a week
    {
        os << enumToString(Days(j)); // get the abbreviation for that day and store in os
        for (int i = 0; i < dataNum; i++)
        {
            // Store the data in os
            os << data2[j][i] << " ";
        }
        os << endl;
    }
    // return os
    return os;
}



