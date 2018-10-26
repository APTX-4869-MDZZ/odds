#include <iostream>
#include "Manager.h"
#include "Table.h"
#include "Dish.h"
#include "Order.h"
#include "Income.h"

using namespace std;

void writeFile() {
    Manager::writeManager("manager.txt");
    Dish::writeFile();
    Table::writeFile();
}

void addTable() {
    int tabNo;
    int floor;
    string type;
    int tabNumer;
    double minCharge;
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
    Table::addTable(Table(tabNo, floor, type, tabNumer, minCharge));
}

void updateTable() {
    int tabNo;
    int floor;
    string type;
    int tabNumer;
    double minCharge;
    cout << "������Ҫ�޸ĵĲ�����ţ�";
    cin >> tabNo;
    cout << "�������޸ĺ�Ĳ�������" << endl;
    cout << "¥�㣺";
    cin >> floor;
    cout << "���ͣ�����/��������";
    cin >> type;
    cout << "��λ����";
    cin >> tabNumer;
    cout << "������ѣ�";
    cin >> minCharge;
    Table::updateTable(Table(tabNo, floor, type, tabNumer, minCharge));
}

void addDish() {
    int dno;
    string dname;
    string dserial;
    string dkind;
    double dprice;
    cout << "�������²�ʽ" << endl;
    cout << "�˺ţ�";
    cin >> dno;
    cout << "������";
    cin >> dname;
    cout << "��ϵ��";
    cin >> dserial;
    cout << "���ࣺ";
    cin >> dkind;
    cout << "�˼ۣ�";
    cin >> dprice;
    Dish::addDish(Dish(dno, dname, dserial, dkind, dprice));
};

void updateDish() {
    int dno;
    string dname;
    string dserial;
    string dkind;
    double dprice;
    cout << "������Ҫ�޸ĵĲ�ʽ��ţ�";
    cin >> dno;
    cout << "�������޸ĺ�Ĳ�ʽ" << endl;
    cout << "������";
    cin >> dname;
    cout << "��ϵ��";
    cin >> dserial;
    cout << "���ࣺ";
    cin >> dkind;
    cout << "�˼ۣ�";
    cin >> dprice;
    Dish::updateDish(Dish(dno, dname, dserial, dkind, dprice));
};

void order() {
    int tabNo;
    int dno;
    cout << "���������ţ�";
    cin >> tabNo;
    cout << "������˺ţ�";
    cin >> dno;
    Order::orders.push_back(Order(tabNo, dno));
    Dish dish = Dish::findDish(dno);
    Income::incomes.push_back(Income(tabNo, dno, dish.getDprice()));
};

void deleteOrder() {
    int tabNo;
    int dno;
    cout << "���������ţ�";
    cin >> tabNo;
    cout << "������Ҫ���˺ţ�";
    cin >> dno;
    Order::deleteOrder(tabNo, dno);
    Dish dish = Dish::findDish(dno);
    Income::updateOrder(tabNo, dno, 0);
};

void returnOrder() {
    int tabNo;
    int dno;
    cout << "���������ţ�";
    cin >> tabNo;
    cout << "������Ҫ�˲˺ţ�";
    cin >> dno;
    Order::deleteOrder(tabNo, dno);
    Dish dish = Dish::findDish(dno);
    Income::updateOrder(tabNo, dno, -dish.getDprice());
};

int main() {
    string name;
    string pwd;
    for (int t = 0; t < 3; t++) {
        cout << "============�� �� �� �� �� �� ϵ ͳ============" << endl;
        cout << "                �û�����";
        cin >> name;
        cout << "                ���룺";
        cin >> pwd;

        Manager manager = Manager(name, pwd);
        if (manager.isExist()) {
            while (true) {
                cout << "===============�� �� Ա �� �� �� ��================" << endl;
                cout << "                    1.�����޸�                        " << endl;
                cout << "                    2.��������                        " << endl;
                cout << "                    3.��ʽ����                        " << endl;
                cout << "                    4.��������                        " << endl;
                cout << "                    5.��ѯ����                        " << endl;
                cout << "                    0.�˳�                        " << endl;
                cout << "�����������ţ�";
                int cmd;
                cin >> cmd;
                switch(cmd) {
                case 0:
                    writeFile();
                    exit(0);
                    break;
                case 1:
                    manager.changePwd();
                case 2:
                    cout << "===================�� �� �� ��================" << endl;
                    cout << "                    1.��������                        " << endl;
                    cout << "                    2.����ɾ��                        " << endl;
                    cout << "                    3.�����޸�                        " << endl;
                    cout << "                    0.�˳�                        " << endl;
                    cout << "�����������ţ�";
                    cin >> cmd;
                    switch(cmd) {
                    case 1:
                        addTable();
                        break;
                    case 2:
                        int tabNo;
                        cout << "������Ҫɾ���Ĳ�����ţ�";
                        cin >> tabNo;
                        Table::deleteTable(tabNo);
                        break;
                    case 3:
                        updateTable();
                        break;
                    case 0:
                        writeFile();
                        exit(0);
                    }
                    break;
                case 3:
                    cout << "===================�� ʽ �� ��=================" << endl;
                    cout << "                    1.��ʽ����                        " << endl;
                    cout << "                    2.��ʽɾ��                        " << endl;
                    cout << "                    3.��ʽ�޸�                        " << endl;
                    cout << "                    0.�˳�                        " << endl;
                    cout << "�����������ţ�";
                    cin >> cmd;
                    switch(cmd) {
                    case 1:
                        addDish();
                        break;
                    case 2:
                        int dno;
                        cout << "������Ҫɾ���Ĳ�ʽ��ţ�";
                        cin >> dno;
                        Dish::deleteDish(dno);
                        break;
                    case 3:
                        updateDish();
                        break;
                    case 0:
                        writeFile();
                        exit(0);
                    }
                    break;
                case 4:
                    cout << "===================�� �� �� ��=================" << endl;
                    cout << "                     1.���                        " << endl;
                    cout << "                     2.����                        " << endl;
                    cout << "                     3.�˲�                        " << endl;
                    cout << "                     0.�˳�                        " << endl;
                    cout << "�����������ţ�";
                    cin >> cmd;
                    switch(cmd) {
                    case 1:
                        order();
                        break;
                    case 2:
                        deleteOrder();
                        break;
                    case 3:
                        returnOrder();
                        break;
                    case 0:
                        writeFile();
                        exit(0);
                    }
                    break;
                case 5:
                    cout << "===================�� �� �� ѯ=================" << endl;
                    cout << "                   1.������ѯ                        " << endl;
                    cout << "                   2.��ʽ��ѯ                        " << endl;
                    cout << "                   3.���Ѳ�ѯ                        " << endl;
                    cout << "                   4.������ϸ                        " << endl;
                    cout << "                   0.�˳�                        " << endl;
                    cout << "�����������ţ�";
                    cin >> cmd;
                    switch(cmd) {
                    case 1:
                        Table::showTables();
                        break;
                    case 2:
                        Dish::showDishes();
                        break;
                    case 3:
                        Income::showConsumes();
                        break;
                    case 4:
                        Income::showIncomes();
                        break;
                    case 0:
                        writeFile();
                        exit(0);
                    }
                    break;
                };
            }
        }
        cout << "�û������������������������" << 2-t << "��" << endl;
    }
    writeFile();
    return 0;
}
