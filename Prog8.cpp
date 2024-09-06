#include <vector>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#include "Support.h"

int main(int argc, char *argv[]) {
  //handle commandline options
  if (argc > 3) {
    cerr << "usage" << endl;
    return 1;
  }
  string filename = argv[argc - 1];
  string mode = argv[1];

  if (mode != "-person" && mode != "-faculty" && mode != "-student") {
    cerr << "usage: " << argv[0] << " -person|faculty|student file.xml" << endl;
    return 1;
  }


  person *n_person;
  vector<person *> person_list;
  vector<string> course_list;
  vector<float> gp_list;

  label type = UNKNOWN;
  label category = UNKNOWN;
  string category_str;
  string name;

  int line = 1;
  string input;
  int counter = 0;

  ifstream fin(filename);
  if (!fin.is_open()) {
    cerr << "Error: unable to open input file." << endl;
    return 1;
  }

  /*if (input.find("<?XML version=\"1.0\" encode=\"ASCII\"?>") == string::npos) {
      cerr << "line " << line << ": XML declaration missing" << endl;
      return 1;
    }*/

  while (getline(fin, input)) {
    ++line;

    if (input.find("<") == string::npos) {
	    continue;

    } else if (input.find("<faculty>") != string::npos) {
      //set type FACULTY
      type = FACULTY;
      //clear course_list
      course_list.clear();

    } else if (input.find("/faculty") != string::npos) {
      //error check: type FACULTY?
      if (type != FACULTY) {
        cerr << "line 19: expected </student> tag" << endl;
        return 1;
      }

        if (category_str == "Assistant Professor") {
          category = ASST_PROF;
        }
        else if (category_str == "Associate Professor") {
          category = ASSOC_PROF;
        }
        else if (category_str == "Professor") {
          category = PROFESSOR;
        }

      //create n_person FACULTY object 
      n_person = new faculty(name, type, category);
	    //add courses from course_list
      for (auto& course : course_list) {
          dynamic_cast<faculty *>(n_person)->add_course(course);
      }

      //add n_person to person_list
      person_list.push_back(n_person);

      type = UNKNOWN;
      category = UNKNOWN;

    } else if (input.find("<student>") != string::npos) {
        type = STUDENT;

        course_list.clear();
        gp_list.clear();

    } else if (input.find("</student>") != string::npos) {
        if (type != STUDENT) {
          cerr << "line 36: expected <person-type> tag" << endl;
          return 1;
        }

        if (category_str == "Freshman") {
          category = FRESHMAN;
        }
        else if (category_str == "Sophomore") {
          category = SOPHOMORE;
        }
        else if (category_str == "Junior") {
          category = JUNIOR;
        }
        else if (category_str == "Senior") {
          category = SENIOR;
        }

        n_person = new student(name, type, category);
        for (size_t i = 0; i < course_list.size(); i++) {
          dynamic_cast<student *>(n_person)->add_course(course_list[i], gp_list[i]);
        }

        person_list.push_back(n_person);

        type = UNKNOWN;
        category = UNKNOWN;

    } else if (input.find("<name") != string::npos) {
        size_t start = input.find("\"") + 1;
        size_t end = input.find("\"", start);

        name = input.substr(start, end - start);

    } else if (input.find("<category") != string::npos) {
        size_t start = input.find("\"") + 1;
        size_t end = input.find("\"", start);
        category_str = input.substr(start, end - start);
        
        //ASST_PROF=11, ASSOC_PROF=12, PROFESSOR=13,
        //     STUDENT=20, FRESHMAN=21, SOPHOMORE=22, JUNIOR=23, SENIOR=24

        if (input.find("/>") == string::npos) {
          
          cerr << "line 5: category missing/not terminated" << endl;
          return 1;
          }
        


    } else if (input.find("<course") != string::npos) {
        size_t start = input.find("\"") + 1;
        size_t end = input.find("\"", start);
        string course = input.substr(start, end - start);


        course_list.push_back(course);

        if (type == STUDENT) {
          size_t gp_start = input.find("gp=\"") + 4;
          size_t gp_end = input.find("\"", gp_start);
          string gp_string = input.substr(gp_start, gp_end - gp_start);
          double gp = stod(gp_string);


          gp_list.push_back(gp);
        }
	  
        if (input.find("/>") == string::npos) {
          cerr << "line 33: course gp missing/not terminated" << endl;
          return 1;
        }
    }
    
  }

  if (mode == "-person") {
    sort(person_list.begin(), person_list.end(), [](person *a, person *b) {return *a < *b;});  
    for (person *p : person_list) {
      cout << *p << endl;
    }
	
  }
  else if (mode == "-faculty") {

    vector <faculty *> f_list;

    for (person *p : person_list) {
      if (p->get_type() == FACULTY) {
        f_list.push_back(dynamic_cast<faculty *>(p));
      }
    }
 
    sort(f_list.begin(), f_list.end(), [](faculty *a, faculty *b) {return *a < *b;});

    for (faculty *f : f_list) {
      cout << *f << endl;
    }
  } 
  else if (mode == "-student") {
    vector <student *> s_list;
	
    for (person *p : person_list) {
      if (p->get_type() == STUDENT) {
        s_list.push_back(dynamic_cast<student *>(p));
      }
    }

    sort(s_list.begin(), s_list.end(), [](student *a, student *b) {return *a < *b;});

    for (student *s : s_list) {
      cout << *s << endl;
    }
  }

  for (person *p : person_list) {
    delete p; 
  }
}
