#include <iostream>
#include <string>
using namespace std;

// Class representing a flight connection (destination, time, fuel)
class FlightNode {
public:
    string destCity;   // Destination city name
    int time;          // Flight time (in hours)
    int fuel;          // Fuel required (in litres)
    FlightNode* down;  // Pointer to next flight in the same city's flight list

    // Constructor
    FlightNode(string dest, int t, int f) {
        destCity = dest;
        time = t;
        fuel = f;
        down = NULL;
    }
};

// Class representing a city and its flight connections
class CityNode {
public:
    string cityName;        // City name
    CityNode* next;         // Pointer to next city in the city list
    FlightNode* flightHead; // Pointer to first flight connection from this city

    // Constructor
    CityNode(string name) {
        cityName = name;
        next = NULL;
        flightHead = NULL;
    }
};

// Class representing the entire flight network
class Flight {
private:
    CityNode* head; // Head pointer for the city list

    // Helper functions
    CityNode* findCity(const string& name);  // Find a city by name
    void StoDUtil(CityNode* current, const string& destination, string path, int time, int fuel, string visited[], int& vcount, bool& found);
  bool isVisited(string visited[], int count, const string& city);  // Check if a city is already visited
    void allUtil(CityNode* current, string visited[], int& vcount);   // Recursive function to find all reachable cities

public:
    // Constructor initializes head as NULL
    Flight() {
        head = NULL;
    }

    // Function declarations
    void read_cities();
    void display_cities();
    void read_flights();
    void display_flights();
    void StoD();
    void all();
};

// Function to read city names from user
void Flight::read_cities() {
    char answer;
    string city;
    CityNode* last = NULL;

    do {
        cout << "Enter City Name: ";
        cin >> city;
        CityNode* newNode = new CityNode(city); // Create new city node

        if (!head) {
            head = newNode; // If first city, make it head
        } else {
            last->next = newNode; // Link the new city at the end
        }
        last = newNode;

        cout << "Add another city? (Y/N): ";
        cin >> answer;

    } while (answer == 'Y' || answer == 'y');
}

// Function to display all cities
void Flight::display_cities() {
    CityNode* temp = head;
    cout << "\nCities:\n";
    while (temp) {
        cout << "- " << temp->cityName << endl;
        temp = temp->next;
    }
}

