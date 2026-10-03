#include <iostream>
#include <string>
#include <vector>
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
    virtual ~User() {} 
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
    int getBorrowedCount() { return borrowedCount; }
};

class Student : public User {
public:
    Student(int i, string n) : User(i, n) {}
    int getMaxLimit() override { return 3; }
    string getRole() override { return "学生"; }
};

class Teacher : public User {
public:
    Teacher(int i, string n) : User(i, n) {}
    int getMaxLimit() override { return 10; }
    string getRole() override { return "教师"; }
};

//图书馆类：组合Book和User
class Library {
private:
    vector<Book> books;// 组合关系：图书馆包含图书
    vector<User*> users;// 组合关系：图书馆包含用户
public:
    ~Library() { // 释放堆内存
        for (size_t i = 0; i < users.size(); i++)
            delete users[i];
    }
    void addBook(int id, string title) {
        books.push_back(Book(id, title));
        cout << "图书添加成功！" << endl;
    }
    void addUser(User* u) {
        users.push_back(u);
        cout << "用户注册成功！" << endl;
    }
    void showAllBooks() {
        cout << "\n===== 图书列表 =====" << endl;
        for (size_t i = 0; i < books.size(); i++)
            books[i].display();
    }
    void showAllUsers() {
        cout << "\n===== 用户列表 =====" << endl;
        for (size_t i = 0; i < users.size(); i++)
            users[i]->display();
    }
};

int main() {
    Library lib;
    lib.addBook(101, "C++");
    lib.addBook(102, "数据结构");
    lib.addUser(new Student(1, "mj"));
    lib.addUser(new Teacher(2, "老师"));

    lib.showAllBooks();
    lib.showAllUsers();
    return 0;
}
