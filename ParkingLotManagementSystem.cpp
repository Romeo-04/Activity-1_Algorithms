#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
using namespace std;

// Structure for a parking spot

struct ParkingSpot {
    string licensePlate;
    bool isOccupied = false;
};

// Node structure for linked list (used for queue and stack)
struct Node {
    string data;
    Node* next;
};

// Linked List Class
class LinkedList {
protected:
    Node* head;

public:
    LinkedList() : head(NULL) {}

    void insertAtEnd(string value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = NULL;

        if (!head) {
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void deleteFromBeginning() {
        if (!head) return;

        Node* temp = head;
        head = head->next;
        delete temp;
    }

    string getFirst() {
        if (head) {
            return head->data;
        }
        return "";
    }

    bool contains(string value) {
        Node* temp = head;
        while (temp) {
            if (temp->data == value) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void display() {
        if (!head) {
            cout << "Empty." << endl;
            return;
        }

        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// Queue Class (extends LinkedList for waiting vehicles)
class Queue : public LinkedList {
public:
    void enqueue(string value) {
        insertAtEnd(value);
    }

    void dequeue() {
        deleteFromBeginning();
    }

    bool isEmpty() {
        return head == NULL;
    }
};

// Stack Class (extends LinkedList for recently vacated spots)

class Stack : public LinkedList {
public:
    void push(string value) {
        insertAtEnd(value);
    }

    string pop() {
        if (!head) return "";
        string value = head->data;
        deleteFromBeginning();
        return value;
    }

    bool isEmpty() {
        return head == NULL;
    }
};

// Updated Parking Lot Management System
class ParkingLotManagementSystem {
private:
    static const int ROWS = 1; // Number of rows
    static const int COLUMNS = 3; // Number of columns
    ParkingSpot parkingLot[ROWS][COLUMNS]; // 2D Array for parking spots
    Queue waitingQueue; // Queue for waiting vehicles
    LinkedList parkedVehicles; // Linked list to manage parked vehicles
    Stack recentlyVacated; // Stack for recently vacated spots

    void logActivity(const string& message) {
        ofstream logFile("parking_log.txt", ios::app);
        if (logFile.is_open()) {
            logFile << message << endl;
            logFile.close();
        }
    }

    bool isDuplicateLicensePlate(const string& licensePlate) {
        return parkedVehicles.contains(licensePlate);
    }

public:
    ParkingLotManagementSystem() {
        // Initialize parking lot
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLUMNS; ++j) {
                parkingLot[i][j].isOccupied = false;
                parkingLot[i][j].licensePlate = "";
            }
        }
    }

    void parkVehicle(const string& licensePlate) {
        //First checkpoint: Check for invalid license plate
        if (licensePlate.empty()) {
            cout << "Error: Invalid license plate." << endl;
            return;
        }
        //Second checkpoint: Check for duplicate license plate
        if (isDuplicateLicensePlate(licensePlate)) {
            cout << "Error: Vehicle with license plate " << licensePlate
                 << " is already parked." << endl;
            return;
        }

        //Third checkpoint: Check if there are recently vacated spots
        if (!recentlyVacated.isEmpty()) {
            string vacatedSpot = recentlyVacated.pop();
            int row = vacatedSpot[0] - '0';
            int col = vacatedSpot[1] - '0';

            parkingLot[row][col].isOccupied = true;
            parkingLot[row][col].licensePlate = licensePlate;
            parkedVehicles.insertAtEnd(licensePlate);

            cout << "Vehicle with license plate " << licensePlate
                 << " parked at recently vacated spot (" << row + 1 << "," << col + 1 << ")." << endl;

            logActivity("Parked vehicle: " + licensePlate + " at recently vacated spot (" +
                        to_string(row + 1) + "," + to_string(col + 1) + ")");
            return;
        }

        // Fourth checkpoint: Find the first available spot
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLUMNS; ++j) {
                if (!parkingLot[i][j].isOccupied) {
                    parkingLot[i][j].isOccupied = true;
                    parkingLot[i][j].licensePlate = licensePlate;
                    parkedVehicles.insertAtEnd(licensePlate);

                    cout << "Vehicle with license plate " << licensePlate
                         << " parked at spot (" << i + 1 << "," << j + 1 << ")." << endl;

                    logActivity("Parked vehicle: " + licensePlate + " at spot (" +
                                to_string(i + 1) + "," + to_string(j + 1) + ")");
                    return;
                }
            }
        }

         // If parking lot is full, add to waiting queue
        waitingQueue.enqueue(licensePlate);
        cout << "Parking lot is full. Vehicle added to waiting queue: " << licensePlate << endl;
        logActivity("Added vehicle to waiting queue: " + licensePlate);
    }

    void retrieveVehicle(const string& licensePlate) {
        if (licensePlate.empty()) {
            cout << "Error: Invalid license plate." << endl;
            return;
        }

        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLUMNS; ++j) {
                if (parkingLot[i][j].isOccupied && parkingLot[i][j].licensePlate == licensePlate) {
                    parkingLot[i][j].isOccupied = false;
                    parkingLot[i][j].licensePlate = "";
                    cout << "Vehicle with license plate " << licensePlate
                         << " retrieved from spot (" << i + 1 << "," << j + 1 << ")." << endl;

                    logActivity("Retrieved vehicle: " + licensePlate + " from spot (" +
                                to_string(i + 1) + "," + to_string(j + 1) + ")");

                    // Push recently vacated spot into the stack
                    recentlyVacated.push(to_string(i) + to_string(j));

                    // Remove vehicle from parked vehicles list
                    parkedVehicles.deleteFromBeginning();

                    // Check if there's a vehicle in the waiting queue to park
                    if (!waitingQueue.isEmpty()) {
                        string nextVehicle = waitingQueue.getFirst();
                        waitingQueue.dequeue();
                        parkVehicle(nextVehicle);
                    }
                    return;
                }
            }
        }

        cout << "Error: Vehicle with license plate " << licensePlate << " not found in the parking lot." << endl;
        logActivity("Failed to retrieve vehicle: " + licensePlate);
    }

    void displayAvailableSpots() {
        cout << "\nParking Lot Status:\n";
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLUMNS; ++j) {
                if (parkingLot[i][j].isOccupied) {
                    cout << "[" << parkingLot[i][j].licensePlate << "] ";
                } else {
                    cout << "[Available] ";
                }
            }
            cout << endl;
        }

        cout << "Waiting Queue: ";
        waitingQueue.display();
    }
};

int main() {
    ParkingLotManagementSystem system;

    int choice;
    string licensePlate;

    do {
        cout << " = = = = = = = = = = = = = = = = = = = = " << endl;
        cout << "   Parking Lot Management System Menu " << endl;
        cout << " = = = = = = = = = = = = = = = = = = = = " << endl;
        cout << "1. Park a Vehicle\n";
        cout << "2. Retrieve a Vehicle\n";
        cout << "3. Display Parking Lot Status\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter license plate: ";
            cin >> licensePlate;
            system.parkVehicle(licensePlate);
            break;
        case 2:
            cout << "Enter license plate to retrieve: ";
            cin >> licensePlate;
            system.retrieveVehicle(licensePlate);
            break;
        case 3:
            system.displayAvailableSpots();
            break;
        case 4:
            cout << "Exiting the system. Goodbye!" << endl;
            break;
        default:
            cout << "Please put a valid number." << endl << endl;
            cin.clear();
            //galing pa to sa divisibility checker ko HAAHHAHA
            //removes the failed input from the buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (choice != 4);

    return 0;
}

