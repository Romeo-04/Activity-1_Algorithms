#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string iterateFilename(int filecounter);

struct Node {
    string igName;
    int pScore;
    Node* next;
};

// CHECK IF PLAYER EXISTS IN THE LIST
bool playerExists(Node* head, string igName) {
    Node* current = head;
    while (current != NULL) {
        if (current->igName == igName) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// INSERT PLAYER INTO PRIORITY QUEUE (SORTED INSERTION)
void insertPlayer(Node*& head, string igName, int pScore) {
    Node* newNode = new Node();
    newNode->igName = igName;
    newNode->pScore = pScore;
    newNode->next = NULL;

    // If the list is empty or the new node has the highest priority
    if (head == NULL || pScore > head->pScore || (pScore == head->pScore && igName < head->igName)) {
        newNode->next = head;
        head = newNode;
        return;
    }

    // Traverse the list to find the correct position
    Node* current = head;
    while (current->next != NULL &&
           (current->next->pScore > pScore || (current->next->pScore == pScore && current->next->igName < igName))) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

// UPDATE PLAYER SCORE IN PRIORITY QUEUE
void updatePlayerScore(Node*& head, string igName, int newScore) {
    Node* current = head;
    Node* prev = NULL;

    // Search for the player in the list
    while (current != NULL && current->igName != igName) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        cout << "Player not found in the leaderboard." << endl;
        return;
    }

    // Remove the current node
    if (prev == NULL) {
        head = current->next;
    } else {
        prev->next = current->next;
    }

    delete current;

    // Reinsert the player with the updated score
    insertPlayer(head, igName, newScore);
    cout << "Player's score updated successfully." << endl;
}

// CLEAR THE LINKED LIST
void clearList(Node*& head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// DISPLAY TOP 10 PLAYERS USING ARRAY
void displayTopTenPlayers(Node* head) {
    int rank = 0;
    Node* current = head;
    Node* topTen[10] = {nullptr}; // Array to store top 10 players

    while (current != NULL && rank < 10) {
        topTen[rank++] = current;
        current = current->next;
    }

    cout << "\nTop 10 Players:\n";
    cout << "Rank\tName\tScore\n";
    for (int i = 0; i < rank; i++) {
        cout << (i + 1) << "\t" << topTen[i]->igName << "\t" << topTen[i]->pScore << endl;
    }
}

// LOAD PLAYERS FROM FILE INTO PRIORITY QUEUE
void loadFromFile(Node*& head, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "No existing leaderboard file found. Starting fresh." << endl;
        return;
    }

    string igName;
    int pScore;
    while (inFile >> igName >> pScore) {
        insertPlayer(head, igName, pScore);
    }
    inFile.close();

    cout << "Leaderboard loaded from file." << endl;
}

// SAVE PLAYERS FROM PRIORITY QUEUE INTO FILE
void saveToFile(Node* head, const string& filename) {
    ofstream outFile(filename);
    Node* current = head;
    while (current != NULL) {
        outFile << current->igName << " " << current->pScore << endl;
        current = current->next;
    }
    outFile.close();
    cout << "Leaderboard saved to file." << endl;
}

string iterateFilename(int filecounter) {
    return "leaderboard_" + to_string(filecounter) + ".txt";
}

int main() {
    Node* head = NULL;
    int filecounter = 1;
    string leaderboardFile = "leaderboard.txt";

    // Load leaderboard from file
    loadFromFile(head, leaderboardFile);

    char choice;
    do {
        cout << "\n== LEADERBOARD SYSTEM ==\n";
        cout << "[1] Add Player\n";
        cout << "[2] Display Top 10 Players\n";
        cout << "[3] Update Player Score\n";
        cout << "[4] Clear Leaderboard\n";
        cout << "[5] Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case '1': {
                string igName;
                int pScore;

                cout << "Enter Name: ";
                getline(cin, igName);

                if (playerExists(head, igName)) {
                    cout << "Player is already in the leaderboard. Please choose to update the score instead." << endl;
                    break;
                }

                do {
                    cout << "Enter Score for " << igName << ": ";
                    cin >> pScore;

                    if (pScore < 0) {
                        cout << "Invalid Score!" << endl;
                    } else {
                        insertPlayer(head, igName, pScore);
                    }

                } while (pScore < 0);
                break;
            }

            case '2': {
                displayTopTenPlayers(head);
                break;
            }

            case '3': {
                string igName;
                int newScore;

                cout << "Enter Name of the Player to Update: ";
                getline(cin, igName);

                do {
                    cout << "Enter New Score for " << igName << ": ";
                    cin >> newScore;

                    if (newScore < 0) {
                        cout << "Invalid Score!" << endl;
                    } else {
                        updatePlayerScore(head, igName, newScore);
                    }

                } while (newScore < 0);
                break;
            }

            case '4': {
                clearList(head);
                cout << "Leaderboard cleared." << endl;
                break;
            }

            case '5': {
                saveToFile(head, leaderboardFile);
                cout << "Exiting program." << endl;
                break;
            }

            default:
                cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != '5');

    clearList(head);
    return 0;
}
