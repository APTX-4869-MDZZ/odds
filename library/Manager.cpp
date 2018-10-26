#include "Manager.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

bool Manager::isExist() {
    for (int i = 0; i < managerList.size(); i++) {
        Manager temp = managerList.at(i);
        if (temp.getName() == name && temp.getPwd() == pwd) {
            return true;
        }
    }
    return false;
}

void Manager::changePwd() {
    cout << "请输入新密码：";
    string pwd;
    cin >> pwd;
    this->pwd = pwd;
}

vector<Manager> Manager::managerList = Manager::readManager("manager.txt");

vector<Manager> Manager::readManager(string fileName) {
    vector<Manager> managerList;
    fstream f(fileName.c_str(), ios::in);
    if (f.bad()) {
        cout << "管理员文件打开出错！";
        exit(0);
    }
    while (!f.eof()) {
        int no;
        string name;
        string pwd;
        string type;
        string department;
        f >> no >> name >> pwd >> type >> department;
        Manager manager = Manager(no, name, pwd, type, department);
        managerList.push_back(manager);
    }
    f.close();
    return managerList;
}

void Manager::writeManager(string fileName) {
    fstream f(fileName.c_str(), ios::out);
    if (f.bad()) {
        cout << "管理员文件打开出错！";
        exit(0);
    }
    int i = 0;
    vector<Manager>::iterator it;
    for (it = managerList.begin(); it != managerList.end(); it++) {
        f << it->getNo() << ' ' << it->getName() << ' ' << it->getPwd() << ' ' << it->getType() << ' ' << it->getDepartment();
        i++;
        if (i != managerList.size()) {
            f << endl;
        }
    }
    f.close();
};
