#include "Book.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

Book::Book() {};
Book::Book(string bname, string ISBN, string cno, string bno, int bn):
    bname(bname),
    ISBN(ISBN),
    cno(cno),
    bno(bno),
    bn(bn)
{

};
vector<Book> Book::bookList = Book::readBook("book.txt");

vector<Book> Book::readBook(string fileName) {
    vector<Book> bookList;
    fstream f(fileName.c_str(), std::ios::in);
    if (f.bad()) {
        cout << "书籍文件打开出错！";
        exit(0);
    }
    while (!f.eof()) {
        string bname;
        string ISBN;
        string cno;
        string bno;
        int bn;
        f >> bname >> ISBN >> cno >> bno >> bn;
        Book book = Book(bname, ISBN, cno, bno, bn);
        bookList.push_back(book);
    }
    f.close();
    return bookList;
}

void Book::showBooks() {
    cout << "---------书籍名--------------ISBN------------分类号------借阅号-----数量------" << endl;
    for (int i = 0; i < bookList.size(); i++) {
        Book book = bookList.at(i);
        cout << "    " << book.getName() << "  " << book.getISBN() << "      " << book.getCno() << "        " << book.getBno() << "        " << book.getBn() << endl;
    }
}

void Book::addBook() {
    string bname;
    string ISBN;
    string cno;
    string bno;
    int bn;
    cout << "请输入书籍名：";
    cin >> bname;
    cout << "请输入ISBN：";
    cin >> ISBN;
    cout << "请输入分类号：";
    cin >> cno;
    cout << "请输入借阅号：";
    cin >> bno;
    cout << "请输入册数：";
    cin >> bn;

    Book book = Book(bname, ISBN, cno, bno, bn);
    bookList.push_back(book);
};

void Book::searchBook() {
    string keyword;
    cout << "请输入ISBN号或分类号：";
    cin >> keyword;
    bool found = false;
    for (int i = 0; i < bookList.size(); i++) {
        Book book = bookList.at(i);
        if (book.getCno() == keyword || book.getISBN() == keyword) {
            found = true;
            cout << "    " << book.getName() << "  " << book.getISBN() << "      " << book.getCno() << "        " << book.getBno() << "        " << book.getBn() << endl;
        }
    }
    if (!found) {
        cout << "未找到符合条件的书籍。" << endl;
    }
};
void Book::deleteBook() {
    string bno;
    cout << "请输入借阅号";
    cin >> bno;
    vector<Book>::iterator it;
    for (it = bookList.begin(); it != bookList.end(); it++) {
        if (it->getBno() == bno) {
            bookList.erase(it);
            break;
        }
    }
};
void Book::updateBook() {
    cout << "请输入要修改的图书信息" << endl;
    string bname;
    string ISBN;
    string cno;
    string bno;
    int bn;
    cout << "请输入书籍名：";
    cin >> bname;
    cout << "请输入ISBN：";
    cin >> ISBN;
    cout << "请输入分类号：";
    cin >> cno;
    cout << "请输入借阅号：";
    cin >> bno;
    cout << "请输入册数：";
    cin >> bn;
    vector<Book>::iterator it;
    for (it = bookList.begin(); it != bookList.end(); it++) {
        if (it->getBno() == bno) {
            bookList.erase(it);
            break;
        }
    }
    Book book = Book(bname, ISBN, cno, bno, bn);
    bookList.push_back(book);
};

void Book::writeBook(string fileName) {
    fstream f(fileName.c_str(), ios::out);
    if (f.bad()) {
        cout << "书籍文件打开出错！";
        exit(0);
    }
    int i = 0;
    vector<Book>::iterator it;
    for (it = bookList.begin(); it != bookList.end(); it++) {
        f << it->getName() << " " << it->getISBN() << " " << it->getCno() << " " << it->getBno() << " " << it->getBn();
        i++;
        if (i != bookList.size()) {
            f << endl;
        }
    }
    f.close();
};
