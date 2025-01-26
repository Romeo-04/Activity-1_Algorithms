Parking Lot Management System 🚗
A C++ program designed to manage parking spots, handle waiting queues, and log activities for a parking lot. This system uses linked lists, stacks, and queues to efficiently manage parking operations.

Features ✨
Parking Management:

Park vehicles in available spots.

Prioritize recently vacated spots using a stack (LIFO).

Handle overflow with a waiting queue (FIFO).

Retrieval System:

Retrieve vehicles by license plate.

Automatically park the next vehicle from the waiting queue.

Real-Time Status:

Display current parking lot occupancy.

Show waiting queue status.

Activity Logging:

Log all parking and retrieval activities to parking_log.txt.

Input Validation:

Prevent duplicate parking.

Reject invalid license plates.

How It Works 🛠️
Data Structures Used
2D Array: Represents the parking lot grid.

Stack: Tracks recently vacated spots (LIFO).

Queue: Manages waiting vehicles (FIFO).

Linked List: Tracks all parked vehicles.

Algorithms
Parking:

Check for invalid or duplicate license plates.

Prioritize recently vacated spots.

Find the first available spot.

Add to waiting queue if the lot is full.

Retrieval:

Search for the vehicle by license plate.

Free the spot and update the stack.

Park the next vehicle from the waiting queue.

Logging:

Record all operations in parking_log.txt.

Code Structure 📂
Key Files
main.cpp: Contains the main program logic.

parking_log.txt: Logs all parking and retrieval activities.

Classes
ParkingSpot:

Represents a single parking spot.

Tracks license plate and occupancy status.

LinkedList:

Base class for stack and queue operations.

Implements insertion, deletion, and traversal.

Stack:

Manages recently vacated spots (LIFO).

Queue:

Manages waiting vehicles (FIFO).

ParkingLotManagementSystem:

Core class for parking and retrieval operations.

Handles logging and status display.

Getting Started 🚀
Prerequisites
C++ compiler (e.g., g++).

Basic understanding of data structures.

Compilation
Clone the repository:

bash
Copy
git clone https://github.com/your-username/parking-lot-system.git
Navigate to the project directory:

bash
Copy
cd parking-lot-system
Compile the program:

bash
Copy
g++ main.cpp -o parking_system
Run the executable:

bash
Copy
./parking_system
Usage 🖥️
Menu Options
Park a Vehicle:

Enter the license plate to park the vehicle.

The system will assign a spot or add to the waiting queue.

Retrieve a Vehicle:

Enter the license plate to retrieve the vehicle.

The system will free the spot and park the next waiting vehicle.

Display Parking Lot Status:

Shows current occupancy and waiting queue.

Exit:

Saves logs and exits the program.

Example Workflow 📝
Scenario 1: Parking Vehicles
Park "ABC123" → Assigned to spot (1,1).

Park "XYZ789" → Assigned to spot (1,2).

Park "DEF456" → Assigned to spot (1,3).

Park "GHI012" → Added to waiting queue (lot is full).

Scenario 2: Retrieving Vehicles
Retrieve "XYZ789" → Spot (1,2) freed.

"GHI012" from the queue parks in spot (1,2).

Logs 📄
All activities are logged in parking_log.txt:

Copy
Parked vehicle: ABC123 at spot (1,1)
Parked vehicle: XYZ789 at spot (1,2)
Parked vehicle: DEF456 at spot (1,3)
Added vehicle to waiting queue: GHI012
Retrieved vehicle: XYZ789 from spot (1,2)
Parked vehicle: GHI012 at recently vacated spot (1,2)
Limitations and Future Improvements 🚧
Limitations
Scalability: The 2D array limits the parking lot size.

Input Handling: License plates with spaces are not supported.

Thread Safety: Not suitable for concurrent access.

Future Improvements
Dynamic Parking Lot Size:

Use dynamic data structures (e.g., vectors) for scalability.

Enhanced Input Validation:

Support spaces in license plates using getline().

Database Integration:

Store logs and parking data in a database for persistence.

Graphical Interface:

Add a GUI for better user interaction.

Contributing 🤝
Contributions are welcome! Please follow these steps:

Fork the repository.

Create a new branch for your feature/bugfix.

Submit a pull request with a detailed description.

License 📜
This project is licensed under the MIT License. See LICENSE for details.

Acknowledgments 🙏
Inspired by real-world parking management systems.

Built with ❤️ using C++.

Enjoy managing your parking lot efficiently! 🚀
