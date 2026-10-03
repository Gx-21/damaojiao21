#include <iostream>
#include <string>
using namespace std;

//图书类
class Book {
private:
    int id;
    string title;
    bool isBorrowed;
public:
    Book(int i, string t) : id(i), title(t), isBorrowed(false) {}
    int getId() { return id; }
    string getTitle() { return title; }
    bool getStatus() { return isBorrowed; }
    void setBorrowed(bool s) { isBorrowed = s; }
    void display() {
        cout << "书号:" << id << " 书名:" << title
            << " 状态:" << (isBorrowed ? "已借出" : "可借阅") << endl;
    }
};

//用户类
class User {
private:
    int id;
    string name;
    int borrowedCount;
public:
    User(int i, string n) : id(i), name(n), borrowedCount(0) {}
    int getId() { return id; }
    string getName() { return name; }
    void incBorrow() { borrowedCount++; }
    void decBorrow() { borrowedCount--; }
    void display() {
        cout << "编号:" << id << " 姓名:" << name
            << " 已借数量:" << borrowedCount << endl;
    }
};

int main() {
    Book b1(101, "C++入门");
    User u1(1, "张三");
    b1.display();
    u1.display();
    return 0;
}
