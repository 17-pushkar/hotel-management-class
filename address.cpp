#include <iostream>
#include <vector>
#include <typeinfo>
using namespace std;

// ----------------------------------
// Address Class
// ----------------------------------
class Address {
public:
    string city, state;
    int pincode;

    void input() {
        cout << "Enter City: ";
        cin >> city;
        cout << "Enter State: ";
        cin >> state;
        cout << "Enter Pincode: ";
        cin >> pincode;
    }

    void display() {
        cout << city << ", " << state << " - " << pincode << endl;
    }
};

// ----------------------------------
// Base Class: Person
// ----------------------------------
class Person {
public:
    string name;
    Address addr;

    virtual void input() {
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Address:\n";
        addr.input();
    }

    virtual void display() {
        cout << "Name: " << name << endl;
        cout << "Address: ";
        addr.display();
    }

    virtual ~Person() {}
};

// ----------------------------------
// Employee (Inheritance from Person)
// ----------------------------------
class Employee : public Person {
public:
    int empID;
    float salary;

    void input() override {
        Person::input();
        cout << "Enter Employee ID: ";
        cin >> empID;
        cout << "Enter Salary: ";
        cin >> salary;
    }

    void display() override {
        Person::display();
        cout << "Employee ID: " << empID << endl;
        cout << "Salary: " << salary << endl;
    }
};

// ----------------------------------
// Payment (Polymorphism)
// ----------------------------------
class Payment {
public:
    virtual void pay(float amount) {
        cout << "Processing Payment of Rs." << amount << endl;
    }
    virtual ~Payment() {}
};

class CashPayment : public Payment {
public:
    void pay(float amount) override {
        cout << "Cash Payment Successful. Amount Paid: Rs." << amount << endl;
    }
};

class CardPayment : public Payment {
public:
    void pay(float amount) override {
        cout << "Card Payment Successful. Amount Paid: Rs." << amount << endl;
    }
};

// ----------------------------------
// Room Service
// ----------------------------------
class RoomService {
public:
    string item;
    float price;

    void input() {
        cout << "Enter Room Service Item: ";
        cin >> item;
        cout << "Enter Price: ";
        cin >> price;
    }

    void display() {
        cout << "Room Service Item: " << item << endl;
        cout << "Price: Rs." << price << endl;
    }
};

// ----------------------------------
// Template Class for Storing Lists
// ----------------------------------
template <class T>
class HotelList {
public:
    vector<T> data;

    void add(T obj) {
        data.push_back(obj);
    }

    void show() {
        for (auto &x : data) {
            cout << "\nObject Type (RTTI): " << typeid(x).name() << endl;
            x.display();
        }
    }
};

// ----------------------------------
// MAIN FUNCTION
// ----------------------------------
int main() {

    // ========== Employee Details ==========
    Employee e;
    cout << "\n--- Enter Employee Details ---\n";
    e.input();

    cout << "\n--- Employee Details ---\n";
    e.display();
    cout << "RTTI Type: " << typeid(e).name() << endl;

    // ========== Room Service Input ==========
    RoomService rs;
    cout << "\n--- Enter Room Service Details ---\n";
    rs.input();

    cout << "\n--- Room Service Summary ---\n";
    rs.display();

    // ========== Template List Example ==========
    HotelList<RoomService> serviceList;
    serviceList.add(rs);

    cout << "\n--- All Room Services (Template + RTTI) ---\n";
    serviceList.show();

    // ========== Payment Processing ==========
    Payment *p;
    int choice;

    cout << "\nSelect Payment Method:\n1. Cash\n2. Card\nEnter choice: ";
    cin >> choice;

    if (choice == 1)
        p = new CashPayment();
    else
        p = new CardPayment();

    p->pay(rs.price);
    delete p;

    return 0;
}
