#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

struct Course {     //course with a course number, title, and a list of prerequisites
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

class CourseManager {
private:
    unordered_map<string, Course> courseTable; //hashtable declared here as unordered map

public:
    void loadDataStructure(const string & filename) {
        ifstream file("Courses.txt");        //input file stream and opens file that is declared in the filename parameter

        if (!file.is_open()) {
            cerr << "Cannot open file!\n";   //cerr allows immediate feedback with no buffer.
            return;
        }

        string line;
        while (getline(file, line)) {    //getline() is used to read a line of text from an input file stream... works using <string> header
            Course course = parseCourseData(line);         //called parseCourseData function is called to convert (line) into (course)
            courseTable[course.courseNumber] = course;     // The key is the courseNumber and the value is the Course object
        }

        cout << "Data loaded!\n";
        file.close();
    }

    void printCourseList() {
        vector<Course> courses;
        for (const auto& pair : courseTable) {   //constant reference to a key-value pair within the courses table and extracts pair.second from each pair and adds to vector
            courses.push_back(pair.second);
        }
        sort(courses.begin(), courses.end(),    //lambda defines sorting order
            [](const Course& a, const Course& b) {
                return a.courseNumber < b.courseNumber;     //aplphanumeric order based on courseNumber
            });
        cout << "Course List\n";
        for (const auto& course : courses) {
            cout << course.courseNumber << " - " << course.courseTitle << "\n";  // using << endl; flushes output buffer and immediatly outputs however using \n is better when endl is not needed
        }
    }

    void printCourseInfo(const string& courseNumber) {
        auto iterator = courseTable.find(courseNumber);
        if (iterator != courseTable.end()) {
            const Course& course = iterator->second;    //iterator->second retrieves the "second" member of the key-value pair pointed to by iterator

            cout << "Course Number: " << course.courseNumber << "\n";
            cout << "Course Title: " << course.courseTitle << "\n";
            if (!course.prerequisites.empty()) {
                cout << "Prerequisites: ";
                for (const auto& prereq : course.prerequisites) {   //iterates over each prereq in the prerequisites vector
                    cout << prereq << " ";
                }
                cout << "\n";
            }
        }
        else {
            cerr << "Error: Course not found.\n";
        }
    }

private:
    Course parseCourseData(const string& line) {    //converts a line of text into a structured Course object.
        istringstream iss(line);     //variable name iss = making line a stream which makes it easier to extract values
        iss >> ws;
        Course course;            //holds extracted values

        getline(iss, course.courseNumber, ',');       //extracts string until it reaches a comma within course object and stores in cNumber
        getline(iss, course.courseTitle, ',');        //extracts string until it reaches a comma within course object and stores in cTitle

        string prereq;
        while (getline(iss, prereq, ',')) {      //extracts string until it reaches a comma within course object and stores in prereq if vector isnt empty
            if (!prereq.empty()) {
                course.prerequisites.push_back(prereq);          
            }
        }

        return course;
    }
};


int main() {
    CourseManager courseManager;
    string filename = "Courses.txt";
    string courseNumber;

    while (true) {
        cout << "------Course Planner------\n";
        cout << "1. Load Data Structure\n";
        cout << "2. Print Course List\n";
        cout << "3. Print Course\n";
        cout << "4. Exit\n";
        cout << "Which option would you like?\n";

        int choice;
        cin >> choice;



        switch (choice) {
            case 1:
                cout << "Enter the file name: ";
                cin >> filename;
                courseManager.loadDataStructure(filename);
                break;
            case 2:
                courseManager.printCourseList();
                break;
            case 3:
                cout << "What course do you want to know about? ";
                cin >> courseNumber;
                courseManager.printCourseInfo(courseNumber);
                break;
            case 4:
                cout << "Exiting program...\n";
                return 0;
            default:
                cerr << "Error: " << choice << " is not a valid option. Please try again.\n";
        }
    }
    

        return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
