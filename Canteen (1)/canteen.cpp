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
    Table::addTable(Table(tabNo, floor, type, tabNumer, minCharge));
}

void updateTable() {
    int tabNo;
    int floor;
    string type;
    int tabNumer;
    double minCharge;
    cout << "请输入要修改的餐桌编号：";
    cin >> tabNo;
    cout << "请输入修改后的餐桌属性" << endl;
    cout << "楼层：";
    cin >> floor;
    cout << "类型（包房/大厅）：";
    cin >> type;
    cout << "餐位数：";
    cin >> tabNumer;
    cout << "最低消费：";
    cin >> minCharge;
    Table::updateTable(Table(tabNo, floor, type, tabNumer, minCharge));
}

void addDish() {
    int dno;
    string dname;
    string dserial;
    string dkind;
    double dprice;
    cout << "请输入新菜式" << endl;
    cout << "菜号：";
    cin >> dno;
    cout << "菜名：";
    cin >> dname;
    cout << "菜系：";
    cin >> dserial;
    cout << "菜类：";
    cin >> dkind;
    cout << "菜价：";
    cin >> dprice;
    Dish::addDish(Dish(dno, dname, dserial, dkind, dprice));
};

void updateDish() {
    int dno;
    string dname;
    string dserial;
    string dkind;
    double dprice;
    cout << "请输入要修改的菜式编号：";
    cin >> dno;
    cout << "请输入修改后的菜式" << endl;
    cout << "菜名：";
    cin >> dname;
    cout << "菜系：";
    cin >> dserial;
    cout << "菜类：";
    cin >> dkind;
    cout << "菜价：";
    cin >> dprice;
    Dish::updateDish(Dish(dno, dname, dserial, dkind, dprice));
};

void order() {
    int tabNo;
    int dno;
    cout << "请输入桌号：";
    cin >> tabNo;
    cout << "请输入菜号：";
    cin >> dno;
    Order::orders.push_back(Order(tabNo, dno));
    Dish dish = Dish::findDish(dno);
    Income::incomes.push_back(Income(tabNo, dno, dish.getDprice()));
};

void deleteOrder() {
    int tabNo;
    int dno;
    cout << "请输入桌号：";
    cin >> tabNo;
    cout << "请输入要消菜号：";
    cin >> dno;
    Order::deleteOrder(tabNo, dno);
    Dish dish = Dish::findDish(dno);
    Income::updateOrder(tabNo, dno, 0);
};

void returnOrder() {
    int tabNo;
    int dno;
    cout << "请输入桌号：";
    cin >> tabNo;
    cout << "请输入要退菜号：";
    cin >> dno;
    Order::deleteOrder(tabNo, dno);
    Dish dish = Dish::findDish(dno);
    Income::updateOrder(tabNo, dno, -dish.getDprice());
};

int main() {
    string name;
    string pwd;
    for (int t = 0; t < 3; t++) {
        cout << "============餐 厅 收 银 管 理 系 统============" << endl;
        cout << "                用户名：";
        cin >> name;
        cout << "                密码：";
        cin >> pwd;

        Manager manager = Manager(name, pwd);
        if (manager.isExist()) {
            while (true) {
                cout << "===============管 理 员 功 能 菜 单================" << endl;
                cout << "                    1.密码修改                        " << endl;
                cout << "                    2.餐桌管理                        " << endl;
                cout << "                    3.菜式管理                        " << endl;
                cout << "                    4.收银管理                        " << endl;
                cout << "                    5.查询报表                        " << endl;
                cout << "                    0.退出                        " << endl;
                cout << "请输入命令编号：";
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
                    cout << "===================餐 桌 管 理================" << endl;
                    cout << "                    1.餐桌增加                        " << endl;
                    cout << "                    2.餐桌删除                        " << endl;
                    cout << "                    3.餐桌修改                        " << endl;
                    cout << "                    0.退出                        " << endl;
                    cout << "请输入命令编号：";
                    cin >> cmd;
                    switch(cmd) {
                    case 1:
                        addTable();
                        break;
                    case 2:
                        int tabNo;
                        cout << "请输入要删除的餐桌编号：";
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
                    cout << "===================菜 式 管 理=================" << endl;
                    cout << "                    1.菜式增加                        " << endl;
                    cout << "                    2.菜式删除                        " << endl;
                    cout << "                    3.菜式修改                        " << endl;
                    cout << "                    0.退出                        " << endl;
                    cout << "请输入命令编号：";
                    cin >> cmd;
                    switch(cmd) {
                    case 1:
                        addDish();
                        break;
                    case 2:
                        int dno;
                        cout << "请输入要删除的菜式编号：";
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
                    cout << "===================收 银 管 理=================" << endl;
                    cout << "                     1.点餐                        " << endl;
                    cout << "                     2.消菜                        " << endl;
                    cout << "                     3.退菜                        " << endl;
                    cout << "                     0.退出                        " << endl;
                    cout << "请输入命令编号：";
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
                    cout << "===================报 表 查 询=================" << endl;
                    cout << "                   1.餐桌查询                        " << endl;
                    cout << "                   2.菜式查询                        " << endl;
                    cout << "                   3.消费查询                        " << endl;
                    cout << "                   4.收入明细                        " << endl;
                    cout << "                   0.退出                        " << endl;
                    cout << "请输入命令编号：";
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
        cout << "用户名或密码错误！您还可以重试" << 2-t << "次" << endl;
    }
    writeFile();
    return 0;
}
