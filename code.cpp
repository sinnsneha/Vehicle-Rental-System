#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <iomanip>
#include <utility>
#include <set>
#include <map>
using namespace std;

// VehicleInventory class to manage all vehicle availability
bool isEmployee() {
    char choice;
    cout << "\n===== Welcome to Jaypee Rental Services =====\n";
    cout << "Are you an manager of the company? (Y/N): ";
    cin >> choice;

    return (choice == 'Y' || choice == 'y');
}
bool loginUser() {
    string username, password;
    int attempts = 0;
    const int MAX_ATTEMPTS = 3;
    map<string, string> validUsers = {
        {"sneha", "giligilichoo"},
        {"sejal", "abracadabra"},
        {"saumil", "khuljaasimsim"}
    };

    while (attempts < MAX_ATTEMPTS) {
        cout << "\n===== LOGIN =====\n";
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        // Check if credentials match
        if (validUsers.find(username) != validUsers.end() && validUsers[username] == password) {
            cout << "\nLogin successful! Welcome, " << username << "!\n";
            return true;
        } else {
            attempts++;
            cout << "\nInvalid username or password. " << (MAX_ATTEMPTS - attempts)
                 << " attempts remaining.\n";
        }
    }

    cout << "\nToo many failed attempts. Please try again later.\n";
    return false;
}
class VehicleInventory {
private:
    // Vehicle counts
    int carAvailability[6] = {5, 5, 5, 5, 5, 5};
    int bikeAvailability[5] = {5, 5, 5, 5, 5};
    int cycleAvailability[3] = {5, 5, 5};

    // Vehicle names for display
    const string carNames[6] = {"Wagon-R", "SwiftDesire", "ToyotaEtios", "ToyotaInnova", "InnovaCrysta", "TempoTraveller"};
    const string bikeNames[5] = {"Activa", "Aviator", "Avenger", "Vespa", "Bullet"};
    const string cycleNames[3] = {"Mountain Bike", "Road Bike", "Hybrid Bike"};

public:
    // Constructor loads inventory from file
    VehicleInventory() {
        loadFromFile();
    }

    // Load inventory from file
    void loadFromFile() {
        ifstream in("vehicle_availability.txt");
        if (in.is_open()) {
            // Load car availability
            for (int i = 0; i < 6; i++) {
                in >> carAvailability[i];
            }
            // Load bike availability
            for (int i = 0; i < 5; i++) {
                in >> bikeAvailability[i];
            }
            // Load cycle availability
            for (int i = 0; i < 3; i++) {
                in >> cycleAvailability[i];
            }
            in.close();
        } else {
            // If file doesn't exist, use default values and save them
            saveToFile();
        }
    }

    // Save inventory to file
    void saveToFile() {
        ofstream out("vehicle_availability.txt");
        // Save car availability
        for (int i = 0; i < 6; i++) {
            out << carAvailability[i];
            if (i < 5) out << " ";
        }
        out << endl;
        // Save bike availability
        for (int i = 0; i < 5; i++) {
            out << bikeAvailability[i];
            if (i < 4) out << " ";
        }
        out << endl;
        // Save cycle availability
        for (int i = 0; i < 3; i++) {
            out << cycleAvailability[i];
            if (i < 2) out << " ";
        }
        out.close();
    }

    // Display all vehicle availability
    void displayAll() {
        cout << "\n============ VEHICLE AVAILABILITY ============\n";

        // Display car availability
        cout << "\n--- CARS ---\n";
        cout << left << setw(5) << "ID" << setw(20) << "Model" << setw(15) << "Available" << endl;
        for (int i = 0; i < 6; i++) {
            cout << left << setw(5) << i+1 << setw(20) << carNames[i] << setw(15) << carAvailability[i] << endl;
        }

        // Display bike availability
        cout << "\n--- BIKES ---\n";
        cout << left << setw(5) << "ID" << setw(20) << "Model" << setw(15) << "Available" << endl;
        for (int i = 0; i < 5; i++) {
            cout << left << setw(5) << i+1 << setw(20) << bikeNames[i] << setw(15) << bikeAvailability[i] << endl;
        }

        // Display cycle availability
        cout << "\n--- CYCLES ---\n";
        cout << left << setw(5) << "ID" << setw(20) << "Model" << setw(15) << "Available" << endl;
        for (int i = 0; i < 3; i++) {
            cout << left << setw(5) << i+1 << setw(20) << cycleNames[i] << setw(15) << cycleAvailability[i] << endl;
        }

        cout << "===========================================\n";
    }

    // Update car availability
    void updateCarAvailability(int carIndex, int change) {
        if (carIndex >= 0 && carIndex < 6) {
            if (carAvailability[carIndex] + change >= 0) {
                carAvailability[carIndex] += change;
                saveToFile();
            }
        }
    }

    // Update bike availability
    void updateBikeAvailability(int bikeIndex, int change) {
        if (bikeIndex >= 0 && bikeIndex < 5) {
            if (bikeAvailability[bikeIndex] + change >= 0) {
                bikeAvailability[bikeIndex] += change;
                saveToFile();
            }
        }
    }

    // Update cycle availability
    void updateCycleAvailability(int cycleIndex, int change) {
        if (cycleIndex >= 0 && cycleIndex < 3) {
            if (cycleAvailability[cycleIndex] + change >= 0) {
                cycleAvailability[cycleIndex] += change;
                saveToFile();
            }
        }
    }

    // Set specific vehicle availability (for manager)
    void setVehicleAvailability(int type, int index, int count) {
        if (count < 0) return;

        if (type == 1) { // Cars
            if (index >= 0 && index < 6) {
                carAvailability[index] = count;
            }
        } else if (type == 2) { // Bikes
            if (index >= 0 && index < 5) {
                bikeAvailability[index] = count;
            }
        } else if (type == 3) { // Cycles
            if (index >= 0 && index < 3) {
                cycleAvailability[index] = count;
            }
        }
        saveToFile();
    }

