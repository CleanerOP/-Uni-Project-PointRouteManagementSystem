#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Structure to hold bus detailss
struct Bus {
    string busID;
    string contactNumber;
    string startingStop;
    string finalStop;
    vector<pair<string, string>> route; // Pair of stop name and expected time
};

// Function prototypes
void showAvailableBuses();
void searchBusData();
void adminAccess();
void readMe();
void addBus();
void updateBus();
void deleteBus();
void loadBusData(vector<Bus>& buses);
void saveBusData(const vector<Bus>& buses);

// Global vector to store bus data
vector<Bus> buses;


void showAvailableBuses() {
    // Check if there are any buses available
    if (buses.empty()) {
        cout << "\n\t\tThere are no available buses in the system.\n";
    } else {
        cout << "\n\t\tThe available buses in the system are:\n";
        for (const auto& bus : buses) {
            cout << "\t\t"<< bus.busID << "\t\t\n";  // Print the bus ID
        }
    }
}
void searchBusData() {
    string searchID;
    cout << "\t\tEnter the bus ID: ";
    cin >> searchID;

    for (const auto& bus : buses) {
        if (bus.busID == searchID) {
            cout << "\n\t\t.===========Bus data===========.\n"
                 << "\n\t\tBus ID: " << bus.busID
                 << "\n\t\tContact Number: " << bus.contactNumber
                 << "\n\t\tStarting Stop: " << bus.startingStop
                 << "\n\t\tFinal Stop: " << bus.finalStop
                 << "\n\n\t\tBus Route:\n\n\t\tStop:\t\tExpected Time:\n";
                 

            for (const auto& stop : bus.route) {
                cout << "\t\t" << stop.first << "\t\t" << stop.second << "\n";
            }
            cout<<"\n\t\t.===============================.";
            return;
        }
        
    }
    cout << "\t\tBus ID not found!\n";
}
void adminAccess() {
    string pin;
    cout << "\t\tEnter pin: ";
    cin >> pin;
    if (pin == "1234") { // Example pin 
        string adminChoice;
        cout << "\t\t1. Add Bus\n\t\t2. Update Bus Data\n\t\t3. Delete Bus Data\n\t\t4. Back\n\t\tEnter your choice: ";
        cin >> adminChoice;
        if (adminChoice == "1") {
            addBus();
        } else if (adminChoice == "2") {
            updateBus();
        } else if (adminChoice == "3") {
            deleteBus();
        } else if (adminChoice == "4") {
            cout << "\n\t\tGoing back..." << endl;
            return;
        } else {
            cout << "\t\tInvalid choice.\n";
        }
    } else {
        cout << "\t\tIncorrect pin!\n";
    }
}
void addBus() {
    Bus newBus;
    cout << "\t\tEnter bus ID: ";
    cin >> newBus.busID;
    cout << "\t\tEnter contact number: ";
    cin >> newBus.contactNumber;
    cout << "\t\tEnter starting stop: ";
    cin >> newBus.startingStop;
    cout << "\t\tEnter final stop: ";
    cin >> newBus.finalStop;

    int stopCount;
    cout << "\t\tEnter number of total stops: ";
    cin >> stopCount;

    for (int i = 1; i <= stopCount; ++i) {
        string stopName, expectedTime;
        cout << "\t\tEnter name of stop " << i << ": ";
        cin >> stopName;
        cout << "\t\tEnter expected time for stop " << i << ": ";
        cin >> expectedTime;
        newBus.route.emplace_back(stopName, expectedTime);
    }

    buses.push_back(newBus);
    saveBusData(buses);
    cout << "\t\tBus added successfully!\n";
}

void updateBus() {
    string updateID;
    cout << "\t\tEnter bus ID that you want to update: ";
    cin >> updateID;

    for (auto& bus : buses) {
        if (bus.busID == updateID) {
            cout << "\t\tEnter new contact number: ";
            cin >> bus.contactNumber;
            cout << "\t\tEnter new starting stop: ";
            cin >> bus.startingStop;
            cout << "\t\tEnter new final stop: ";
            cin >> bus.finalStop;

            int stopCount;
            cout << "\t\tEnter number of total stops: ";
            cin >> stopCount;

            bus.route.clear();
            for (int i = 1; i <= stopCount; ++i) {
                string stopName, expectedTime;
                cout << "\t\t\t\tEnter name of stop " << i << ": ";
                cin >> stopName;
                cout << "\t\t\t\tEnter expected time for stop " << i << ": ";
                cin >> expectedTime;
                bus.route.emplace_back(stopName, expectedTime);
            }

            saveBusData(buses);
            cout << "\t\t\t\tBus updated successfully!\n";
            return;
        }
    }
    cout << "\t\t\t\tBus ID not found!\n";
}

