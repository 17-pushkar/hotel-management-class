#include "Booking.h"
#include <iostream>

Booking::Booking() : roomNo(0), customer() {}

Booking::Booking(int r, const Customer &c)
    : roomNo(r), customer(c) {}

void Booking::showBooking() const {
    std::cout << "\n--- Booking Details ---\n";
    std::cout << "Room No: " << roomNo << "\n";
    customer.display();
}
