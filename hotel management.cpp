#include<iostream>
using namespace std;

class HotelException : public runtime_error {
public:
    HotelException(const string& message) : runtime_error("HOTEL SYSTEM ERROR: " + message) {}
};

class BookingException : public HotelException {
public:
    BookingException(const string& message) : HotelException("Booking Failure - " + message) {}
};

class ServiceException : public HotelException {
public:
    ServiceException(const string& message) : HotelException("Service Failure - " + message) {}
};

struct ReservationDate {
    int day;
    int month;
    int year;

    string toString() {
        stringstream ss;
        ss << day << "/" << month << "/" << year;
        return ss.str();
    }
};

class IRoomManagement {
public:
    virtual void checkIn(int roomId, const string& guestName, const ReservationDate& checkInDate) = 0;
    virtual void checkOut(int roomId, const ReservationDate& checkOutDate) = 0;
    virtual ~IRoomManagement() = default;
};

class IService {
public:
    virtual void executeService(const string& details) = 0;
    virtual string getServiceName() = 0;
    virtual ~IService() = default;
};

class TransportService : public IService {
public:
    string getServiceName() override { return "Transport Service"; }
    void executeService(const string& details) override {
        cout << "[SERVICE] Transport: Dispatching vehicle for: " << details << endl;
    }
};

class SecurityGuard : public IService {
public:
    string getServiceName() override { return "Security Guard"; }
    void executeService(const string& details) override {
        cout << "[SERVICE] Security: Guard inspecting area: " << details << endl;
        if (details.find("emergency") != string::npos) {
             // Throws an exception for serious events
             throw ServiceException("Security reported an emergency at " + details);
        }
    }
};

class HotelManager : public IRoomManagement {
private:
    vector<int> occupiedRoomIDs;
    vector<unique_ptr<IService>> availableServices;

    bool isRoomOccupied(int roomId) {
        return find(occupiedRoomIDs.begin(), occupiedRoomIDs.end(), roomId) != occupiedRoomIDs.end();
    }

    void sendInternalNotification(const string& message, const string& eventType) {
        cout << "--- [NOTIFICATION: " << eventType << "] ---\n";
        cout << "  Detail: " << message << endl;
        cout << "--------------------------------\n";
    }

public:
    HotelManager() {
        // Initialize services using polymorphism
        availableServices.push_back(make_unique<TransportService>());
        availableServices.push_back(make_unique<SecurityGuard>());
    }

    void checkIn(int roomId, const string& guestName, const ReservationDate& checkInDate) override {
        if (isRoomOccupied(roomId)) {
            throw BookingException("Room " + to_string(roomId) + " is already occupied.");
        }
        
        occupiedRoomIDs.push_back(roomId);
        cout << "CHECK-IN SUCCESS: Guest " << guestName << " assigned Room " << roomId << "." << endl;
        sendInternalNotification("Room " + to_string(roomId) + " is occupied by " + guestName, "Guest Check-In");
    }

    void checkOut(int roomId, const ReservationDate& checkOutDate) override {
        if (!isRoomOccupied(roomId)) {
            throw BookingException("Room " + to_string(roomId) + " is already vacant.");
        }

        occupiedRoomIDs.erase(remove(occupiedRoomIDs.begin(), occupiedRoomIDs.end(), roomId), occupiedRoomIDs.end());
        
        cout << "CHECK-OUT SUCCESS: Room " << roomId << " vacated on " << checkOutDate.toString() << "." << endl;
        sendInternalNotification("Room " + to_string(roomId) + " is now vacant.", "Guest Check-Out");
    }
    
    void requestService(const string& serviceName, const string& details) {
        cout << "\n[Service Request] Processing: " << serviceName << endl;
        
        for (const auto& service : availableServices) {
            if (service->getServiceName() == serviceName) {
                try {
                    // Polymorphism
                    service->executeService(details);
                } catch (const ServiceException& e) {
                    cerr << "!!! CAUGHT EXCEPTION: " << e.what() << " !!!" << endl;
                    sendInternalNotification(e.what(), "Critical Alert");
                }
                return;
            }
        }
        cout << "SERVICE ERROR: Requested service '" << serviceName << "' is not available." << endl;
    }
};
