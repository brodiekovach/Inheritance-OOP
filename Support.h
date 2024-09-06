#ifndef __SUPPORT_H__ 
#define __SUPPORT_H__

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

enum label { UNKNOWN=-1, PERSON=0,
             FACULTY=10, ASST_PROF=11, ASSOC_PROF=12, PROFESSOR=13,
             STUDENT=20, FRESHMAN=21, SOPHOMORE=22, JUNIOR=23, SENIOR=24 };

class person {
    friend ostream& operator<<(ostream& os, person& p);

    public:

        person(const string& name, label type, label category) : name(name), type(type), category(category) {} 

        virtual ~person() {}
        

        bool operator<(const person& other) const {

            if (type < other.type) {
                return true;
            }
            else if (other.type < type ) {
                return false;
            }
            
            return name < other.name;
            
        }

        label get_type();
        string get_category() const;

        string name;
        label type;
        label category;    

        
        virtual void print_personinfo() = 0;
        virtual void print_courseinfo() = 0;    

    protected:


        //virtual void print_personinfo() = 0;
        //virtual void print_courseinfo() = 0;
};      

class faculty : public person {

    public:

        faculty(const string& name, label category, label type) : person(name, category, type) {}

        bool operator<(const faculty& other) const {
            if (category > other.category) {
                return true;
            }
            else if (category < other.category) {
                return false;
            }

            return name < other.name;
        }

       

        void add_course(const string& course);

    private:

        void print_personinfo()  ;
        void print_courseinfo()  ;

        vector<string> course_list;
};

class student : public person {

    public:

        student(const string& name, label category, label type) : person(name, category, type) {}

        bool operator<(const student& other) const {
            
            if (category < other.category) {
                return true;
            }
            else if (category > other.category) {
                return false;
            }
            return name < other.name;
        }

        
        
        void add_course(const string& course, double gp);

    private:

        void print_personinfo()  ;
        void print_courseinfo()  ;

        vector<pair<string, double>> course_list;
};

#endif

