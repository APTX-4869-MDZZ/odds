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
        cout << "�����ļ��򿪳���";
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
        cout << "�����ļ��򿪳���";
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
    cout << "�������²���������" << endl;
    cout << "���ţ�";
    cin >> tabNo;
    cout << "¥�㣺";
    cin >> floor;
    cout << "���ͣ�����/��������";
    cin >> type;
    cout << "��λ����";
    cin >> tabNumer;
    cout << "������ѣ�";
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
    cout << "������Ҫ�޸ĵĲ�����ţ�";
    cin >> tabNo;
    cout << "�������޸ĺ�Ĳ�������" << endl;
    cout << "¥�㣺";
    cin >> floor;
    cout << "���ͣ�����/��������";
    cin >> type;
    cout << "��λ����";
    cin >> tabNumber;
    cout << "������ѣ�";
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
    cout << setw(10) << "����";
    cout << setw(10) << "¥��";
    cout << setw(10) << "����";
    cout << setw(10) << "��λ��";
    cout << setw(10) << "�������" << endl;
    vector<Table>::iterator it;
    for (it = tables.begin(); it != tables.end(); it++) {
        cout << setw(10) << it->getTabNo() << setw(10) << it->getFloor() << setw(10) << it->getType() << setw(10) << it->getTabNumber() << setw(10) << it->getMinCharge() << endl;
    }
};

