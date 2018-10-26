#ifndef DISH_H
#define DISH_H
#include <string>
#include <vector>
using namespace std;

class Dish {
public:
    int dno;
    string dname;
    string dserial;
    string dkind;
    double dprice;

    Dish();
    Dish(int dno, string dname, string dserial, string dkind, double dprice);
    int getDno() {return dno;};
    string getDname() {return dname;};
    string getDserial() {return dserial;};
    string getDkind() {return dkind;};
    double getDprice() {return dprice;};
    void setDno(int dno) {this->dno = dno;};
    void setDname(string dname) {this->dname = dname;};
    void setDserial(string dserial) {this->dserial = dserial;};
    void setDkind(string dkind) {this->dkind = dkind;};
    void setDprice(double dprice) {this->dprice = dprice;};

    static vector<Dish> dishes;
    static vector<Dish> readDishes();
    static void addDish();
    static void writeFile();
    static void deleteDish(int tabNo);
    static void updateDish();
    static Dish findDish(int dno);
    static void showDishes();
    static string getNameFromDno(int dno);
    static int getDnoFromName(string name);
};
#endif // DISH_H

