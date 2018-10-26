#ifndef RECORD_H
#define RECORD_H
#include <vector>
using namespace std;
class Record {
private:
    int tabNo;
    int dno;
    double price;
public:
    Record();
    Record(int tabNo, int dno, double price);
    int getTabNo() {return tabNo;};
    int getDno() {return dno;};
    int getPrice() {return price;};
    void setPrice(double price) {this->price = price;};

    static vector<Record> records;
    static void updateRecord(int tabNo, int dno, double price);
    static void showRecords();
    static void showConsumes();
};

#endif // RECORD_H


