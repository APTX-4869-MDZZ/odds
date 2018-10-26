#ifndef TABLE_H
#define TABLE_H
#include <vector>
#include <string>
using namespace std;

class Table {
public:
    int tabNo;
    int floor;
    string type;
    int tabNumber;
    double minCharge;

    Table();
    Table(int tabNo, int floor, string type, int tabNumber, double minCharge);
    int getTabNo() {return tabNo;};
    int getFloor() {return floor;};
    string getType() {return type;};
    int getTabNumber() {return tabNumber;};
    double getMinCharge() {return minCharge;};
    void setTabNo(int tabNo) {this->tabNo = tabNo;};
    void setFloor(int floor) {this->floor = floor;};
    void setType(string type) {this->type = type;};
    void setTabNumber(int tabNumber) {this->tabNumber = tabNumber;};
    void setMinCharge(double minCharge) {this->minCharge = minCharge;};

    static vector<Table> tables;
    static vector<Table> readTables();
    static void addTable(Table table);
    static void writeFile();
    static void deleteTable(int tabNo);
    static void updateTable(Table table);
    static void showTables();
};
#endif // TABLE_H
