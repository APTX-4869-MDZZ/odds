#include <iostream>
#include "Manager.h"
#include "Table.h"
#include "Dish.h"
#include "DishOrder.h"
#include "Record.h"
#include <cstdlib>

using namespace std;

void writeFile() {
    Manager::writeManager("manager.txt");
    Dish::writeFile();
    Table::writeFile();
};

void order() {
    int tabNo;
    string dName;
    cout << "���������ţ�";
    cin >> tabNo;
    cout << "�����������";
    cin >> dName;
    int dno = Dish::getDnoFromName(dName);
    DishOrder::dishOrders.push_back(DishOrder(tabNo, dno));
    Dish dish = Dish::findDish(dno);
    Record::records.push_back(Record(tabNo, dno, dish.getDprice()));
};

void deleteDishOrder() {
    int tabNo;
    string dname;
    cout << "���������ţ�";
    cin >> tabNo;
    cout << "������Ҫ��������";
    cin >> dname;
    int dno = Dish::getDnoFromName(dname);
    DishOrder::deleteDishOrder(tabNo, dno);
    Dish dish = Dish::findDish(dno);
    Record::updateRecord(tabNo, dno, 0);
};

void returnDishOrder() {
    int tabNo;
    string dname;
    cout << "���������ţ�";
    cin >> tabNo;
    cout << "������Ҫ�˲�����";
    cin >> dname;
    int dno = Dish::getDnoFromName(dname);
    DishOrder::deleteDishOrder(tabNo, dno);
    Dish dish = Dish::findDish(dno);
    Record::updateRecord(tabNo, dno, -dish.getDprice());
};

int main() {
    string name;
    string pwd;
    cout << endl;
    for (int t = 0; t < 3; t++) {
        cout << endl;
        cout << "                               ============�� �� �� �� �� �� ϵ ͳ============" << endl;
        cout << endl;
        cout << "                                               �û�����";
        cin >> name;
        cout << "                                               ���룺";
        cin >> pwd;

        Manager manager = Manager(name, pwd);
        if (manager.isExist()) {
            while (true) {
                cout << endl;
                cout << "                               -------========�� �� Ա �� �� �� ��========-------" << endl;
                cout << "                                                   0.�˳�                        " << endl;
                cout << "                                                   1.�����޸�                        " << endl;
                cout << "                                                   2.��������                        " << endl;
                cout << "                                                   3.��ʽ����                        " << endl;
                cout << "                                                   4.��������                        " << endl;
                cout << "                                                   5.��ѯ����                        " << endl;
                cout << "                               �����������ţ�";
                int cmd;
                cin >> cmd;
                switch(cmd) {
                case 0:
                    writeFile();
                    exit(0);
                    break;
                case 1:
                    manager.changePwd();
                    break;
                case 2:
                    cout << endl;
                    cout << "                               --------===========�� �� �� ��========--------" << endl;
                    cout << "                                                   0.�˳�                        " << endl;
                    cout << "                                                   1.��������                        " << endl;
                    cout << "                                                   2.����ɾ��                        " << endl;
                    cout << "                                                   3.�����޸�                        " << endl;
                    cout << "                               �����������ţ�";
                    cin >> cmd;
                    switch(cmd) {
                    case 1:
                        Table::addTable();
                        break;
                    case 2:
                        int tabNo;
                        cout << endl;
                        cout << "                               ������Ҫɾ���Ĳ�����ţ�";
                        cin >> tabNo;
                        Table::deleteTable(tabNo);
                        break;
                    case 3:
                        Table::updateTable();
                        break;
                    case 0:
                        writeFile();
                        exit(0);
                    }
                    break;
                case 3:
                    cout << endl;
                    cout << "                               ---------==========�� ʽ �� ��========-----------" << endl;
                    cout << "                                                   0.�˳�                        " << endl;
                    cout << "                                                   1.��ʽ����                        " << endl;
                    cout << "                                                   2.��ʽɾ��                        " << endl;
                    cout << "                                                   3.��ʽ�޸�                        " << endl;
                    cout << "                               �����������ţ�";
                    cin >> cmd;
                    switch(cmd) {
                    case 1:
                        Dish::addDish();
                        break;
                    case 2:
                        int dno;
                        cout << endl;
                        cout << "                               ������Ҫɾ���Ĳ�ʽ��ţ�";
                        cin >> dno;
                        Dish::deleteDish(dno);
                        break;
                    case 3:
                        Dish::updateDish();
                        break;
                    case 0:
                        writeFile();
                        exit(0);
                    }
                    break;
                case 4:
                    cout << endl;
                    cout << "                               ---------==========�� �� �� ��========---------" << endl;
                    cout << "                                                    0.�˳�                        " << endl;
                    cout << "                                                    1.���                        " << endl;
                    cout << "                                                    2.����                        " << endl;
                    cout << "                                                    3.�˲�                        " << endl;
                    cout << "                               �����������ţ�";
                    cin >> cmd;
                    switch(cmd) {
                    case 1:
                        order();
                        break;
                    case 2:
                        deleteDishOrder();
                        break;
                    case 3:
                        returnDishOrder();
                        break;
                    case 0:
                        writeFile();
                        exit(0);
                    }
                    break;
                case 5:
                    cout << endl;
                    cout << "                               --------==========�� �� �� ѯ=========--------" << endl;
                    cout << "                                                  0.�˳�                        " << endl;
                    cout << "                                                  1.������ѯ                        " << endl;
                    cout << "                                                  2.��ʽ��ѯ                        " << endl;
                    cout << "                                                  3.���Ѳ�ѯ                        " << endl;
                    cout << "                                                  4.������ϸ                        " << endl;
                    cout << "                               �����������ţ�";
                    cin >> cmd;
                    switch(cmd) {
                    case 1:
                        Table::showTables();
                        break;
                    case 2:
                        Dish::showDishes();
                        break;
                    case 3:
                        Record::showConsumes();
                        break;
                    case 4:
                        Record::showRecords();
                        break;
                    case 0:
                        writeFile();
                        exit(0);
                    }
                    break;
                };
            }
        }
        cout << "                               �û������������������������" << 2-t << "��" << endl;
    }
    writeFile();
    return 0;
}