// Function to find a city by name
CityNode* Flight::findCity(const string& name) {
    CityNode* temp = head;
    while (temp) {
        if (temp->cityName == name)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

// Function to read flight connections (edges)
void Flight::read_flights() {
    char ans;
    string src, dest;
    int time, fuel;

    do {
        cout << "\nEnter Source City: ";
        cin >> src;
        cout << "Enter Destination City: ";
        cin >> dest;
        cout << "Enter Time (in hours): ";
        cin >> time;
        cout << "Enter Fuel (in litres): ";
        cin >> fuel;

        // Find source city
        CityNode* srcNode = findCity(src);
        if (!srcNode) {
            cout << "Source city not found!\n";
        } else {
            // Create new flight node and link it at the beginning
            FlightNode* newFlight = new FlightNode(dest, time, fuel);
            newFlight->down = srcNode->flightHead;
            srcNode->flightHead = newFlight;
        }

        cout << "Add another flight? (Y/N): ";
        cin >> ans;

    } while (ans == 'Y' || ans == 'y');
}

// Function to display all flight connections
void Flight::display_flights() {
    CityNode* city = head;

    cout << "\nFlight Connections:\n";
    while (city) {
        cout << city->cityName << " -> ";
        FlightNode* flight = city->flightHead;

        // Display all flights from this city
        while (flight) {
            cout << "[" << flight->destCity << ", " << flight->time << "h, " << flight->fuel << "L] -> ";
            flight = flight->down;
        }

        cout << "NULL\n";
        city = city->next;
    }
}

// Function to check if a city was already visited
bool Flight::isVisited(string visited[], int count, const string& city) {
    for (int i = 0; i < count; i++) {
        if (visited[i] == city)
            return true;
    }
    return false;
}

// Recursive DFS utility for finding source-to-destination paths
void Flight::StoDUtil(CityNode* current, const string& destination, string path, int time, int fuel, string visited[], int& vcount, bool& found) {
    // If city is NULL or already visited, return
    if (!current || isVisited(visited, vcount, current->cityName))
        return;

    visited[vcount++] = current->cityName; // Mark current city as visited

    FlightNode* flight = current->flightHead;
    while (flight) {
        // Create new path, time, and fuel
        string newPath = path + " -> " + flight->destCity;
        int newTime = time + flight->time;
        int newFuel = fuel + flight->fuel;

        // If destination found, display path
        if (flight->destCity == destination) {
            cout << "Path: " << newPath << " | Time: " << newTime << "h | Fuel: " << newFuel << "L\n";
            found = true;
        } else {
            // Continue DFS for next city
            CityNode* nextCity = findCity(flight->destCity);
            StoDUtil(nextCity, destination, newPath, newTime, newFuel, visited, vcount, found);
        }

        flight = flight->down;
    }

    vcount--; // Backtrack (unmark current city)
}

// Function to find and display all paths between two cities
void Flight::StoD() {
    string source, dest;
    cout << "Enter Source City: ";
    cin >> source;
    cout << "Enter Destination City: ";
    cin >> dest;

    CityNode* srcNode = findCity(source);
    if (!srcNode) {
        cout << "Source city not found.\n";
        return;
    }

    bool found = false;
    string visited[100];
    int vcount = 0;

    cout << "\nPaths from " << source << " to " << dest << ":\n";
    StoDUtil(srcNode, dest, source, 0, 0, visited, vcount, found);

    if (!found)
        cout << "No path found from " << source << " to " << dest << ".\n";
}

// Recursive DFS utility to find all reachable cities from a given source
void Flight::allUtil(CityNode* current, string visited[], int& vcount) {
    // Base case: city is null or already visited
    if (!current || isVisited(visited, vcount, current->cityName))
        return;

    visited[vcount++] = current->cityName; // Mark city visited

    FlightNode* flight = current->flightHead;
    while (flight) {
        if (!isVisited(visited, vcount, flight->destCity)) {
            cout << "- " << flight->destCity << endl; // Print reachable city
            CityNode* next = findCity(flight->destCity);
            allUtil(next, visited, vcount); // Continue DFS
        }
        flight = flight->down;
    }
}

// Function to show all reachable cities from a given source
void Flight::all() {
    string source;
    cout << "Enter Source City: ";
    cin >> source;

    CityNode* srcNode = findCity(source);
    if (!srcNode) {
        cout << "City not found.\n";
        return;
    }

    string visited[100];
    int vcount = 0;

    cout << "\nCities reachable from " << source << ":\n";
    allUtil(srcNode, visited, vcount);

    if (vcount <= 1) {
        cout << "No connected cities found.\n";
    }
}

// Main function with menu-driven interface
int main() {
    Flight F1;
    int x;

    do {
        cout << "\n*** Select An Option ***";
        cout << "\n1. Enter Cities";
        cout << "\n2. Display Cities";
        cout << "\n3. Add Flight Connections";
        cout << "\n4. Display Flight Connections";
        cout << "\n5. Source To Destination Paths";
        cout << "\n6. All Reachable Cities From Source";
        cout << "\n7. Exit";
        cout << "\nEnter Choice: ";
        cin >> x;

        switch (x) {
            case 1: F1.read_cities(); break;
            case 2: F1.display_cities(); break;
            case 3: F1.read_flights(); break;
            case 4: F1.display_flights(); break;
            case 5: F1.StoD(); break;
            case 6: F1.all(); break;
            case 7: cout << "Exiting...\n"; break;
            default: cout << "Invalid Choice!\n";
        }
    } while (x != 7);

    return 0;
}



/*

/*
*** Select An Option ***
1. Enter Cities
2. Display Cities
3. Add Flight Connections
4. Display Flight Connections
5. Source To Destination Paths
6. All Reachable Cities From Source
7. Exit
Enter Choice: 1
Enter City Name: pune
Add another city? (Y/N): y
Enter City Name: mumbai
Add another city? (Y/N): y
Enter City Name: delhi
Add another city? (Y/N): n

*** Select An Option ***
1. Enter Cities
2. Display Cities
3. Add Flight Connections
4. Display Flight Connections
5. Source To Destination Paths
6. All Reachable Cities From Source
7. Exit
Enter Choice: 2

Cities:
- pune
- mumbai
- delhi

*** Select An Option ***
1. Enter Cities
2. Display Cities
3. Add Flight Connections
4. Display Flight Connections
5. Source To Destination Paths
6. All Reachable Cities From Source
7. Exit
Enter Choice: 3

Enter Source City: pune
Enter Destination City: mumbai
Enter Time (in hours): 2
Enter Fuel (in litres): 150
Add another flight? (Y/N): y

Enter Source City: mumbai
Enter Destination City: delhi
Enter Time (in hours): 4
Enter Fuel (in litres): 250
Add another flight? (Y/N): 2

*** Select An Option ***
1. Enter Cities
2. Display Cities
3. Add Flight Connections
4. Display Flight Connections
5. Source To Destination Paths
6. All Reachable Cities From Source
7. Exit
Enter Choice: 4

Flight Connections:
pune -> [mumbai, 2h, 150L] -> NULL
mumbai -> [delhi, 4h, 250L] -> NULL
delhi -> NULL

*** Select An Option ***
1. Enter Cities
2. Display Cities
3. Add Flight Connections
4. Display Flight Connections
5. Source To Destination Paths
6. All Reachable Cities From Source
7. Exit
Enter Choice: 5
Enter Source City: pune
Enter Destination City: mumbai

Paths from pune to mumbai:
Path: pune -> mumbai | Time: 2h | Fuel: 150L

*** Select An Option ***
1. Enter Cities
2. Display Cities
3. Add Flight Connections
4. Display Flight Connections
5. Source To Destination Paths
6. All Reachable Cities From Source
7. Exit
Enter Choice: 6
Enter Source City: pune

Cities reachable from pune:
- mumbai
- delhi


⚙️ Time Complexity Summary
Operation	Time Complexity	Description
Add city	O(1)	Append to city list
Add flight	O(1)	Add to city’s adjacency list
Display flights	O(V + E)	Traverse graph
Path from source to destination (DFS)	O(V + E)	Depth-first traversal
All reachable cities	O(V + E)	DFS traversal

*** Select An Option ***
1. Enter Cities
2. Display Cities
3. Add Flight Connections
4. Display Flight Connections
5. Source To Destination Paths
6. All Reachable Cities From Source
7. Exit
Enter Choice: */

