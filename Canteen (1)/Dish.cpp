#include "Dish.h"
#include <fstream>
#include <iostream>
#include <iomanip>

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

void Dish::addDish(Dish Dish) {
    dishes.push_back(Dish);
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

void Dish::updateDish(Dish dish) {
    vector<Dish>::iterator it;
    for (it = dishes.begin(); it != dishes.end(); it++) {
        if (it->getDno() == dish.getDno()) {
            it->setDname(dish.getDname());
            it->setDserial(dish.getDserial());
            it->setDkind(dish.getDkind());
            it->setDprice(dish.getDprice());
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
    cout << setw(10) << "菜号" << setw(10) << "菜名" << setw(10) << "菜系" << setw(10) << "菜类" << setw(10) << "价格" << endl;
    for (it = dishes.begin(); it != dishes.end(); it++) {
        cout << setw(10) << it->getDno() << setw(10) << it->getDname() << setw(10) << it->getDserial() << setw(10) << it->getDkind() << setw(10) << it->getDprice() << endl;
    }
};
