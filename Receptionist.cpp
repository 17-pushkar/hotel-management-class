#include "Receptionist.h"
#include <iostream>

Booking Receptionist::createBooking() {
    Customer c;
    c.input();

    int room;
    std::cout << "Enter Room No: ";
    std::cin >> room;

    Booking b(room, c);

    std::cout << "\nBooking Created Successfully!\n";
    return b;
}

void Receptionist::generateInvoice(const Booking &b) {
    Invoice inv(b.getCustomerName(), 1500);
    inv.printInvoice();
}

void Receptionist::laundryService() {
    LaundryService ls;
    int count;
    std::cout << "Enter number of clothes: ";
    std::cin >> count;

    double bill = ls.calculateBill(count);
    std::cout << "Laundry Bill: Rs." << bill << "\n";
}

void Receptionist::takeFeedback() {
    Feedback f;
    f.input();
    f.show();
}
