#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <unordered_map>

#include "Book.hpp"

class Reader;

std::unordered_map<int, Book> Books;
std::unordered_map<int, std::shared_ptr<Reader>> Readers;

class Reader {
    int id;
    std::string name;
    std::list<int> borrowedBooks;

   public:
    Reader() = default;
    Reader(int _id, std::string _name, std::list<int> _books = std::list<int>())
        : id(_id), name(_name), borrowedBooks(_books) {}

    auto getId() { return id; }

    auto getName() { return name; }

    // 修改读者信息
    void changeInfo() {
        puts(
            "输入1修改读者名\n输入2给这位用户借阅图书\n输入3归还这位用户借阅的"
            "图书\n其他输入返回");
        int op;
        std::cin >> op;
        switch (op) {
            case 1:
                puts("输入新的读者名称");
                std::cin >> name;
                return;
            case 2:
                borrowBook();
                return;
            case 3:
                returnBook();
            default:
                return;
        }
    }

    // 借书
    void borrowBook() {
        puts("所有书籍如下:");
        for (auto [k, v] : Books) {
            printf("* %d %s\n", k, v.getName().c_str());
        }
        std::cout << "请输入要借阅的书籍号" << std::endl;
        int bookId;
        std::cin >> bookId;
        if (Books[bookId].setBorrow(id)) {
            borrowedBooks.push_back(bookId);
            std::cout << "借阅成功" << std::endl;
            return;
        }
        std::cout << "此书已被借空活着您已经拥有此书" << std::endl;
    }

    // 还书
    void returnBook() {
        std::cout << "请输入要归还的书籍号" << std::endl;
        int bookId;
        std::cin >> bookId;
        auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), bookId);
        if (it != end(borrowedBooks)) {
            if (Books[bookId].unBorrow(id)) {
                std::cout << "归还成功" << std::endl;
                borrowedBooks.erase(it);
                return;
            }
        }
        std::cout << "归还失败" << std::endl;
    }

    // 按书籍编号查询书籍信息
    void queryById() {
        std::cout << "请输入要查询的书籍号" << std::endl;
        int bookId;
        std::cin >> bookId;
        queryBook(bookId);
    }

    // 按书籍名称查询书籍信息
    void queryByName() {
        std::cout << "请输入要查询的书籍名称" << std::endl;
        std::string bookName;
        std::cin >> bookName;
        for (auto [k, v] : Books) {
            if (v.getName() == bookName) {
                queryBook(k);
                return;
            }
        }
        std::cout << "查无此书" << std::endl;
    }

    friend std::istream &operator>>(std::istream &in, Reader &reader) {
        in >> reader.id >> reader.name;
        int n;
        in >> n;
        reader.borrowedBooks = std::list<int>();
        int t;
        for (int i = 0; i < n; i++) {
            in >> t;
            reader.borrowedBooks.push_back(t);
        }
        return in;
    }

    friend std::ostream &operator<<(std::ostream &out, const Reader &reader) {
        out << reader.id << " " << reader.name << std::endl;
        out << reader.borrowedBooks.size() << " ";
        for (const auto &e : reader.borrowedBooks) {
            out << e << " ";
        }
        out << std::endl;
        return out;
    }

   private:
    void queryBook(int bookId) {
        if (!Books.count(bookId)) {
            std::cout << "查无此书" << std::endl;
            return;
        }
        auto book = Books[bookId];
        std::cout << "该书基本信息：" << std::endl;
        book.show();
        auto borrowers = book.getBorrowers();
        printf("借走该书的人有%ld人，如下：\n", borrowers.size());
        for (const auto &e : borrowers) {
            std::cout << "***********" << std::endl;
            std::cout << "  id: " << Readers[e]->id << std::endl;
            std::cout << "  name: " << Readers[e]->name << std::endl;
            std::cout << "***********" << std::endl;
        }
    }
};

class Administrator {
   public:
    void inputBook() {
        int id;
        std::string name;
        int quantity;
        std::cout << "请输入书籍信息" << std::endl;
        std::cin >> id >> name >> quantity;
        if (Books.count(id)) {
            std::cout << "该书已经存在" << std::endl;
            return;
        }
        Books[id] = Book(id, name, quantity);
    }

    // 修改书籍名称
    void alterBookName() {
        int id;
        std::cout << "请输入要修改的书籍号以及新的书名" << std::endl;
        std::cin >> id;
        std::string newName;
        std::cin >> newName;
        Books[id].changeName(newName);
    }

