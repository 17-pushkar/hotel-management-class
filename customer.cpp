#include "Customer.h"

Customer::Customer() : id(0), name(""), phone("") {}

Customer::Customer(int i, std::string n, std::string p)
    : id(i), name(n), phone(p) {}

void Customer::input() {
    std::cout << "Enter Customer ID: ";
    std::cin >> id;
    std::cout << "Enter Name: ";
    std::cin >> name;
    std::cout << "Enter Phone: ";
    std::cin >> phone;
}

void Customer::display() const {
    std::cout << "ID: " << id 
              << " | Name: " << name 
              << " | Phone: " << phone << "\n";
}
