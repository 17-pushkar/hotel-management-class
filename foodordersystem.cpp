#include <iostream>
#include <vector>
using namespace std;

// Base class
class MenuItem {
public:
    string name;
    double price;
    MenuItem(string n, double p) : name(n), price(p) {}
    virtual void display() const {
        cout << name << " - ₹" << price;
    }
    virtual string getCategory() const = 0;
    virtual ~MenuItem() {}
};

// Derived classes
class MainCourse : public MenuItem {
public:
    MainCourse(string n, double p) : MenuItem(n, p) {}
    void display() const override {
        cout << "[Main Course] ";
        MenuItem::display();
        cout << endl;
    }
    string getCategory() const override { return "Main Course"; }
};

class Drink : public MenuItem {
public:
    Drink(string n, double p) : MenuItem(n, p) {}
    void display() const override {
        cout << "[Drink] ";
        MenuItem::display();
        cout << endl;
    }
    string getCategory() const override { return "Drink"; }
};

class Dessert : public MenuItem {
public:
    Dessert(string n, double p) : MenuItem(n, p) {}
    void display() const override {
        cout << "[Dessert] ";
        MenuItem::display();
        cout << endl;
    }
    string getCategory() const override { return "Dessert"; }
};

// Food ordering system
class FoodOrder {
    vector<MenuItem*> menu;
    vector<MenuItem*> cart;
public:
    void loadMenu() {
        menu.push_back(new MainCourse("Burger", 120));
        menu.push_back(new MainCourse("Pizza", 250));
        menu.push_back(new Drink("Coke", 50));
        menu.push_back(new Drink("Lemonade", 40));
        menu.push_back(new Dessert("Ice Cream", 80));
        menu.push_back(new Dessert("Brownie", 90));
    }

    void showMenu() {
        cout << "\n--- Menu ---\n";
        for (int i = 0; i < menu.size(); ++i) {
            cout << i + 1 << ". ";
            menu[i]->display();
        }
    }

    void placeOrder(int choice) {
        if (choice > 0 && choice <= menu.size()) {
            cart.push_back(menu[choice - 1]);
            cout << "✅ Added to cart: " << menu[choice - 1]->name << endl;
        } else {
            cout << "❌ Invalid choice.\n";
        }
    }

    void showBill() {
        if (cart.empty()) {
            cout << "\n🧾 Your cart is empty.\n";
            return;
        }
        double total = 0;
        cout << "\n--- Bill Summary ---\n";
        for (auto item : cart) {
            item->display();
            total += item->price;
        }
        cout << "---------------------\n";
        cout << "Total Amount: ₹" << total << endl;
    }

    ~FoodOrder() {
        for (auto item : menu) delete item;
    }
};

// Main function
int main() {
    FoodOrder order;
    order.loadMenu();

    int choice;
    do {
        cout << "\n=== Food Ordering System ===\n";
        cout << "1. Show Menu\n";
        cout << "2. Place Order\n";
        cout << "3. View Bill\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                order.showMenu();
                break;
            case 2: {
                int item;
                order.showMenu();
                cout << "Enter item number to order: ";
                cin >> item;
                order.placeOrder(item);
                break;
            }
            case 3:
                order.showBill();
                break;
            case 4:
                cout << "👋 Thank you! Visit again.\n";
                break;
            default:
                cout << "❗ Invalid option. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
