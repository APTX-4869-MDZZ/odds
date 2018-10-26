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
    cout << "请输入桌号：";
    cin >> tabNo;
    cout << "请输入菜名：";
    cin >> dName;
    int dno = Dish::getDnoFromName(dName);
    DishOrder::dishOrders.push_back(DishOrder(tabNo, dno));
    Dish dish = Dish::findDish(dno);
    Record::records.push_back(Record(tabNo, dno, dish.getDprice()));
};

void deleteDishOrder() {
    int tabNo;
    string dname;
    cout << "请输入桌号：";
    cin >> tabNo;
    cout << "请输入要消菜名：";
    cin >> dname;
    int dno = Dish::getDnoFromName(dname);
    DishOrder::deleteDishOrder(tabNo, dno);
    Dish dish = Dish::findDish(dno);
    Record::updateRecord(tabNo, dno, 0);
};

void returnDishOrder() {
    int tabNo;
    string dname;
    cout << "请输入桌号：";
    cin >> tabNo;
    cout << "请输入要退菜名：";
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
        cout << "                               ============餐 厅 收 银 管 理 系 统============" << endl;
        cout << endl;
        cout << "                                               用户名：";
        cin >> name;
        cout << "                                               密码：";
        cin >> pwd;

        Manager manager = Manager(name, pwd);
        if (manager.isExist()) {
            while (true) {
                cout << endl;
                cout << "                               -------========管 理 员 功 能 菜 单========-------" << endl;
                cout << "                                                   0.退出                        " << endl;
                cout << "                                                   1.密码修改                        " << endl;
                cout << "                                                   2.餐桌管理                        " << endl;
                cout << "                                                   3.菜式管理                        " << endl;
                cout << "                                                   4.收银管理                        " << endl;
                cout << "                                                   5.查询报表                        " << endl;
                cout << "                               请输入命令编号：";
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
                    cout << "                               --------===========餐 桌 管 理========--------" << endl;
                    cout << "                                                   0.退出                        " << endl;
                    cout << "                                                   1.餐桌增加                        " << endl;
                    cout << "                                                   2.餐桌删除                        " << endl;
                    cout << "                                                   3.餐桌修改                        " << endl;
                    cout << "                               请输入命令编号：";
                    cin >> cmd;
                    switch(cmd) {
                    case 1:
                        Table::addTable();
                        break;
                    case 2:
                        int tabNo;
                        cout << endl;
                        cout << "                               请输入要删除的餐桌编号：";
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
                    cout << "                               ---------==========菜 式 管 理========-----------" << endl;
                    cout << "                                                   0.退出                        " << endl;
                    cout << "                                                   1.菜式增加                        " << endl;
                    cout << "                                                   2.菜式删除                        " << endl;
                    cout << "                                                   3.菜式修改                        " << endl;
                    cout << "                               请输入命令编号：";
                    cin >> cmd;
                    switch(cmd) {
                    case 1:
                        Dish::addDish();
                        break;
                    case 2:
                        int dno;
                        cout << endl;
                        cout << "                               请输入要删除的菜式编号：";
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
                    cout << "                               ---------==========收 银 管 理========---------" << endl;
                    cout << "                                                    0.退出                        " << endl;
                    cout << "                                                    1.点餐                        " << endl;
                    cout << "                                                    2.消菜                        " << endl;
                    cout << "                                                    3.退菜                        " << endl;
                    cout << "                               请输入命令编号：";
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
                    cout << "                               --------==========报 表 查 询=========--------" << endl;
                    cout << "                                                  0.退出                        " << endl;
                    cout << "                                                  1.餐桌查询                        " << endl;
                    cout << "                                                  2.菜式查询                        " << endl;
                    cout << "                                                  3.消费查询                        " << endl;
                    cout << "                                                  4.收入明细                        " << endl;
                    cout << "                               请输入命令编号：";
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
        cout << "                               用户名或密码错误！您还可以重试" << 2-t << "次" << endl;
    }
    writeFile();
    return 0;
}
