#include <iostream>
#include <string>
#include <vector>
using namespace std;

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

class User {
protected:
    int id;
    string name;
    int borrowedCount;
public:
    User(int i, string n) : id(i), name(n), borrowedCount(0) {}
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
    string getName() { return name; }
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

class Library {
private:
    vector<Book> books;
    vector<User*> users;
public:
    ~Library() {
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

    // 借书功能
    void borrowBook(int uid, int bid) {
        User* user = nullptr;
        //查找用户
        for (size_t i = 0; i < users.size(); i++) {
            if (users[i]->getId() == uid) {
                user = users[i];
                break;
            }
        }
        if (!user) { cout << "错误：未找到该用户！" << endl; return; }
        //校验借阅上限
        if (user->getBorrowedCount() >= user->getMaxLimit()) {
            cout << "错误：已达借阅上限！" << endl;
            return;
        }
        //查找图书并借出
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].getId() == bid) {
                if (books[i].getStatus()) {
                    cout << "错误：该书已借出！" << endl;
                    return;
                }
                books[i].setBorrowed(true);
                user->incBorrow();
                cout << user->getName() << " 成功借出《" << books[i].getTitle() << "》" << endl;
                return;
            }
        }
        cout << "错误：未找到该图书！" << endl;
    }

    //还书功能
    void returnBook(int bid) {
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].getId() == bid) {
                if (!books[i].getStatus()) {
                    cout << "错误：该书未被借出！" << endl;
                    return;
                }
                books[i].setBorrowed(false);
                cout << "《" << books[i].getTitle() << "》 归还成功" << endl;
                return;
            }
        }
        cout << "错误：未找到该图书！" << endl;
    }
};

int main() {
    Library lib;
    lib.addBook(101, "C++");
    lib.addUser(new Student(1, "张三"));

    lib.borrowBook(1, 101);
    lib.showAllBooks();
    lib.returnBook(101); 
    lib.showAllBooks();
    return 0;
}

