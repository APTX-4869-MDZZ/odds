#include "Income.h"
#include <iostream>
#include <iomanip>

Income::Income() {};

Income::Income(int tabNo, int dno, double price):
    tabNo(tabNo),
    dno(dno),
    price(price)
{

};

vector<Income> Income::incomes;

void Income::updateOrder(int tabNo, int dno, double price) {
    vector<Income>::iterator it;
    for (it = incomes.begin(); it != incomes.end(); it++) {
        if (it->getTabNo() == tabNo && it->getDno() == dno) {
            it->setPrice(price);
            break;
        }
    }
};
void Income::showIncomes() {
    vector<Income>::iterator it;
    cout << setw(10) << "×ÀºÅ" << setw(10) << "²ËºÅ" << setw(10) << "¼Û¸ñ" << endl;
    for (it = incomes.begin(); it != incomes.end(); it++) {
        cout << setw(10) << it->getTabNo() << setw(10) << it->getDno() << setw(10) << it->getPrice() << endl;
    }
};

void Income::showConsumes() {
    vector<Income>::iterator it;
    cout << setw(10) << "×ÀºÅ" << setw(10) << "²ËºÅ" << setw(10) << "¼Û¸ñ" << endl;
    for (it = incomes.begin(); it != incomes.end(); it++) {
        if (it->getPrice() < 0) {
            cout << setw(10) << it->getTabNo() << setw(10) << it->getDno() << setw(10) << it->getPrice() << endl;
        }
    }
};