    // Check if vehicle is available
    bool isCarAvailable(int carIndex) {
        return (carIndex >= 0 && carIndex < 6 && carAvailability[carIndex] > 0);
    }

    bool isBikeAvailable(int bikeIndex) {
        return (bikeIndex >= 0 && bikeIndex < 5 && bikeAvailability[bikeIndex] > 0);
    }

    bool isCycleAvailable(int cycleIndex) {
        return (cycleIndex >= 0 && cycleIndex < 3 && cycleAvailability[cycleIndex] > 0);
    }

    // Get vehicle name by index
    string getCarName(int index) {
        if (index >= 0 && index < 6) {
            return carNames[index];
        }
        return "Unknown Car";
    }

    string getBikeName(int index) {
        if (index >= 0 && index < 5) {
            return bikeNames[index];
        }
        return "Unknown Bike";
    }

    string getCycleName(int index) {
        if (index >= 0 && index < 3) {
            return cycleNames[index];
        }
        return "Unknown Cycle";
    }

    // Get available count
    int getCarAvailability(int index) {
        if (index >= 0 && index < 6) {
            return carAvailability[index];
        }
        return 0;
    }

    int getBikeAvailability(int index) {
        if (index >= 0 && index < 5) {
            return bikeAvailability[index];
        }
        return 0;
    }

    int getCycleAvailability(int index) {
        if (index >= 0 && index < 3) {
            return cycleAvailability[index];
        }
        return 0;
    }
};

// Global vehicle inventory
VehicleInventory inventory;

class Payment {
private:
    float amount;
    string paymentMethod;
    string transactionID;
    bool paymentStatus;
    time_t paymentTime;
    string vehicleID;  // To track which vehicle this payment is for

public:
    // Constructor
    Payment(float amt = 0.0, string vID = "") : amount(amt), paymentStatus(false), vehicleID(vID) {
        transactionID = generateTransactionID();
    }

    // Generate a unique transaction ID
    string generateTransactionID() {
        time_t now = time(0);
        string id = "TXN" + to_string(now) + to_string(rand() % 1000);
        return id;
    }

    // Process payment
    bool processPayment(string method) {
        paymentMethod = method;
        paymentTime = time(0);

        cout << "\n\nProcessing payment via " << method << "..." << endl;

        for(int i = 0; i < 5; i++) {
            cout << ".";
            this_thread::sleep_for(chrono::milliseconds(300));
        }

        paymentStatus = true;
        cout << "\nPayment successful!" << endl;

        saveToFile();  // Save payment info to file
        return paymentStatus;
    }

    // Display payment receipt
    void displayReceipt() {
        if(!paymentStatus) {
            cout << "\nNo payment has been processed yet." << endl;
            return;
        }

        char* dt = ctime(&paymentTime);

        cout << "\n\n***************************************" << endl;
        cout << "              PAYMENT RECEIPT" << endl;
        cout << "***************************************" << endl;
        cout << "Transaction ID : " << transactionID << endl;
        cout << "Payment Method : " << paymentMethod << endl;
        cout << "Amount Paid    : Rs. " << amount << endl;
        cout << "Date & Time    : " << dt;
        cout << "Status         : " << (paymentStatus ? "Completed" : "Pending") << endl;
        if (!vehicleID.empty()) {
            cout << "Vehicle ID     : " << vehicleID << endl;
        }
        cout << "***************************************" << endl;
        cout << "     Thank you for your payment!" << endl;
        cout << "***************************************" << endl;
    }

    // Save payment record to file
    void saveToFile() {
        ofstream out("payment_records.txt", ios::app); // append mode
        out << transactionID << "," << paymentMethod << "," << amount << ","
            << (paymentStatus ? "1" : "0") << "," << vehicleID << "," << ctime(&paymentTime);
        out.close();
    }

    // Static method to read all payment records
    static void readFromFile() {
        ifstream in("payment_records.txt");
        string line;

        cout << "\n===== Payment History Records =====\n";
        cout << left << setw(15) << "Transaction ID"
             << setw(15) << "Method"
             << setw(10) << "Amount"
             << setw(10) << "Status"
             << setw(15) << "Vehicle ID"
             << "Date & Time" << endl;
        cout << "-------------------------------------------\n";

        while(getline(in, line)) {
            stringstream ss(line);
            string token;

            // Parse the comma-separated values
            vector<string> fields;
            while(getline(ss, token, ',')) {
                fields.push_back(token);
            }

            if (fields.size() >= 5) {
                cout << left << setw(15) << fields[0]  // Transaction ID
                     << setw(15) << fields[1]  // Payment Method
                     << setw(10) << fields[2]  // Amount
                     << setw(10) << (fields[3] == "1" ? "Cleared" : "Pending")  // Status
                     << setw(15);

                if (fields.size() >= 6) {
                    cout << fields[4];  // Vehicle ID
                    // Combine remaining fields for date/time (they might contain commas)
                    for (size_t i = 5; i < fields.size(); ++i) {
                        cout << "," << fields[i];
                    }
                } else {
                    cout << "N/A";  // If no vehicle ID
                    if (fields.size() >= 5) {
                        cout << fields[4];  // Date & Time
                    }
                }
                cout << endl;
            }
        }
        in.close();
    }

    // Setters and Getters
    void setAmount(float amt) {
        amount = amt;
    }

    float getAmount() const {
        return amount;
    }

    bool getPaymentStatus() const {
        return paymentStatus;
    }

