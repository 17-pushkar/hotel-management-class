
#include <iostream>
#include <vector>
using namespace std;

class RoomType {
    string name;
    double price;
    vector<string> features;
    int availableCount;

public:
    RoomType(string n, double p, vector<string> f, int count)
        : name(n), price(p), features(f), availableCount(count) {}

    void displayDetails() const {
        cout << "\nRoom Type: " << name << "\nPrice per night: ₹" << price
             << "\nAvailable: " << availableCount << "\nFeatures:\n";
        for (const auto& feature : features)
            cout << " - " << feature << endl;
    }

    bool bookRoom() {
        if (availableCount > 0) {
            availableCount--;
            cout << name << " booked successfully.\n";
            return true;
        } else {
            cout << name << " is fully booked.\n";
            return false;
        }
    }

    void cancelRoom() {
        availableCount++;
        cout << "Booking cancelled for " << name << ".\n";
    }

    string getName() const { return name; }
};

class Hotel {
    vector<RoomType> roomTypes;

public:
    void addRoomType(const RoomType& rt) {
        roomTypes.push_back(rt);
    }

    void showRoomTypes() const {
        for (const auto& rt : roomTypes)
            rt.displayDetails();
    }

    void bookRoomType(const string& typeName) {
        for (auto& rt : roomTypes) {
            if (rt.getName() == typeName) {
                rt.bookRoom();
                return;
            }
        }
        cout << "Room type not found.\n";
    }

    void cancelRoomType(const string& typeName) {
        for (auto& rt : roomTypes) {
            if (rt.getName() == typeName) {
                rt.cancelRoom();
                return;
            }
        }
        cout << "Room type not found.\n";
    }
};

int main() {
    Hotel hotel;
    hotel.addRoomType(RoomType("Standard", 1000.0, {"TV", "WiFi", "AC"}, 5));
    hotel.addRoomType(RoomType("Deluxe", 2000.0, {"TV", "WiFi", "AC", "Mini Fridge"}, 3));
    hotel.addRoomType(RoomType("Suite", 3500.0, {"TV", "WiFi", "AC", "Mini Fridge", "Living Area"}, 2));

    int choice;
    string typeName;

    do {
        cout << "\n--- Hotel Room Type Menu ---\n";
        cout << "1. Show Room Types\n2. Book Room Type\n3. Cancel Booking\n4. Exit\nEnter choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline

        switch (choice) {
            case 1:
                hotel.showRoomTypes();
                break;
            case 2:
                cout << "Enter room type to book (Standard/Deluxe/Suite): ";
                getline(cin, typeName);
                hotel.bookRoomType(typeName);
                break;
            case 3:
                cout << "Enter room type to cancel (Standard/Deluxe/Suite): ";
                getline(cin, typeName);
                hotel.cancelRoomType(typeName);
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}
