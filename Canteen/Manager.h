#ifndef MANAGER_H
#define MANAGER_H
#include "Person.h"
#include <string>
#include <vector>
using namespace std;

class Manager:public Person {
private:
    string auth;
    string department;
public:
    Manager();
    Manager(int no, string name, string pwd, string auth, string department):
        Person(no, name, pwd),
        auth(auth),
        department(department)
    {

    };
    Manager(string name,  string pwd);
    string getName() {return name;};
    string getPwd() {return pwd;};
    int getNo() {return no;};
    string getAuth() {return auth;};
    string getDepartment() {return department;};
    bool isExist();
    void changePwd();
    void setPwd(string pwd) {this->pwd = pwd;};

    static vector<Manager> managerList;
    static vector<Manager> readManager(string fileName);
    static void writeManager(string filename);
};
#endif // MANAGER_H

