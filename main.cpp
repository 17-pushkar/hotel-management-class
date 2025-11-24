#include <iostream>
#include "Receptionist.h"

using namespace std;

int main() {
    Receptionist r;
    Booking b;

    int choice;

    while (true) {
        cout << "\n--- HOTEL SYSTEM ---\n";
        cout << "1. New Booking\n";
        cout << "2. Generate Invoice\n";
        cout << "3. Laundry Service\n";
        cout << "4. Feedback\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: b = r.createBooking(); break;
            case 2: r.generateInvoice(b); break;
            case 3: r.laundryService(); break;
            case 4: r.takeFeedback(); break;
            case 5: return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}
