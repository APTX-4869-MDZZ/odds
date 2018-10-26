#ifndef EBOOK_H
#define EBOOK_H
#include <string>
#include <vector>
using namespace std;

class Ebook {
private:
    string book;
    string name;
public:
    Ebook();
    Ebook(string book, string name):
        book(book),
        name(name)
    {
    };
    string getBook() {return book;};
    string getName() {return name;};

    static vector<Ebook> ebookList;
    static vector<Ebook> readEbook(string fileName);
    static void addEbook(Ebook ebook) {ebookList.push_back(ebook);};
    static void writeEbook(string filename);
};

#endif // EBOOK_H
