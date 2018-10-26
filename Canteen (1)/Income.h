#ifndef INCOME_H
#define INCOME_H
#include <vector>
using namespace std;
class Income {
private:
    int tabNo;
    int dno;
    double price;
public:
    Income();
    Income(int tabNo, int dno, double price);
    int getTabNo() {return tabNo;};
    int getDno() {return dno;};
    int getPrice() {return price;};
    void setPrice(double price) {this->price = price;};

    static vector<Income> incomes;
    static void updateOrder(int tabNo, int dno, double price);
    static void showIncomes();
    static void showConsumes();
};

#endif // INCOME_H

