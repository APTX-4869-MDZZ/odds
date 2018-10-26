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
        cout << "----------------ͼ �� �� �� ϵ ͳ----------------" << endl;
        cout << "                �û�����";
        cin >> name;
        cout << "                ���룺";
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
                cout << "----------------ͼ �� �� �� ϵ ͳ----------------" << endl;
                cout << "                    1.�����޸�                        " << endl;
                cout << "                    2.ͼ���ѯ                        " << endl;
                cout << "                    3.����                        " << endl;
                cout << "                    4.����                        " << endl;
                cout << "                    0.�˳�                        " << endl;
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
                cout << "----------------ͼ �� �� �� ϵ ͳ----------------" << endl;
                cout << "                    1.�����޸�                        " << endl;
                cout << "                    2.ͼ����Ϣ����                        " << endl;
                cout << "                    3.ѧ����Ϣ����                        " << endl;
                cout << "                    0.�˳�                        " << endl;
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
                    cout << "----------------ͼ �� �� �� ϵ ͳ----------------" << endl;
                    cout << "                    1.ͼ��¼��                        " << endl;
                    cout << "                    2.ͼ���ѯ                        " << endl;
                    cout << "                    3.ͼ��ɾ��                        " << endl;
                    cout << "                    4.ͼ���޸�                        " << endl;
                    cout << "                    0.�˳�                        " << endl;
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
                    cout << "----------------ͼ �� �� �� ϵ ͳ----------------" << endl;
                    cout << "                    1.ѧ����Ϣ¼��                        " << endl;
                    cout << "                    2.ѧ����Ϣ�޸�                        " << endl;
                    cout << "                    3.ѧ����Ϣ��ѯ                        " << endl;
                    cout << "                    4.ѧ�����������ѯ                        " << endl;
                    cout << "                    5.ѧ����Ϣɾ��                        " << endl;
                    cout << "                    0.�˳�                        " << endl;
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
        cout << "�û������������������������" << 2-t << "��" << endl;
    }
    writeFile();
    return 0;
}