    string getTransactionID() const {
        return transactionID;
    }

    string getVehicleID() const {
        return vehicleID;
    }

    void setVehicleID(string vID) {
        vehicleID = vID;
    }
};

class Travel // base class for all travel options
{
public:
    time_t now = time(0);
    char *dt = ctime(&now);

    string Name;
    int Age = 0;
    int IDno;
    int passengno;
    int dayno;
    int nightno;
    int cardno;
    int phonecount = 0;
    long long int Phoneno;

    virtual void Accept() = 0;
    virtual void Display() = 0;
    virtual void FareDetails() = 0; // Use of virtual functions

    long long int count_digit(long long int number) {
        if (number == 0) return 1;
        int count = 0;
        while(number != 0) {
            number = number / 10;
            count++;
        }
        return count;
    }

    void EnterDetails() {
    system("cls");

    cout << "\nEnter your Name : ";
    cin.ignore();
    getline(cin,Name);

    cout << "\nEnter your age : ";
    cin >> Age;

    try {
        if (Age < 18) {
            throw Age;
        }
    } catch (int x) {
        cout << "Sorry, you are not eligible!!";
        exit(0);
    }

    cout << "\nEnter your Driving License reference ID no. : ";
    cin >> IDno;

    // Modified phone number validation - keep asking until valid
    phonecount = 0;
    while(phonecount != 10) {
        cout << "\nEnter your phone number : ";
        cin >> Phoneno;

        if (count_digit(Phoneno) == 10) {
            phonecount = 10;
        } else {
            cout << "Invalid Number. Phone number must be 10 digits." << endl;
            // Instead of exit(0), we just continue the loop
        }
    }
}

    static void displayLogo() {
        cout << "                   *********    **********      *********   \n";
        cout << "                      **        **      **     **          \n";
        cout << "                      **        **      **     **           \n";
        cout << "                      **        **********     **           \n";
        cout << "                      **        *********       ********         \n";
        cout << "                      **        **     **              **        \n";
        cout << "                      **        **      **             **    \n";
        cout << "                 **  **         **       **            **   \n";
        cout << "                   **           **        **    ********       \n";
        cout << "\nWELCOME TO JAYPEE RENTAL SERVICES\n";
        cout << "\n                    MAKING EVERY JOURNEY BEAUTIFUL\n";
    }

