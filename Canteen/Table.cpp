#include "Table.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>

Table::Table() {};

Table::Table(int tabNo, int floor, string type, int tabNumber, double minCharge):
    tabNo(tabNo),
    floor(floor),
    type(type),
    tabNumber(tabNumber),
    minCharge(minCharge)
{

};

vector<Table> Table::tables = readTables();

vector<Table> Table::readTables() {
    vector<Table> tables;
    fstream f("table.txt", ios::in);
    if (f.bad()) {
        cout << "餐桌文件打开出错！";
        exit(0);
    }
    int tabNo;
    int floor;
    string type;
    int tabNumber;
    double minCharge;
    while (!f.eof()) {
        f >> tabNo >> floor >> type >> tabNumber >> minCharge;
        Table table = Table(tabNo, floor, type, tabNumber, minCharge);
        tables.push_back(table);
    }
    f.close();
    return tables;
};

void Table::writeFile() {
    fstream f("table.txt", ios::out);
    if (f.bad()) {
        cout << "餐桌文件打开出错！";
        exit(0);
    }
    int i = 0;
    vector<Table>::iterator it;
    for (it = tables.begin(); it != tables.end(); it++) {
        f << it->getTabNo() << " " << it->getFloor() << " " << it->getType() << " " << it->getTabNumber() << " " << it->getMinCharge();
        i++;
        if (i != tables.size()) {
            f << endl;
        }
    }
    f.close();
};

void Table::addTable() {
    int tabNo;
    int floor;
    string type;
    int tabNumer;
    double minCharge;
    cout << endl;
    cout << "请输入新餐桌参数：" << endl;
    cout << "桌号：";
    cin >> tabNo;
    cout << "楼层：";
    cin >> floor;
    cout << "类型（包房/大厅）：";
    cin >> type;
    cout << "餐位数：";
    cin >> tabNumer;
    cout << "最低消费：";
    cin >> minCharge;
    tables.push_back(Table(tabNo, floor, type, tabNumer, minCharge));
};

void Table::deleteTable(int tabNo) {
    vector<Table>::iterator it;
    for (it = tables.begin(); it != tables.end(); it++) {
        if (it->getTabNo() == tabNo) {
            tables.erase(it);
            break;
        }
    }
};

void Table::updateTable() {
    int tabNo;
    int floor;
    string type;
    int tabNumber;
    double minCharge;
    cout << endl;
    cout << "请输入要修改的餐桌编号：";
    cin >> tabNo;
    cout << "请输入修改后的餐桌属性" << endl;
    cout << "楼层：";
    cin >> floor;
    cout << "类型（包房/大厅）：";
    cin >> type;
    cout << "餐位数：";
    cin >> tabNumber;
    cout << "最低消费：";
    cin >> minCharge;
    vector<Table>::iterator it;
    for (it = tables.begin(); it != tables.end(); it++) {
        if (it->getTabNo() == tabNo) {
            it->setFloor(floor);
            it->setType(type);
            it->setTabNumber(tabNumber);
            it->setMinCharge(minCharge);
            break;
        }
    }
};


void Table::showTables() {
    cout << endl;
    cout << setw(10) << "桌号";
    cout << setw(10) << "楼层";
    cout << setw(10) << "类型";
    cout << setw(10) << "餐位数";
    cout << setw(10) << "最低消费" << endl;
    vector<Table>::iterator it;
    for (it = tables.begin(); it != tables.end(); it++) {
        cout << setw(10) << it->getTabNo() << setw(10) << it->getFloor() << setw(10) << it->getType() << setw(10) << it->getTabNumber() << setw(10) << it->getMinCharge() << endl;
    }
};

