#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <vector>
using namespace std;

class Book {
private:
    string bname;
    string ISBN;
    string cno;
    string bno;
    int bn;
public:
    Book();
    Book(string bname, string ISBN, string cno, string bno, int bn);
    string getName() {return bname;};
    string getISBN() {return ISBN;};
    string getCno() {return cno;};
    string getBno() {return bno;};
    int getBn() {return bn;};
    void setBn(int bn) {this->bn = bn;};

    static vector<Book> bookList;
    static vector<Book> readBook(string fileName);
    static void showBooks();
    static void addBook();
    static void searchBook();
    static void deleteBook();
    static void updateBook();
    static void writeBook(string filename);
};

#endif // BOOK_H
