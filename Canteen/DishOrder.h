#ifndef DISHORDER_H
#define DISHORDER_H
#include <vector>
using namespace std;
class DishOrder {
private:
    int tabNo;
    int dno;
public:
    DishOrder();
    DishOrder(int tabNo, int dno);
    int getTabNo() {return tabNo;};
    int getDno() {return dno;};

    static vector<DishOrder> dishOrders;
    static void deleteDishOrder(int tabNo, int dno);
    static void showDishOrders();
};

#endif // DISHORDER_H

