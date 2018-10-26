#include <iostream>
#include <cstdlib>
#include "Student.h"
#include "Book.h"
#include "Manager.h"
#include "Ebook.h"

using namespace std;

void writeFile() {
    Student::writeStudent("student.txt");
    Manager::writeManager("manager.txt");
    Book::writeBook("book.txt");
    Ebook::writeEbook("ebook.txt");
}

int main() {
    string name;
    string pwd;
    for (int t = 0; t < 3; t++) {
        cout << "----------------图 书 管 理 系 统----------------" << endl;
        cout << "                用户名：";
        cin >> name;
        cout << "                密码：";
        cin >> pwd;
        Student student = Student(name, pwd);
        if (student.isExist()) {
            for (int i = 0; i < Student::studentList.size(); i++) {
                Student temp = Student::studentList.at(i);
                if (temp.getName() == name && temp.getPwd() == pwd) {
                    student = temp;
                    break;
                }
            }
            while (true) {
                cout << "----------------图 书 管 理 系 统----------------" << endl;
                cout << "                    1.密码修改                        " << endl;
                cout << "                    2.图书查询                        " << endl;
                cout << "                    3.借书                        " << endl;
                cout << "                    4.还书                        " << endl;
                cout << "                    0.退出                        " << endl;
                int cmd;
                cin >> cmd;
                switch(cmd) {
                case 0:
                    writeFile();
                    exit(0);
                    break;
                case 1:
                    student.changePwd();
                    break;
                case 2:
                    Book::showBooks();
                    break;
                case 3:
                    student.borrowBook();
                    break;
                case 4:
                    student.returnBook();
                    break;
                };
            }

        }

        Manager manager = Manager(name, pwd);
        if (manager.isExist()) {
            while (true) {
                cout << "----------------图 书 管 理 系 统----------------" << endl;
                cout << "                    1.密码修改                        " << endl;
                cout << "                    2.图书信息管理                        " << endl;
                cout << "                    3.学生信息管理                        " << endl;
                cout << "                    0.退出                        " << endl;
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
                    cout << "----------------图 书 管 理 系 统----------------" << endl;
                    cout << "                    1.图书录入                        " << endl;
                    cout << "                    2.图书查询                        " << endl;
                    cout << "                    3.图书删除                        " << endl;
                    cout << "                    4.图书修改                        " << endl;
                    cout << "                    0.退出                        " << endl;
                    cin >> cmd;
                    switch(cmd) {
                    case 1:
                        Book::addBook();
                        break;
                    case 2:
                        Book::searchBook();
                        break;
                    case 3:
                        Book::deleteBook();
                        break;
                    case 4:
                        Book::updateBook();
                        break;
                    case 0:
                        writeFile();
                        exit(0);
                    }
                    break;
                case 3:
                    cout << "----------------图 书 管 理 系 统----------------" << endl;
                    cout << "                    1.学生信息录入                        " << endl;
                    cout << "                    2.学生信息修改                        " << endl;
                    cout << "                    3.学生信息查询                        " << endl;
                    cout << "                    4.学生借阅情况查询                        " << endl;
                    cout << "                    5.学生信息删除                        " << endl;
                    cout << "                    0.退出                        " << endl;
                    cin >> cmd;
                    switch(cmd) {
                    case 1:
                        Student::addStudent();
                        break;
                    case 2:
                        Student::updateStudent();
                        break;
                    case 3:
                        Student::searchStudent();
                        break;
                    case 4:
                        Student::searchStudentBorrow();
                        break;
                    case 5:
                        Student::deleteStudent();
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
