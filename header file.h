#ifndef HOTEL_MANAGEMENT_H
#define HOTEL_MANAGEMENT_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

/* ========================================================
   1. CUSTOM EXCEPTION CLASS
   ======================================================== */
class LoggerException : public exception {
    string msg;
public:
    LoggerException(const string& m) : msg(m) {}
    const char* what() const noexcept override {
        return msg.c_str();
    }
};

/* ========================================================
   2. BASE CLASS: STAFF
   ======================================================== */
class Staff {
protected:
    int staffId;
    string name;
    string role;

public:
    Staff() : staffId(0), name("unknown"), role("unknown") {}

    Staff(int id, const string& n, const string& r)
        : staffId(id), name(n), role(r) {}

    virtual ~Staff() {}

    int getId() const { return staffId; }
    string getName() const { return name; }
    string getRole() const { return role; }

    virtual void work() = 0;  
};

/* ========================================================
   3. DERIVED CLASS: WAITER
   ======================================================== */
class Waiter : public Staff {
private:
    int tableNo;

public:
    Waiter() : Staff(), tableNo(0) {}

    Waiter(int id, const string& n, int tno)
        : Staff(id, n, "Waiter"), tableNo(tno) {}

    void work() override {
        cout << name << " is serving customers at table "
             << tableNo << endl;
    }

    ~Waiter() {}
};

/* ========================================================
   4. DERIVED CLASS: HOUSEKEEPING
   ======================================================== */
class Housekeeping : public Staff {
private:
    int floorNumber;
    int roomsCleaned;

public:
    Housekeeping() : Staff(), floorNumber(0), roomsCleaned(0) {}

    Housekeeping(int id, const string& n, int fno, int r)
        : Staff(id, n, "Housekeeping"), floorNumber(fno), roomsCleaned(r) {}

    void work() override {
        cout << name << " is cleaning rooms on floor "
             << floorNumber << endl;
    }

    void cleanRoom() {
        roomsCleaned++;
        cout << name << " cleaned a room. Total = "
             << roomsCleaned << endl;
    }

    ~Housekeeping() {}
};

/* ========================================================
   5. DERIVED CLASS: MAINTENANCE
   ======================================================== */
class Maintenance : public Staff {
private:
    int toolsCount;
    bool onDuty;

public:
    Maintenance() : Staff(), toolsCount(0), onDuty(false) {}

    Maintenance(int id, const string& n, int tools)
        : Staff(id, n, "Maintenance"), toolsCount(tools), onDuty(false) {}

    void work() override {
        if (onDuty)
            cout << name << " is fixing issues using " << toolsCount << " tools.\n";
        else
            cout << name << " is available for maintenance tasks.\n";
    }

    void reportIssue(const string& issue) {
        onDuty = true;
        cout << name << " started working on: " << issue << endl;
    }

    ~Maintenance() {}
};

/* ========================================================
   6. LOGGER CLASS + OPERATOR <<
   ======================================================== */
class Logger {
private:
    ofstream file;

public:
    Logger(const string& filename) {
        file.open(filename, ios::app);
        if (!file.is_open())
            throw LoggerException("Could not open log file: " + filename);
    }

    Logger& operator<<(const string& msg) {
        file << msg << endl;
        return *this;
    }

    ~Logger() {
        if (file.is_open())
            file.close();
    }
};

/* ========================================================
   7. TEMPLATE CLASS: REPORT
   ======================================================== */
template <typename T>
class Report {
private:
    vector<T*> records;
    string filename;

public:
    Report(const string& file) : filename(file) {}

    void addRecord(T* obj) {
        records.push_back(obj);
    }

    void save() {
        ofstream out(filename);

        if (!out.is_open())
            throw LoggerException("Unable to save report");

        for (auto obj : records) {
            out << obj->getId() << " - "
                << obj->getName() << " - "
                << obj->getRole() << endl;
        }
        out.close();
    }
};

/* ========================================================
   8. HOTEL CLASS
   ======================================================== */
class Hotel {
private:
    vector<Staff*> staffList;
    Logger logger;

public:
    Hotel() : logger("hotel.log") {}

    void addStaff(Staff* s) {
        staffList.push_back(s);
        logger << "Added staff: " + s->getName();
    }

    void showAllStaff() const {
        cout << "\n---- STAFF LIST ----\n";
        for (auto s : staffList) {
            cout << s->getId() << " | "
                 << s->getName() << " | "
                 << s->getRole() << endl;
        }
    }

    void generateReport(const string& file) {
        Report<Staff> rep(file);
        for (auto s : staffList)
            rep.addRecord(s);
        rep.save();
        logger << "Report generated: " + file;
    }

    ~Hotel() {
        for (auto s : staffList)
            delete s;
        logger << "Hotel destroyed";
    }
};

#endif  // HOTEL_MANAGEMENT_H
