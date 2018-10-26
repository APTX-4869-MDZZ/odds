#include "Table.h"
#include <fstream>
#include <iostream>
#include <iomanip>

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

void Table::addTable(Table table) {
    tables.push_back(table);
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

void Table::updateTable(Table table) {
    vector<Table>::iterator it;
    for (it = tables.begin(); it != tables.end(); it++) {
        if (it->getTabNo() == table.getTabNo()) {
            it->setFloor(table.getFloor());
            it->setType(table.getType());
            it->setTabNumber(table.getTabNumber());
            it->setMinCharge(table.getMinCharge());
            break;
        }
    }
};


void Table::showTables() {
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

