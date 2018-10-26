#ifndef MANAGER_H
#define MANAGER_H
#include "Person.h"
#include <string>
#include <vector>
using namespace std;

class Manager:public Person {
private:
    string type;
    string department;
public:
    Manager();
    Manager(int no, string name, string pwd, string type, string department):
        Person(no, name, pwd),
        type(type),
        department(department)
    {

    };
    Manager(string name,  string pwd): Person(name, pwd) {};
    string getName() {return name;};
    string getPwd() {return pwd;};
    int getNo() {return no;};
    string getType() {return type;};
    string getDepartment() {return department;};
    bool isExist();
    void changePwd();

    static vector<Manager> managerList;
    static vector<Manager> readManager(string fileName);
    static void writeManager(string filename);
};
#endif // MANAGER_H
