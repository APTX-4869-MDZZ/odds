#include "Record.h"
#include "Dish.h"
#include <iostream>
#include <iomanip>

Record::Record() {};

Record::Record(int tabNo, int dno, double price):
    tabNo(tabNo),
    dno(dno),
    price(price)
{

};

vector<Record> Record::records;

void Record::updateRecord(int tabNo, int dno, double price) {
    vector<Record>::iterator it;
    for (it = records.begin(); it != records.end(); it++) {
        if (it->getTabNo() == tabNo && it->getDno() == dno) {
            it->setPrice(price);
            break;
        }
    }
};
void Record::showRecords() {
    vector<Record>::iterator it;
    cout << endl;
    cout << setw(10) << "桌号" << setw(10) << "菜名" << setw(10) << "收入" << endl;
    for (it = records.begin(); it != records.end(); it++) {
        cout << setw(10) << it->getTabNo() << setw(10) << Dish::getNameFromDno(it->getDno()) << setw(10) << it->getPrice() << endl;
    }
};

void Record::showConsumes() {
    vector<Record>::iterator it;
    cout << endl;
    cout << setw(10) << "桌号" << setw(10) << "菜名" << setw(10) << "消费" << endl;
    for (it = records.begin(); it != records.end(); it++) {
        if (it->getPrice() < 0) {
            cout << setw(10) << it->getTabNo() << setw(10) << Dish::getNameFromDno(it->getDno()) << setw(10) << it->getPrice() << endl;
        }
    }
};

