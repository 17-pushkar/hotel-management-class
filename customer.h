#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>

class Customer {
    int id;
    std::string name;
    std::string phone;

public:
    Customer();
    Customer(int i, std::string n, std::string p);

    void input();
    void display() const;

    int getId() const { return id; }
    std::string getName() const { return name; }
};

#endif