void deleteBus() {
    string deleteID;
    cout << "\t\tEnter bus ID that you want to delete: ";
    cin >> deleteID;

    for (auto it = buses.begin(); it != buses.end(); ++it) {
        if (it->busID == deleteID) {
            buses.erase(it);
            saveBusData(buses);
            cout << "\t\tBus deleted successfully!\n";
            return;
        }
    }
    cout << "\t\tBus ID not found!\n";
}

void loadBusData(vector<Bus>& buses) {
    ifstream file("bus_data.txt");
    if (file.is_open()) {
        Bus bus;
        int stopCount;
        while (file >> bus.busID >> bus.contactNumber >> bus.startingStop >> bus.finalStop >> stopCount) {
            bus.route.clear();
            for (int i = 0; i < stopCount; ++i) {
                string stopName, expectedTime;
                file >> stopName >> expectedTime;
                bus.route.emplace_back(stopName, expectedTime);
            }
            buses.push_back(bus);
        }
        file.close();
    }
}

void saveBusData(const vector<Bus>& buses) {
    ofstream file("bus_data.txt");
    if (file.is_open()) {
        for (const auto& bus : buses) {
            file << bus.busID << " " << bus.contactNumber << " " << bus.startingStop << " " << bus.finalStop << " " << bus.route.size() << "\n";
            for (const auto& stop : bus.route) {
                file << stop.first << " " << stop.second << "\n"; 
            }
        }
        file.close();
    }
}
void readMe(){
    cout << "\t\t.=============================================================================.\n";
    cout << "\t\tThe University Bus Route Management System provides students with\n";
    cout << "\t\tinformation about bus routes, including bus IDs, contact numbers, stops, and estimated times.\n";
    cout << "\t\tThe system includes an admin interface for managing bus data.\n\n";
    cout << "\t\tThe system features a user-friendly interface, ensuring easy navigation\n";
    cout << "\t\tand accessibility for both students and administrators.\n\n";
    cout << "\t\tFor students:\n\n";
    cout << "\t\tView bus routes and details.\n";
    cout << "\t\tBuses with ID \"000\" are arriving at MUET.\n";
    cout << "\t\tBuses with ID \"000*\" are departing from MUET.\n\n";
    cout << "\t\tFor admins:\n\n";
    cout << "\t\tAdmin access requires a PIN for security.\n";
    cout << "\t\tAdd a bus: Enter bus details such as ID, contact number, stops, and estimated time.\n";
    cout << "\t\tUpdate a bus: Modify existing bus details.\n";
    cout << "\t\tDelete a bus: Remove a bus from the system.\n\n";
    cout << "\t\tNote: No spaces are allowed while adding data to a bus, as it may cause the code to not work as\n";
    cout << "\t\tintended (e.g., use \"Muet_CL\" instead of \"Muet CL\").\n";
    cout << "\t\t.=============================================================================.\n";
}

int main() {

    system("color F4");


    // Clear the terminal screen
    #ifdef _WIN32 
        system("cls");
    #else 
        system("clear");
    #endif

    loadBusData(buses); // Load existing bus data from file

    string choice;
    do {
        cout << "\n\t\t.=== Bus Management System ===.\n";
        cout << "\t\t1. Show Available Buses\n";
        cout << "\t\t2. Search Bus Data\n";
        cout << "\t\t3. Admin Access\n";
        cout << "\t\t4. Exit\n";
        cout << "\t\t5. Read Me\n";
        cout << "\t\tEnter your choice: ";
        cin >> choice;

        if (choice=="1") showAvailableBuses(); 
        else if (choice=="2") searchBusData(); 
        else if (choice=="3")adminAccess(); 
        else if (choice=="4")cout << "\t\tThanks for using this program. Safe travels!\n";
        else if (choice=="5")readMe();
        else cout << "\t\tInvalid choice/input. Try again.\n";
    } while (choice != "4");

    return 0;
}
