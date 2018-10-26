#include "Order.h"
#include <vector>
#include <iostream>

Order::Order() {};

Order::Order(int tabNo, int dno):
    tabNo(tabNo),
    dno(dno)
{

};

vector<Order> Order::orders;

void Order::deleteOrder(int tabNo, int dno) {
    vector<Order>::iterator it;
    for (it = orders.begin(); it != orders.end(); it++) {
        if (it->getTabNo() == tabNo && it->getDno() == dno) {
            orders.erase(it);
            break;
        }
    }
};

void Order::showOrders() {
    vector<Order>::iterator it;
    cout << "   桌号  菜号  " << endl;
    for (it = orders.begin(); it != orders.end(); it++) {
        cout << "   " << it->getTabNo() << "    " << it->getDno() << endl;
    }
};
