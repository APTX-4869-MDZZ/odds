#include "Student.h"
#include "Ebook.h"
#include "Book.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

Student::Student() {};
Student::Student(string major, string className, int num, vector<string> bnoList):
    major(major),
    className(className),
    num(num),
    bnoList(bnoList)
{

};

Student::Student(int no, string name, string pwd, string major, string className, int num, vector<string> bnoList):
    Person(no, name, pwd),
    major(major),
    className(className),
    num(num),
    bnoList(bnoList)
{

};

Student::Student(string name, string pwd):
    Person(name, pwd)
{

};

bool Student::isExist() {
    for (int i = 0; i < studentList.size(); i++) {
        Student temp = studentList.at(i);
        if (temp.getName() == name && temp.getPwd() == pwd) {
            return true;
        }
    }
    return false;
}

string Student::getName() {
    return name;
};

string Student::getPwd() {
    return pwd;
};

void Student::changePwd() {
    cout << "请输入新密码：";
    string pwd;
    cin >> pwd;
    vector<Student>::iterator it;
    for (it = studentList.begin(); it != studentList.end(); it++) {
        if (it->getNo() == this->no) {
            it->setPwd(pwd);
            break;
        }
    }
}
void Student::borrowBook() {
    cout << "请输入分类号：";
    string cno;
    cin >> cno;
    for (int i = 0; i < Book::bookList.size(); i++) {
        Book book = Book::bookList.at(i);
        if (book.getCno() == cno && book.getBn() > 0) {
            vector<Student>::iterator it;
            for (it = studentList.begin(); it != studentList.end(); it++) {
                if (it->getNo() == this->no) {
                    it->addBno(book.getBno());
                    it->setNum(num+1);
                    break;
                }
            }
            Ebook ebook = Ebook(book.getBno(), name);
            Ebook::addEbook(ebook);
            Book::bookList.at(i).setBn(book.getBn() - 1);
            break;
        }
    }
};

void Student::returnBook() {
    cout << "请输入借阅号：";
    string bno;
    cin >> bno;
    for (int i = 0; i < Book::bookList.size(); i++) {
        Book book = Book::bookList.at(i);
        if (book.getBno() == bno) {
            Book::bookList.at(i).setBn(book.getBn() + 1);
        }
    }
    for(vector<Ebook>::iterator iter=Ebook::ebookList.begin(); iter!=Ebook::ebookList.end(); iter++) {
        if(bno == iter->getBook()) {
            Ebook::ebookList.erase(iter);
            break;
       }
    }
    vector<Student>::iterator it;
    for (it = studentList.begin(); it != studentList.end(); it++) {
        if (it->getNo() == this->no) {
            it->deleteBno(bno);
            it->setNum(num-1);
            break;
        }
    }
};

void Student::deleteBno(string bno) {
    vector<string>::iterator itb;
    for (itb = bnoList.begin(); itb != bnoList.end(); itb++) {
        if (*itb == bno) {
            bnoList.erase(itb);
            break;
        }
    }
}

vector<Student> Student::studentList = Student::readStudent("student.txt");

vector<Student> Student::readStudent(string fileName) {
    vector<Student> studentList;
    fstream f(fileName.c_str(), ios::in);
    if (f.bad()) {
        cout << "学生文件打开出错！";
        exit(0);
    }
    while (!f.eof()) {
        int no;
        string name;
        string pwd;
        string major;
        string className;
        int num;
        f >> no >> name >> pwd >> major >> className >> num;
        string bno;
        vector<string> bnoListTemp;
        for (int i = 0; i < num; i++) {
            f >> bno;
            bnoListTemp.push_back(bno);
        }
        Student student = Student(no, name, pwd, major, className, num, bnoListTemp);
        studentList.push_back(student);
    }
    f.close();
    return studentList;
}

void Student::addStudent() {
    int no;
    string name;
    string major;
    string className;
    string pwd = "000000";
    int num = 0;
    cout << "请输入学生编号：";
    cin >> no;
    cout << "请输入学生姓名：";
    cin >> name;
    cout << "请输入学生专业：";
    cin >> major;
    cout << "请输入学生班级：";
    cin >> className;
    vector<string> bnoListTemp;
    Student student = Student(no, name, pwd, major, className, num, bnoListTemp);
    studentList.push_back(student);
};

void Student::updateStudent() {
    int no;
    string name;
    string major;
    string className;
    string pwd;
    int num = 0;
    vector<string> bnoListTemp;
    cout << "请输入要修改的学生信息" << endl;
    cout << "请输入学生编号：";
    cin >> no;
    cout << "请输入学生姓名：";
    cin >> name;
    cout << "请输入学生专业：";
    cin >> major;
    cout << "请输入学生班级：";
    cin >> className;
    vector<Student>::iterator it;
    for (it = studentList.begin(); it != studentList.end(); it++) {
        if (it->getNo() == no) {
            pwd = it->getPwd();
            num = it->getNum();
            bnoListTemp = it->getBnoList();
            studentList.erase(it);
            break;
        }
    }
    Student student = Student(no, name, pwd, major, className, num, bnoListTemp);
    studentList.push_back(student);
};

void Student::searchStudent() {
    int no;
    cout << "请输入学号：";
    cin >> no;
    vector<Student>::iterator it;
    for (it = studentList.begin(); it != studentList.end(); it++) {
        if (it->getNo() == no) {
            cout << it->getNo() << ' ' << it->getName() << ' ' << it->getMajor() << ' ' << it->getClassname() << endl;
            break;
        }
    }
};
void Student::searchStudentBorrow() {
    int no;
    cout << "请输入要查询的学号：";
    cin >> no;
    vector<Student>::iterator it;
    for (it = studentList.begin(); it != studentList.end(); it++) {
        if (it->getNo() == no) {
            vector<string>bnoListTemp = it->getBnoList();
            for (int i = 0; i < bnoListTemp.size(); i++) {
                for (int j = 0; j < Book::bookList.size(); j++) {
                    Book book = Book::bookList.at(j);
                    if (book.getBno() == bnoListTemp.at(i)) {
                        cout << "    " << book.getName() << "  " << book.getISBN() << "      " << book.getCno() << "        " << book.getBno() << "        " << book.getBn() << endl;
                    }
                }
            }
            break;
        }
    }

};
void Student::deleteStudent() {
    int no;
    cout << "请输入要删除的学生学号：";
    cin >> no;
    vector<Student>::iterator it;
    for (it = studentList.begin(); it != studentList.end(); it++) {
        if (it->getNo() == no) {
            studentList.erase(it);
            break;
        }
    }
};

void Student::writeStudent(string fileName) {
    fstream f(fileName.c_str(), ios::out);
    if (f.bad()) {
        cout << "学生文件打开出错！";
        exit(0);
    }
    int i = 0;
    vector<Student>::iterator it;
    for (it = studentList.begin(); it != studentList.end(); it++) {
        f << it->getNo() << ' ' << it->getName() << ' ' << it->getPwd() << ' ' << it->getMajor() << ' ' << it->getClassname() << ' ' << it->getNum();
        vector<string> bnoListTemp = it->getBnoList();
        for (int i = 0; i < it->getNum(); i++) {
            f << ' ' << bnoListTemp.at(i);
        }
        i++;
        if (i != studentList.size()) {
            f << endl;
        }
    }
    f.close();
};
