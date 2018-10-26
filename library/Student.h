#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <vector>
#include "Person.h"
using namespace std;

class Student: public Person{
private:
    string major;
    string className;
    int num;
    vector<string> bnoList;

public:
    Student();
    Student(string major, string className, int num, vector<string> bnoList);
    Student(int no, string name, string pwd, string major, string className, int num, vector<string> bnoList);
    Student(string name, string pwd);
    bool isExist();
    string getName();
    string getPwd();
    int getNo() {return no;};
    int getNum() {return num;};
    vector<string> getBnoList() {return bnoList;};
    string getMajor() {return major;};
    string getClassname() {return className;};
    void changePwd();
    void borrowBook();
    void returnBook();
    void setPwd(string pwd) {this->pwd = pwd;};
    void addBno(string bno) {bnoList.push_back(bno);};
    void setNum(int num) {this->num = num;};
    void deleteBno(string bno);

    static vector<Student> studentList;
    static vector<Student> readStudent(string fileName);
    static void addStudent();
    static void updateStudent();
    static void searchStudent();
    static void searchStudentBorrow();
    static void deleteStudent();
    static void writeStudent(string filename);
};
#endif // STUDENT_H
