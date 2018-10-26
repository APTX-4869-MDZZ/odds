#ifndef PERSON_H
#define PERSON_H
#include <string>
using namespace std;

class Person {
public:
    int no;
    string name;
    string pwd;

    Person();
    Person(int no, string name, string pwd);
    Person(string name, string pwd);
};
#endif // PERSON_H