    // 修改书籍数量
    void alterBookQuantity() {
        std::cout << "请输入要修改的书籍号以及新的书籍数量" << std::endl;
        int id, newQuantity;
        std::cin >> id >> newQuantity;
        Books[id].changeQuantity(newQuantity);
    }

    // 删除图书
    void deleteBook() {
        int id;
        std::cout << "请输入读者id" << std::endl;
        std::cin >> id;
        if (Books.count(id)) {
            Books.erase(id);
            std::cout << "删除成功" << std::endl;
        } else {
            std::cout << "删除失败" << std::endl;
        }
    }

    // 录入读者信息
    void inputReader() {
        int id;
        std::string name;
        std::cout << "请输入读者信息" << std::endl;
        std::cin >> id >> name;
        if (Readers.count(id)) {
            std::cout << "该读者已经存在" << std::endl;
            return;
        }
        Readers[id] = std::make_shared<Reader>(id, name);
    }

    // 修改读者信息
    void alterReader() {
        int id;
        std::cout << "请输入读者id" << std::endl;
        std::cin >> id;
        if (Readers.count(id)) {
            Readers[id]->changeInfo();
            return;
        }
        std::cout << "该读者不存在" << std::endl;
    }

    // 删除读者
    void deleteReader() {
        int id;
        std::cout << "请输入读者id" << std::endl;
        std::cin >> id;
        if (Readers.count(id)) {
            Readers.erase(id);
            std::cout << "删除成功" << std::endl;
        } else {
            std::cout << "删除失败" << std::endl;
        }
    }
};

// 管理员菜单
void admin() {
    Administrator admin;
    printf("admin login in...\n");
    int op;
    while (true) {
        puts(
            "输入1录入书籍信息\n输入21修改书籍名称\n输入22修改书籍数量\n输入3删"
            "除书籍\n输入4录入用户信息\n输入5修改用户信息\n输入其他退出");
        std::cin >> op;
        switch (op) {
            case 1:
                admin.inputBook();
                break;
            case 21:
                admin.alterBookName();
                break;
            case 22:
                admin.alterBookQuantity();
                break;
            case 3:
                admin.deleteBook();
                break;
            case 4:
                admin.inputReader();
                break;
            case 5:
                admin.alterReader();
                break;
            default:
                return;
        }
    }
}

// 读者菜单
void reader(const char *name) {
    std::string nameStr(name);
    bool flag = false;
    int readerId;
    for (auto [k, v] : Readers) {
        if (v->getName() == nameStr) {
            flag = true;
            readerId = k;
        }
    }
    if (!flag) {
        puts("系统中无此用户信息，请联系管理员录入");
        return;
    }
    printf("reader login in...\n");
    printf("Hello, %s!\n", name);
    int op;
    while (true) {
        puts(
            "输入1借书\n输入2还书\n输入31按图书名称查询信息\n输入32按图书名称查"
            "询信息\n输入其他退出");
        std::cin >> op;
        switch (op) {
            case 1:
                Readers[readerId]->borrowBook();
                break;
            case 2:
                Readers[readerId]->returnBook();
                break;
            case 31:
                Readers[readerId]->queryById();
                break;
            case 32:
                Readers[readerId]->queryByName();
                break;
            default:
                return;
        }
    }
}

// 从文件恢复数据
void retrieveFromFile() {
    std::ifstream booksFile("books.dat", std::ios::in);
    Book book;
    while (booksFile >> book) {
        Books[book.getId()] = book;
    }

    booksFile.close();

    std::ifstream readersFile("users.dat", std::ios::in);
    Reader reader;
    while (readersFile >> reader) {
        Readers[reader.getId()] = std::make_shared<Reader>(reader);
    }

    readersFile.close();
}

// 将数据写回文件
void storeToFile() {
    std::ofstream booksFile("books.dat", std::ios::out | std::ios::trunc);
    for (auto book : Books) {
        booksFile << book.second << std::endl;
    }
    booksFile.close();

    std::ofstream readersFile("users.dat", std::ios::out | std::ios::trunc);
    for (auto reader : Readers) {
        readersFile << *(reader.second) << std::endl;
    }

    readersFile.close();
}

int main(int argc, char *argv[]) {
    if (argc != 3 || argv[1][0] != '-' ||
        !(argv[1][1] == 'a' || argv[1][1] == 'u')) {
        puts("invalid args");
        puts("usage: Libsim -a(-u) xxxx");
        return 0;
    }
    retrieveFromFile();
    if (strcmp(argv[1], "-a") == 0) {
        admin();
    } else if (strcmp(argv[1], "-u") == 0) {
        reader(argv[2]);
    }
    storeToFile();
    return 0;
}