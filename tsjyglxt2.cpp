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

//用户基类
class User {
protected:
    int id;
    string name;
    int borrowedCount;
public:
    User(int i, string n) : id(i), name(n), borrowedCount(0) {}
    //纯虚函数，实现多态
    virtual int getMaxLimit() = 0;
    virtual string getRole() = 0;
    virtual void display() {
        cout << "编号:" << id << " 姓名:" << name
            << " 角色:" << getRole() << " 已借:" << borrowedCount
            << " 上限:" << getMaxLimit() << endl;
    }
    void incBorrow() { borrowedCount++; }
    void decBorrow() { borrowedCount--; }
    int getId() { return id; }
};

//派生子类：学生
class Student : public User {
public:
    Student(int i, string n) : User(i, n) {}
    int getMaxLimit() override { return 3; }
    string getRole() override { return "学生"; }
};

//派生子类：教师
class Teacher : public User {
public:
    Teacher(int i, string n) : User(i, n) {}
    int getMaxLimit() override { return 10; }
    string getRole() override { return "教师"; }
};

int main() {
    Book b1(101, "C++入门");
    Student s1(1, "张三");
    Teacher t1(2, "李老师");

    b1.display();// 多态调用
    s1.display(); 
    t1.display();
    return 0;
}
