#include "DishOrder.h"
#include "Dish.h"
#include <vector>
#include <iostream>

DishOrder::DishOrder() {};

DishOrder::DishOrder(int tabNo, int dno):
    tabNo(tabNo),
    dno(dno)
{

};

vector<DishOrder> DishOrder::dishOrders;

void DishOrder::deleteDishOrder(int tabNo, int dno)
{
    vector<DishOrder>::iterator it;
    for (it = dishOrders.begin(); it != dishOrders.end(); it++)
    {
        if (it->getTabNo() == tabNo && it->getDno() == dno)
        {
            dishOrders.erase(it);
            break;
        }
    }
};

void DishOrder::showDishOrders()
{
    vector<DishOrder>::iterator it;
    cout << endl;
    cout << "   ×ÀºÅ  ²ËÃû  " << endl;
    for (it = dishOrders.begin(); it != dishOrders.end(); it++)
    {
        cout << "   " << it->getTabNo() << "    " << Dish::getNameFromDno(it->getDno()) << endl;
    }
};

