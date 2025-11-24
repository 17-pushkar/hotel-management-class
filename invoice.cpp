#include "Invoice.h"
#include <iostream>

Invoice::Invoice(std::string name, double amt)
    : customerName(name), amount(amt) {}

void Invoice::printInvoice() const {
    std::cout << "\n--- Invoice ---\n";
    std::cout << "Customer: " << customerName << "\n";
    std::cout << "Amount: Rs." << amount << "\n";
}
