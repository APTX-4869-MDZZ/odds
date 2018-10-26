#include "Dish.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>

Dish::Dish() {};

Dish::Dish(int dno, string dname, string dserial, string dkind, double dprice):
    dno(dno),
    dname(dname),
    dserial(dserial),
    dkind(dkind),
    dprice(dprice)
{

};


vector<Dish> Dish::dishes = readDishes();

vector<Dish> Dish::readDishes() {
    vector<Dish> dishes;
    fstream f("dish.txt", ios::in);
    if (f.bad()) {
        cout << "餐桌文件打开出错！";
        exit(0);
    }
    int dno;
    string dname;
    string dserial;
    string dkind;
    double dprice;
    while (!f.eof()) {
        f >> dno >> dname >> dserial >> dkind >> dprice;
        Dish dish = Dish(dno, dname, dserial, dkind, dprice);
        dishes.push_back(dish);
    }
    f.close();
    return dishes;
};

void Dish::writeFile() {
    fstream f("dish.txt", ios::out);
    if (f.bad()) {
        cout << "菜式文件打开出错！";
        exit(0);
    }
    int i = 0;
    vector<Dish>::iterator it;
    for (it = dishes.begin(); it != dishes.end(); it++) {
        f << it->getDno() << " " << it->getDname() << " " << it->getDserial() << " " << it->getDkind() << " " << it->getDprice();
        i++;
        if (i != dishes.size()) {
            f << endl;
        }
    }
    f.close();
};

void Dish::addDish() {
    int dno;
    string dname;
    string dserial;
    string dkind;
    double dprice;
    cout << endl;
    cout << "请输入新菜式" << endl;
    cout << "菜号：";
    cin >> dno;
    cout << "菜名：";
    cin >> dname;
    cout << "菜系：";
    cin >> dserial;
    cout << "菜类：";
    cin >> dkind;
    cout << "菜价：";
    cin >> dprice;
    dishes.push_back(Dish(dno, dname, dserial, dkind, dprice));
};

void Dish::deleteDish(int dno) {
    vector<Dish>::iterator it;
    for (it = dishes.begin(); it != dishes.end(); it++) {
        if (it->getDno() == dno) {
            dishes.erase(it);
            break;
        }
    }
};

void Dish::updateDish() {
    int dno;
    string dname;
    string dserial;
    string dkind;
    double dprice;
    cout << endl;
    cout << "请输入要修改的菜式编号：";
    cin >> dno;
    cout << "请输入修改后的菜式" << endl;
    cout << "菜名：";
    cin >> dname;
    cout << "菜系：";
    cin >> dserial;
    cout << "菜类：";
    cin >> dkind;
    cout << "菜价：";
    cin >> dprice;
    vector<Dish>::iterator it;
    for (it = dishes.begin(); it != dishes.end(); it++) {
        if (it->getDno() == dno) {
            it->setDname(dname);
            it->setDserial(dserial);
            it->setDkind(dkind);
            it->setDprice(dprice);
            break;
        }
    }
};

Dish Dish::findDish(int dno) {
    vector<Dish>::iterator it;
    for (it = dishes.begin(); it != dishes.end(); it++) {
        if (it->getDno() == dno) {
            return *it;
        }
    }
}

void Dish::showDishes() {
    vector<Dish>::iterator it;
    cout << endl;
    cout << setw(10) << "菜号" << setw(10) << "菜名" << setw(10) << "菜系" << setw(10) << "菜类" << setw(10) << "价格" << endl;
    for (it = dishes.begin(); it != dishes.end(); it++) {
        cout << setw(10) << it->getDno() << setw(10) << it->getDname() << setw(10) << it->getDserial() << setw(10) << it->getDkind() << setw(10) << it->getDprice() << endl;
    }
};

string Dish::getNameFromDno(int dno) {
    vector<Dish>::iterator it;
    for (it = dishes.begin(); it != dishes.end(); it++) {
        if (it->getDno() == dno) {
            return it->getDname();
        }
    }
};
int Dish::getDnoFromName(string name) {
    vector<Dish>::iterator it;
    for (it = dishes.begin(); it != dishes.end(); it++) {
        if (it->getDname() == name) {
            return it->getDno();
        }
    }
};
