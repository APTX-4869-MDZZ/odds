#include "Person.h"

Person::Person() {};
Person::Person(int no, string name, string pwd):
    no(no),
    name(name),
    pwd(pwd)
{

};

Person::Person(string name, string pwd):
    name(name),
    pwd(pwd)
{

};

