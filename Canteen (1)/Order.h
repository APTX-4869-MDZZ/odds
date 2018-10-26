#ifndef ORDER_H
#define ORDER_H
#include <vector>
using namespace std;
class Order {
private:
    int tabNo;
    int dno;
public:
    Order();
    Order(int tabNo, int dno);
    int getTabNo() {return tabNo;};
    int getDno() {return dno;};

    static vector<Order> orders;
    static void deleteOrder(int tabNo, int dno);
    static void showOrders();
};

#endif // ORDER_H