    void Show() {
    cout << "";
    cout << " Loading";
    for(int i = 0; i < 6; i++) {
        cout << ".";
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    // Fixed non-portable screen clearing with cross-platform solution
    #ifdef _WIN32
        system("cls"); // For Windows
    #else
        system("clear"); // For Unix/Linux/MacOS
    #endif

    cout << "\n_\n\n";
    cout << "\n\t\t\t\t*---------------------------------*";
    cout << "\n\n\t\t\t\t J A Y P E E  T R A V E L L I N G  S E R V I C E S \n";
    cout << "\t\t\t\t\t\t\tSector 128 , Noida \n";
    cout << "\n\t\t\t\t*---------------------------------*" << endl;
    cout << "\t\t\t\t\t\tContact us at : 232476 , 554462\n\n\n\n ";
    cout << "\t Time of Booking: " << dt << endl;
    cout << "\t Name : " << Name << "\t\t\t Phone no. : " << Phoneno << "\n\n";
    cout << "\t Age : " << Age << "\t\t\t Driving License reference ID no. :" << IDno << "\n\n";
}

   void SaveBaseDetailsToFile(ofstream& out) {
    out << "Name: " << Name << ", "
        << "Age: " << Age << ", "
        << "ID: " << IDno << ", "
        << "Phone: " << Phoneno << ", ";
}
// Centralized file handling method to ensure uniqueness
bool IsRecordDuplicate(const string& recordKey) {
    ifstream in("travel_records.txt");
    string line;

    if (!in.is_open()) {
        return false; // File doesn't exist, so no duplicates
    }

    while (getline(in, line)) {
        if (line.find(recordKey) != string::npos) {
            in.close();
            return true; // Found a record with the same key
        }
    }

    in.close();
    return false;
}

static void ReadFromFile() {
    ifstream in("travel_records.txt");
    if (!in) {
        cout << "\n============== Travel Booking Records ==============\n";
        cout << "No booking records found. Make a booking to see it here.\n";
        cout << "===================================================\n";
        return;
    }

    string line;
    set<string> uniqueRecords; // Using a set to ensure uniqueness

    cout << "\n============== Travel Booking Records ==============\n";
    cout << left
         << setw(15) << "Booking Type"
         << setw(15) << "Name"
         << setw(6) << "Age"
         << setw(10) << "ID"
         << setw(15) << "Phone"
         << setw(10) << "Days/Pass"
         << setw(20) << "Vehicle"
         << "Total Fare\n";
    cout << "===================================================\n";

    while (getline(in, line)) {
        if (line.empty()) continue;

        // Skip duplicate records
        if (uniqueRecords.find(line) != uniqueRecords.end()) {
            continue;
        }
        uniqueRecords.insert(line);

        // Parse the record
        map<string, string> booking;
        stringstream ss(line);
        string token;

        while (getline(ss, token, ',')) {
            size_t pos = token.find(':');
            if (pos != string::npos) {
                string key = token.substr(0, pos);
                string value = token.substr(pos + 1);

                // Trim whitespace
                key.erase(0, key.find_first_not_of(" \t"));
                key.erase(key.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t"));
                value.erase(value.find_last_not_of(" \t") + 1);

                booking[key] = value;
            }
        }

        // Extract and display data in standard format
        string bookingType = booking.count("Booking Type") ? booking.at("Booking Type") : "N/A";
        string name = booking.count("Name") ? booking.at("Name") : "N/A";
        string age = booking.count("Age") ? booking.at("Age") : "N/A";
        string id = booking.count("ID") ? booking.at("ID") : "N/A";
        string phone = booking.count("Phone") ? booking.at("Phone") : "N/A";

        // Handle different day/passenger formats
        string daysPass = "N/A";
        if (booking.count("Days")) {
            daysPass = booking.at("Days");
        } else if (booking.count("Passengers")) {
            daysPass = booking.at("Passengers");
        }

        // Handle different vehicle formats
        string vehicle = "N/A";
        if (booking.count("Car") || booking.count("Cars")) {
            vehicle = booking.count("Car") ? booking.at("Car") : booking.at("Cars");
        } else if (booking.count("Bike")) {
            vehicle = booking.at("Bike");
        } else if (booking.count("Cycle")) {
            vehicle = booking.at("Cycle");
        }

        // Get total fare from different possible fields
        string totalFare = "Rs. 0.00";
        if (booking.count("Total")) {
            totalFare = "Rs. " + booking.at("Total");
        } else if (booking.count("Grand Total")) {
            totalFare = booking.at("Grand Total");
        }

        // Make sure total fare has Rs. prefix
        if (totalFare.find("Rs.") == string::npos) {
            totalFare = "Rs. " + totalFare;
        }

        // Display the booking
        cout << left
             << setw(15) << bookingType
             << setw(15) << name
             << setw(6) << age
             << setw(10) << id
             << setw(15) << phone
             << setw(10) << daysPass
             << setw(20) << vehicle
             << totalFare << endl;
    }

    if (uniqueRecords.empty()) {
        cout << left
             << setw(15) << "N/A"
             << setw(15) << "N/A"
             << setw(6) << "N/A"
             << setw(10) << "N/A"
             << setw(15) << "N/A"
             << setw(10) << "N/A"
             << setw(20) << "N/A"
             << "Rs. 0.00" << endl;
    }

    cout << "===================================================\n";
    in.close();
}
};

class cycle : public Travel {
public:
    string cycleChoice;
    float days, total;
    string cyclesAvailable[3] = { "Mountain Bike", "Road Bike", "Hybrid Bike" };
    float Perdayrate[3] = { 30, 40, 60 };
    int ch, i;

    void Accept() override {
        cout << "Looks like you have opted for a Cycle on rent\n";
        EnterDetails();
        cout << "Enter the no. of days you want to rent the cycle for: ";
        cin >> days;

        cout << "\nYou can choose a cycle from the following options: \n\n";
        cout << "Choice no.\tVehicle\t\tPer Day Rate\tAvailable\n";

        for (i = 0; i < 3; i++) {
            cout << i + 1 << "\t\t" << cyclesAvailable[i] << "\t\tRs." << Perdayrate[i]
                 << "\t\t" << inventory.getCycleAvailability(i) << "\n";
        }

        cout << "\n\nPlease Enter choice no.: ";
        cin >> ch;

        while (ch < 1 || ch > 3 || !inventory.isCycleAvailable(ch-1)) {
            if (ch < 1 || ch > 3) {
                cout << "Invalid choice. Please enter a number between 1 and 3: ";
            } else {
                cout << "Sorry, this cycle is not available. Please select another: ";
            }
            cin >> ch;
        }

        cycleChoice = cyclesAvailable[ch - 1];

        // Update inventory
        inventory.updateCycleAvailability(ch-1, -1);
    }

    void FareDetails() override {
        total = Perdayrate[ch - 1] * days;
        cout << "\nTotal rent for " << days << " days: Rs." << total << endl;
    }

    void Display() override {
        Show();
        cout << "\n\tYou have selected the cycle " << cycleChoice << " for " << days << " days.\n\n";
        cout << "\tCycle Rent: " << Perdayrate[ch - 1] << " * " << days << " = Rs." << total << "\n";
        cout << "\tTotal Amount payable: Rs." << total << "\n";
        cout << "\tThank you for choosing us, we hope you have a safe and fun ride!\n";
        cout << "\tVisit Again\n";
        cout << "_" << "\n";
    }

   void ProcessPayment() {
    string vehicleID = "CYCLE" + to_string(ch);
    Payment payment(total, vehicleID);
    string paymentMethod;
    cout << "\nChoose payment method (Cash/Card/NetBanking): ";
    cin >> paymentMethod;

    if (payment.processPayment(paymentMethod)) {
        payment.displayReceipt();
        SaveToFile(); // Add this line to save the booking data
    }

    }
void SaveToFile() {
    string recordKey = "Name: " + Name + ", ID: " + to_string(IDno) + ", Phone: " + to_string(Phoneno);

    if (IsRecordDuplicate(recordKey)) {
        cout << "This record already exists. Skipping save to prevent duplicates.\n";
        return;
    }

    ofstream out("travel_records.txt", ios::app); // Append mode
    out << "Booking Type: Cycle, ";
    SaveBaseDetailsToFile(out);
    out << "Cycle: " << cycleChoice << ", "
        << "Days: " << days << ", "
        << "Rate: " << Perdayrate[ch - 1] << ", "
        << "Total: " << total << ", "
        << "Booking Time: " << dt;
    out << endl;
    out.close();
}

};
class Bike : public Travel {
private:
    int bikechoice;
    float days, total;
    string BikeAvailable[5] = { "Activa", "Aviator", "Avenger", "Vespa", "Bullet" };
    string sidecar;
    float Perdayrate[5] = { 900, 1000, 1350, 1200, 1500 };
    string vehicleID;

public:
    void Accept() override {
        cout << "Looks like you have opted for a two-wheeler rental service.\n";
        EnterDetails(); // Base class input
        cout << "\nEnter number of days you want to rent the bike: ";
        cin >> days;

        cout << "\nAvailable bikes:\n";
        cout << "Choice\tModel\t\tRate/Day\tAvailable\n";
        for (int i = 0; i < 5; ++i) {
            cout << i + 1 << "\t" << setw(15) << left << BikeAvailable[i]
                 << "\tRs." << Perdayrate[i]
                 << "\t\t" << inventory.getBikeAvailability(i) << "\n";
        }

        cout << "\nEnter your choice (1-5): ";
        cin >> bikechoice;
        --bikechoice;

        while (bikechoice < 0 || bikechoice >= 5 || !inventory.isBikeAvailable(bikechoice)) {
            cout << "Invalid or unavailable choice. Try again: ";
            cin >> bikechoice;
            --bikechoice;
        }

        inventory.updateBikeAvailability(bikechoice, -1);
        inventory.saveToFile();  // <-- Save the updated inventory to the file
        vehicleID = "BIKE" + to_string(bikechoice + 1) + "_" + to_string(time(0));
    }

    void FareDetails() override {
        total = Perdayrate[bikechoice] * days;
        cout << "\nDo you want a sidecar for an additional Rs.200/day? (yes/no): ";
        cin >> sidecar;

        if (sidecar == "yes" || sidecar == "Yes") {
            total += 200 * days;
        }
    }

    void ProcessPayment() {
    float finalAmount = total + (0.05f * total);  // 5% tax
    Payment payment(finalAmount, vehicleID);

    string method;
    cout << "\nTotal after 5% tax: Rs. " << finalAmount;
    cout << "\nChoose payment method (Cash/Card/NetBanking): ";
    cin >> method;

    if (payment.processPayment(method)) {
        payment.displayReceipt();
        SaveToFile(); // Add this line to save the booking data
    } else {
        cout << "\nPayment failed. Booking will be cancelled.\n";
        inventory.updateBikeAvailability(bikechoice, 1); // Revert inventory
    }
}

    void Display() override {
        Show();
        cout << "\nBooking Summary:\n";
        cout << "\tBike: " << BikeAvailable[bikechoice] << "\n";
        cout << "\tDays: " << days << "\n";
        cout << "\tRate: Rs." << Perdayrate[bikechoice] << " per day\n";

        if (sidecar == "yes" || sidecar == "Yes") {
            cout << "\tSidecar: Yes (Rs. " << 200 * days << ")\n";
        } else {
            cout << "\tSidecar: No\n";
        }

        float tax = 0.05f * total;
        float finalAmount = total + tax;

        cout << "\tSubtotal: Rs." << total << "\n";
        cout << "\tTax (5%): Rs." << tax << "\n";
        cout << "\tTotal Payable: Rs." << finalAmount << "\n";
        cout << "\tVehicle ID: " << vehicleID << "\n";
        cout << "\nThank you! Enjoy your ride.\n";
    }

   void SaveToFile() {
    // Create a unique identifier for this record
    string recordKey = "Name: " + Name + ", ID: " + to_string(IDno) + ", Phone: " + to_string(Phoneno);

    // Check for duplicates before saving
    if (IsRecordDuplicate(recordKey)) {
        cout << "This record already exists. Skipping save to prevent duplicates.\n";
        return;
    }

    ofstream out("travel_records.txt", ios::app); // Append mode
    out << "Booking Type: Bike, ";
    SaveBaseDetailsToFile(out);
    out << "Bike: " << BikeAvailable[bikechoice] << ", "
        << "Days: " << days << ", ";

    if (sidecar == "yes" || sidecar == "Yes") {
        out << "Sidecar: Yes, ";
    } else {
        out << "Sidecar: No, ";
    }

    float tax = 0.05f * total;
    float finalAmount = total + tax;

    out << "Subtotal: " << total << ", "
        << "Tax: " << tax << ", "
        << "Total: " << finalAmount << ", "
        << "Booking Time: " << dt;
    out << endl;
    out.close();
}

    static void CancelBooking(const string& vID) {
        if (vID.rfind("BIKE", 0) == 0) {
            int index = vID[4] - '1'; // assuming single-digit bike index
            if (index >= 0 && index < 5) {
                inventory.updateBikeAvailability(index, 1);
                cout << "Booking canceled and inventory updated.\n";
            }
        }
    }
};

class Car : public Travel {
private:
    string status;
    int numberOfPassengers;
    int numberOfDays;
    int cityChoice;
    int ch; // Trip type choice (1: One Way, 2: Round Trip)
    int Taxihiredays;
    vector<string> carChoices;

    // Constants for car information
    const string CarCode[6] = {"1", "2", "3", "4", "5", "6"};
    const string CarAvailable[6] = {"Wagon-R", "SwiftDesire", "ToyotaEtios", "ToyotaInnova", "InnovaCrysta", "TempoTraveller"};
    const string OutsideCity[5] = {"Varanasi", "Lucknow", "Chandigarh", "Ajmer", "Merrut"};
    const float Distance[5] = {821.6, 512, 297.5, 414.8, 72.5};
    const float pricePerKm[6] = {9, 10, 11, 13, 15, 20};
    const float OneWayRates[6] = {12, 13, 15, 16, 18, 35};
    const float DriverCharges[6] = {250, 250, 250, 300, 300, 400};
    const float TaxiFare[6] = {1600, 1800, 2100, 2500, 2500, 3500};
    const float After80kms[6] = {80, 100, 0, 150, 200, 0};

    // Dynamic availability tracking
    int carAvailability[6];

    // Payment handling
    float totalCost;

public:
    // Constructor to initialize with default values
    Car() : numberOfPassengers(0), numberOfDays(0), cityChoice(0),
            ch(0), Taxihiredays(0), totalCost(0.0) {
        LoadAvailability();
    }

    // Destructor to ensure proper cleanup
    ~Car() {
        SaveAvailability();
    }

void LoadAvailability() {
    ifstream in("car_availability.txt");
    bool validData = true;

    if (in.is_open()) {
        try {
            for (int i = 0; i < 6; i++) {
                if (!(in >> carAvailability[i])) {
                    // Failed to read a valid number
                    validData = false;
                    break;
                }

                // Check for reasonable values (0 or positive)
                if (carAvailability[i] < 0) {
                    validData = false;
                    break;
                }
            }
        } catch (...) {
            validData = false;
        }

        in.close();

        // If we read bad data, reset to defaults
        if (!validData) {
            cout << "Warning: Corrupted car availability data detected. Resetting to defaults." << endl;
            for (int i = 0; i < 6; i++) {
                carAvailability[i] = 5;
            }
        }
    } else {
        // If file doesn't exist, initialize with default availability (5 of each)
        for (int i = 0; i < 6; i++) {
            carAvailability[i] = 5;
        }
        SaveAvailability();
    }
}

void SaveAvailability() {
    ofstream out("car_availability.txt");
    if (!out.is_open()) {
        cerr << "Error: Could not open car_availability.txt for writing.\n";
        cout << "Warning: Unable to save car availability. Changes may not persist.\n";
        return;
    }

    try {
        for (int i = 0; i < 6; i++) {
            out << carAvailability[i];
            if (i < 5) out << " ";
        }

        if (out.fail()) {
            cerr << "Error occurred while writing to car_availability.txt\n";
            cout << "Warning: Car availability data may not have been saved properly.\n";
        }
    } catch (const exception& e) {
        cerr << "Exception while saving car availability: " << e.what() << endl;
        cout << "Warning: Car availability may not have been saved correctly.\n";
    }

    out.close();
}
    // Get car model name by index
    string GetCarName(int index) const {
        if (index >= 0 && index < 6)
            return CarAvailable[index];
        return "Unknown Car";
    }

    // Get car code by index
    string GetCarCode(int index) const {
        if (index >= 0 && index < 6)
            return CarCode[index];
        return "";
    }

    // Display available car options
   void ShowCarMenu() {
    cout << "\n================ Available Car Options ================\n";
    cout << left << setw(10) << "Code"
         << setw(20) << "Model"
         << setw(15) << "Available" << "\n";
    cout << "--------------------------------------------------------\n";
    for (int i = 0; i < 6; ++i) {
        cout << left << setw(10) << CarCode[i]
             << setw(20) << CarAvailable[i]
             << setw(15) << inventory.getCarAvailability(i) << "\n"; // Use global inventory
    }
    cout << "========================================================\n";
}

    // Check if a car code is valid and available
    bool IsValidCarCode(const string& code) {
        for (int i = 0; i < 6; ++i) {
            if (CarCode[i] == code && carAvailability[i] > 0)
                return true;
        }
        return false;
    }

    // Get user's car choices
    void GetCarChoices(int numCars) {
        carChoices.clear(); // Clear any previous choices

        for (int i = 0; i < numCars; ++i) {
            string carCode;
            ShowCarMenu();
            cout << "Enter car choice code for car #" << i + 1 << ": ";
            cin >> carCode;

            // Validate input
            while (!IsValidCarCode(carCode)) {
                cout << "Invalid code or car not available. Enter again: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> carCode;
            }
            carChoices.push_back(carCode);

            // Decrease availability for selected car
           for (int j = 0; j < 6; j++) {
                    if (CarCode[j] == carCode) {
                        if (inventory.isCarAvailable(j)) {
                            inventory.updateCarAvailability(j, -1);  // Updates global inventory
                        }
                        break;
                    }
                }
        }
    }

    // Implement Accept method from Travel base class
    void Accept() override {
        cout << "\n========= Car Booking =========\n";

        // Get user details
        EnterDetails(); // This calls the base class method

        cout << "Enter Status (Inside/Outside): ";
        cin >> status;

        // Validate status input
        while (status != "inside" && status != "Inside" && status != "INSIDE" &&
               status != "outside" && status != "Outside" && status != "OUTSIDE") {
            cout << "Invalid status. Enter 'Inside' or 'Outside': ";
            cin >> status;
        }

        cout << "Enter number of passengers: ";
        while (!(cin >> numberOfPassengers) || numberOfPassengers <= 0) {
            cout << "Invalid input. Please enter a positive number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // Decide number of cars needed (Assuming max 5 passengers per car)
        int maxPerCar = 5;
        int numCars = (numberOfPassengers + maxPerCar - 1) / maxPerCar;
        cout << "\nYou will need " << numCars << " car(s) for " << numberOfPassengers << " passenger(s).\n";

        // Get car choices
        GetCarChoices(numCars);

        // If outside city, get additional details
        if (status == "outside" || status == "Outside" || status == "OUTSIDE") {
            cout << "\nOutside City Options:\n";
            for (int i = 0; i < 5; i++) {
                cout << i + 1 << ". " << OutsideCity[i] << " (" << Distance[i] << " km)\n";
            }

            cout << "Choose destination city (1-5): ";
            while (!(cin >> cityChoice) || cityChoice < 1 || cityChoice > 5) {
                cout << "Invalid choice. Enter a number between 1 and 5: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cityChoice--; // Adjust for array index

            cout << "Enter number of days: ";
            while (!(cin >> numberOfDays) || numberOfDays <= 0) {
                cout << "Invalid input. Please enter a positive number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cout << "Choose trip type (1-One Way, 2-Round Trip): ";
            while (!(cin >> ch) || (ch != 1 && ch != 2)) {
                cout << "Invalid choice. Enter 1 for One Way or 2 for Round Trip: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } else {
            cout << "Enter number of days for taxi hire: ";
            while (!(cin >> Taxihiredays) || Taxihiredays <= 0) {
                cout << "Invalid input. Please enter a positive number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        // Calculate total cost
        CalculateTotalCost();
    }

    // Calculate the total cost of the booking
    void CalculateTotalCost() {
        totalCost = 0.0f;

        for (const auto& selectedCar : carChoices) {
            for (int i = 0; i < 6; i++) {
                if (selectedCar == CarCode[i]) {
                    if (status == "inside" || status == "Inside" || status == "INSIDE") {
                        float tax = 0.05f * TaxiFare[i] * Taxihiredays;
                        float total = TaxiFare[i] * Taxihiredays + tax + DriverCharges[i] * Taxihiredays;
                        totalCost += total;
                    } else {
                        float dist = Distance[cityChoice];
                        float baseFare = (ch == 1) ? OneWayRates[i] * dist : pricePerKm[i] * dist * 2;
                        float tax = 0.05f * baseFare;
                        float driverCharge = DriverCharges[i] * numberOfDays;
                        float finalTotal = baseFare + tax + driverCharge;
                        totalCost += finalTotal;
                    }
                    break;
                }
            }
        }
    }

    // Implement Display method from Travel base class
    void Display() override {
        Show(); // Call base class method to show common information

        cout << "\n========= Booking Summary =========\n";
        cout << "Status: " << status << "\n";
        cout << "Number of Passengers: " << numberOfPassengers << "\n";

        cout << "\nCars Booked:\n";
        for (const auto& selectedCar : carChoices) {
            for (int i = 0; i < 6; i++) {
                if (selectedCar == CarCode[i]) {
                    cout << "- " << CarAvailable[i] << "\n";
                    if (status == "inside" || status == "Inside" || status == "INSIDE") {
                        float tax = 0.05f * TaxiFare[i] * Taxihiredays;
                        float total = TaxiFare[i] * Taxihiredays + tax + DriverCharges[i] * Taxihiredays;

                        cout << "  Type: Full Day\n";
                        cout << "  Days: " << Taxihiredays << "\n";
                        cout << "  Base Fare: " << TaxiFare[i] * Taxihiredays << "\n";
                        cout << "  Tax: " << tax << "\n";
                        cout << "  Driver Charges: " << DriverCharges[i] * Taxihiredays << "\n";
                        cout << "  Subtotal: " << total << "\n";
                    } else {
                        float dist = Distance[cityChoice];
                        float baseFare = (ch == 1) ? OneWayRates[i] * dist : pricePerKm[i] * dist * 2;
                        float tax = 0.05f * baseFare;
                        float driverCharge = DriverCharges[i] * numberOfDays;
                        float finalTotal = baseFare + tax + driverCharge;

                        cout << "  Type: " << (ch == 1 ? "One-way" : "Roundtrip") << "\n";
                        cout << "  Destination: " << OutsideCity[cityChoice] << "\n";
                        cout << "  Distance: " << dist << " km\n";
                        cout << "  Days: " << numberOfDays << "\n";
                        cout << "  Base Fare: " << baseFare << "\n";
                        cout << "  Tax: " << tax << "\n";
                        cout << "  Driver Charges: " << driverCharge << "\n";
                        cout << "  Subtotal: " << finalTotal << "\n";
                    }
                    break;
                }
            }
        }

        cout << "\nTotal Cost: Rs. " << fixed << setprecision(2) << totalCost << "\n";
        cout << "===================================\n";
    }

    // Implement FareDetails method from Travel base class
    void FareDetails() override {
        cout << "\n=================== Fare Details ===================\n";
        cout << left << setw(20) << "Car"
             << setw(15) << "Per Km Rate"
             << setw(15) << "One-Way Rate"
             << setw(15) << "Full Day Fare"
             << setw(15) << "Driver Fee/Day" << "\n";
        cout << "----------------------------------------------------\n";
        for (int i = 0; i < 6; i++) {
            cout << left << setw(20) << CarAvailable[i]
                 << setw(15) << pricePerKm[i]
                 << setw(15) << OneWayRates[i]
                 << setw(15) << TaxiFare[i]
                 << setw(15) << DriverCharges[i] << "\n";
        }
        cout << "====================================================\n";
    }

    // Process payment for the booking
void ProcessPayment() {
    if (totalCost <= 0) {
        CalculateTotalCost(); // Ensure cost is calculated
    }

    // Create unique vehicle ID for this booking
    string vehicleID = "CAR_" + to_string(time(0));

    // Create payment object
    Payment payment(totalCost, vehicleID);
    string paymentMethod;

    cout << "\nTotal Fare: Rs. " << fixed << setprecision(2) << totalCost;
    cout << "\nChoose payment method (Cash/Card/NetBanking): ";
    cin >> paymentMethod;

    // Fix error 9: Properly verify payment success
    if (payment.processPayment(paymentMethod)) {
        // Only display receipt if payment was successful
        payment.displayReceipt();
        cout << "\nPayment completed successfully!" << endl;
        // Save the booking details only if payment succeeds
        SaveToFile();
    } else {
        cout << "\nPayment failed. Please try again.\n";
        // Revert car availability if payment fails
        RestoreAvailability();
    }
}

    // Restore car availability (in case of payment failure)
    void RestoreAvailability() {
        for (const auto& selectedCar : carChoices) {
            for (int i = 0; i < 6; i++) {
                if (selectedCar == CarCode[i]) {
                    carAvailability[i]++;
                    break;
                }
            }
        }
        SaveAvailability();
    }


void SaveToFile() {
    // Create a unique identifier for this record to prevent duplicates
    string recordKey = "Name: " + Name + ", ID: " + to_string(IDno) + ", Phone: " + to_string(Phoneno);

    // Check for duplicates before saving
    if (IsRecordDuplicate(recordKey)) {
        cout << "This record already exists. Skipping save to prevent duplicates.\n";
        return;
    }

    ofstream out("travel_records.txt", ios::app);
    if (!out.is_open()) {
        cerr << "Error: Could not open travel_records.txt for writing.\n";
        cout << "Failed to save booking record. Please contact support.\n";
        return;
    }

    try {
        out << "Booking Type: Car, ";
        SaveBaseDetailsToFile(out);
        out << "Status: " << status << ", "
            << "Passengers: " << numberOfPassengers << ", ";

        // Concatenate all booked cars into a single field
        out << "Cars: ";
        for (size_t i = 0; i < carChoices.size(); i++) {
            for (int j = 0; j < 6; j++) {
                if (carChoices[i] == CarCode[j]) {
                    out << CarAvailable[j];
                    if (i < carChoices.size() - 1) {
                        out << ", ";
                    }
                    break;
                }
            }
        }
        out << ", ";

        if (status == "inside" || status == "Inside" || status == "INSIDE") {
            out << "Type: Inside City, "
                << "Days: " << Taxihiredays << ", ";
        } else {
            out << "Type: Outside City, "
                << "Destination: " << OutsideCity[cityChoice] << ", "
                << "Trip: " << (ch == 1 ? "One-way" : "Roundtrip") << ", "
                << "Distance: " << Distance[cityChoice] << " km, "
                << "Days: " << numberOfDays << ", ";
        }

        out << "Grand Total: Rs. " << fixed << setprecision(2) << totalCost << ", "
            << "Booking Time: " << dt;
        out << endl;

        if (!out.good()) {
            throw runtime_error("Failed writing to file");
        }

        out.close();
        cout << "Booking record saved successfully.\n";
    }
    catch (const exception& e) {
        cerr << "Error while writing to file: " << e.what() << endl;
        cout << "Failed to save complete booking record.\n";
        if (out.is_open()) {
            out.close();
        }
    }

    // Save car availability separately
    SaveAvailability();
}

    // Get the list of car choices
    const vector<string>& GetCarChoices() const {
        return carChoices;
    }

    // Get total cost
    float GetTotalCost() const {
        return totalCost;
    }
};

int main() {
    int choice;
    char continueBooking;

    // Clear screen and show welcome
    cout << "\033[2J\033[1;1H";
    Travel::displayLogo();\

    if (isEmployee()) {
        if (!loginUser()) {
            cout << "\nAccess denied. Program will exit.\n";
            return 0;
        }
        inventory.displayAll();
        char viewChoice;
        cout << "\nWould you like to view previous rental records? (Y/N): ";
        cin >> viewChoice;
        if (viewChoice == 'Y' || viewChoice == 'y') {
            Travel::ReadFromFile();
            cout << "\n-----------------------------------\n";
        }
        cout << "\nPress any key to logout...";
        exit(0);
        return 0;
    } else {
        cout << "\nWelcome, valued customer!\n";
        cout << "\nThank you for choosing us!\n"
             << "We offer bikes, cycles, and cars for city and outstation travel.\n"
             << "_\nHELP:-\n CONTACT US AT:\n"
             << "Phone: 9854244573, 7634256822\n"
             << "Email: jtservices@gmail.com\n";
    }

    do {
        cout << "\nChoose your vehicle:\n";
        cout << "1. Bike\n2. Car\n3. Cycle\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\n--- BIKES AVAILABILITY ---\n";
                cout << left << setw(5) << "ID" << setw(20) << "Model" << setw(15) << "Available" << endl;
                for (int i = 0; i < 5; i++) {
                    cout << left << setw(5) << i+1 << setw(20) << inventory.getBikeName(i)
                         << setw(15) << inventory.getBikeAvailability(i) << endl;
                }
                Bike obj;
                obj.Accept();
                obj.FareDetails();
                obj.Display();
                obj.ProcessPayment();
                break;
            }

            case 2: {
                cout << "\n--- CARS AVAILABILITY ---\n";
                cout << left << setw(5) << "ID" << setw(20) << "Model" << setw(15) << "Available" << endl;
                for (int i = 0; i < 6; i++) {
                    cout << left << setw(5) << i+1 << setw(20) << inventory.getCarName(i)
                         << setw(15) << inventory.getCarAvailability(i) << endl;
                }
                Car ob;
                ob.FareDetails();
                ob.Accept();
                ob.Display();
                ob.ProcessPayment();
                break;
            }

            case 3: {
                cout << "\n--- CYCLES AVAILABILITY ---\n";
                cout << left << setw(5) << "ID" << setw(20) << "Model" << setw(15) << "Available" << endl;
                for (int i = 0; i < 3; i++) {
                    cout << left << setw(5) << i+1 << setw(20) << inventory.getCycleName(i)
                         << setw(15) << inventory.getCycleAvailability(i) << endl;
                }
                cycle obj;
                obj.Accept();
                obj.FareDetails();
                obj.Display();
                obj.ProcessPayment();
                break;
            }

            default:
                cout << "\nInvalid input. Please enter 1, 2, or 3.\n";
                break;
        }

        cout << "\nWould you like to make another booking? (Y/N): ";
        cin >> continueBooking;

    } while (continueBooking == 'Y' || continueBooking == 'y');

    cout << "\nThank you for using Jaypee Rental Services! Have a great day!\n";
    return 0;
}
