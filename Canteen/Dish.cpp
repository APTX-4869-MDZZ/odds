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
        cout << "�����ļ��򿪳���";
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
        cout << "��ʽ�ļ��򿪳���";
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
    cout << "�������²�ʽ" << endl;
    cout << "�˺ţ�";
    cin >> dno;
    cout << "������";
    cin >> dname;
    cout << "��ϵ��";
    cin >> dserial;
    cout << "���ࣺ";
    cin >> dkind;
    cout << "�˼ۣ�";
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
    cout << "������Ҫ�޸ĵĲ�ʽ��ţ�";
    cin >> dno;
    cout << "�������޸ĺ�Ĳ�ʽ" << endl;
    cout << "������";
    cin >> dname;
    cout << "��ϵ��";
    cin >> dserial;
    cout << "���ࣺ";
    cin >> dkind;
    cout << "�˼ۣ�";
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
    cout << setw(10) << "�˺�" << setw(10) << "����" << setw(10) << "��ϵ" << setw(10) << "����" << setw(10) << "�۸�" << endl;
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
