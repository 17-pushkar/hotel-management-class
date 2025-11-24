#ifndef RECEPTIONIST_H
#define RECEPTIONIST_H

#include "Customer.h"
#include "Booking.h"
#include "Invoice.h"
#include "LaundryService.h"
#include "Feedback.h"

class Receptionist {
public:
    Booking createBooking();
    void generateInvoice(const Booking &b);
    void laundryService();
    void takeFeedback();
};

#endif
