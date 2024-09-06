#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

#include "Support.h"

bool compareCourses(const pair<string, double>& a, const pair<string, double>& b) {
    return a.first < b.first;

}

ostream& operator<<(ostream& os, person& p) {
    p.print_personinfo();
    p.print_courseinfo();
    return os;
}

label person::get_type() {
    return type;
}

void faculty::add_course(const string& course) {
    course_list.push_back(course);
}

void faculty::print_personinfo()  {
    /*cout << left << "Name: Dr. " << name << endl;
    cout << left << "Category: " << get_category() << endl;*/

    // Print name and category with proper spacing
    cout << setw(16) << right << "Name: Dr. " << name << endl;
    cout << setw(12) << right << "Category: " << get_category() << endl;
}


void faculty::print_courseinfo()  {

    sort(course_list.begin(), course_list.end());

    for (string course : course_list) {
        cout << setw(12) << right << "Course: " << course;
        cout << endl;
    }
}

void student::add_course(const string& course, double gp) {
    course_list.push_back(make_pair(course, gp));
}

void student::print_personinfo()  {
    cout << setw(12) << right << "Name: " << name << endl;
    cout << setw(12) << right << "Category: " << get_category() << endl;
}



void student::print_courseinfo() {
    

    sort(course_list.begin(), course_list.end(), compareCourses);
    float total = 0;
    int count = 1;

    for (const auto& course : course_list) {
        total += course.second;
        float gpa = total / count;

        cout << "    Course: " << course.first;
        int dots = 28 - course.first.length();

        for (int i = 0; i < dots; i++) {
            cout << '.';
        }

        cout << " " << fixed << setprecision(2) << course.second << " " << gpa << endl;
        count++;
    }

    
}

string person::get_category() const{


    string out = " ";

    switch(category) {
        case ASST_PROF:
            out = "Assistant Professor";
            return out;
            break;
        case ASSOC_PROF:
            out = "Associate Professor";
            return out;
            break;
        case PROFESSOR:
            out = "Professor";
            return out;
            break;
        case FRESHMAN:
            out = "Freshman";
            return out;
            break;
        case SOPHOMORE:
            out = "Sophomore";
            return out;
            break;
        case JUNIOR:
            out = "Junior";
            return out;
            break;
        case SENIOR:
            out = "Senior";
            return out;
            break;
        default:
            out = "IDK";
            return out;
            break;     
        
    }
}