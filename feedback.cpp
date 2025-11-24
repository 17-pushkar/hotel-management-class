#include "Feedback.h"
#include <iostream>

void Feedback::input() {
    std::cout << "Enter Feedback: ";
    std::cin.ignore();
    std::getline(std::cin, message);
}

void Feedback::show() const {
    std::cout << "\n--- Feedback Received ---\n";
    std::cout << message << "\n";
}
