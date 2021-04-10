#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

class Book {
    int id;
    std::string name;
    int quantity;
    std::list<int> borrowers;

   public:
    Book() = default;
    Book(int _id, std::string _name = "", int _quantity = 0)
        : id(_id),
          name(_name),
          quantity(_quantity),
          borrowers(std::list<int>()) {}

    int getId() { return id; }

    std::string getName() { return name; }

    void changeName(std::string newName) { name = newName; }

    void changeQuantity(int newQuantity) { quantity = newQuantity; }

    bool setBorrow(int readerId) {
        auto it = std::find(begin(borrowers), end(borrowers), readerId);
        if (quantity == 0 || it != end(borrowers)) {
            return false;
        }
        quantity--;
        borrowers.push_back(readerId);
        return true;
    }

    bool unBorrow(int readerId) {
        auto it = std::find(begin(borrowers), end(borrowers), readerId);
        if (it == end(borrowers)) {
            return false;
        }
        quantity++;
        borrowers.erase(it);
        return true;
    }

    auto getBorrowers() { return borrowers; }

    void show() {
        std::cout << "id: " << id << std::endl;
        std::cout << "name: " << name << std::endl;
        std::cout << "quantity: " << quantity << std::endl;
    }

    friend std::istream& operator>>(std::istream& in, Book& book) {
        in >> book.id >> book.name >> book.quantity;
        int n;
        in >> n;
        int t;
        book.borrowers.clear();
        for (int i = 0; i < n; i++) {
            in >> t;
            book.borrowers.push_back(t);
        }
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const Book& book) {
        out << book.id << " " << book.name << " " << book.quantity << std::endl;
        out << book.borrowers.size() << " ";
        for (const auto& e : book.borrowers) {
            out << e << " ";
        }
        out << std::endl;
        return out;
    }
};