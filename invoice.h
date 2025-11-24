#ifndef INVOICE_H
#define INVOICE_H

#include <string>

class Invoice {
    std::string customerName;
    double amount;

public:
    Invoice(std::string name = "", double amt = 0);
    void printInvoice() const;
};

#endif
