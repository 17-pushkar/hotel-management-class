#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include "Customer.h"

class Booking {
    int roomNo;
    Customer customer;

public:
    Booking();
    Booking(int r, const Customer &c);

    void showBooking() const;
};

#endif
