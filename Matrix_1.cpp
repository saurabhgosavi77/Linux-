#include <iostream>
#include <string>
using namespace std;

// Class representing the flight network using adjacency matrices
class Flight {
private:
    int matrix_size;            // Number of cities
    string cities[100];         // Array to store city names
    int mat[100][100];          // Adjacency matrix for flight time (in hours)
    int fuel[100][100];         // Adjacency matrix for fuel consumption (in litres)

public:
    // Constructor to initialize matrices with zero
    Flight();
    
    // Functions for different operations
    void read_cities();     // Input city names
    void display_cities();  // Display city names with codes
    void read_flight();     // Input flight connections
    void display_flight();  // Display flight matrices (time & fuel)
    void StoD();            // Show Source to Destination flights (direct & indirect)
    void all();             // Show all connected cities from a source city
};

// Constructor - initializes all matrix values to zero
Flight::Flight() {
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            mat[i][j] = 0;   // No flight initially
            fuel[i][j] = 0;  // No fuel data initially
        }
    }
}

// Function to read city names and assign unique codes
void Flight::read_cities() {
    cout << "\nEnter Matrix Size: ";
    cin >> matrix_size;    // Number of cities to enter
    cin.ignore();          // Ignore newline left by cin

    for (int i = 1; i <= matrix_size; i++) {
        cout << "\nEnter City Name: ";
        getline(cin, cities[i]);   // Input city name
        cout << "Unique Code For " << cities[i] << " Is " << i << endl; // Display assigned code
    }
}

// Function to display all cities with their unique codes
void Flight::display_cities() {
    cout << "\nList of Cities with Their Unique Codes:\n";
    for (int i = 1; i <= matrix_size; i++) {
        cout << i << ". " << cities[i] << endl;
    }
}

// Function to read flight connections between cities
void Flight::read_flight() {
    int source, dest, time, fuel_amt;

    display_cities();  // Show available cities

    char choice;
    do {
        // Get source and destination codes
        cout << "\nEnter Code For Source City: ";
        cin >> source;
        cout << "Enter Code For Destination City: ";
        cin >> dest;

        // Get flight details
        cout << "Enter Time (in hours) from " << cities[source] << " to " << cities[dest] << ": ";
        cin >> time;
        cout << "Enter Fuel (in litres) from " << cities[source] << " to " << cities[dest] << ": ";
        cin >> fuel_amt;

        // Store in adjacency matrices
        mat[source][dest] = time;
        fuel[source][dest] = fuel_amt;

        // Ask if user wants to continue
        cout << "Do you want to add another flight (y/n)? ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');  // Repeat if user enters 'y' or 'Y'
}

// Function to display the time and fuel matrices
void Flight::display_flight() {
    display_cities(); // Show cities first for reference

    // Display Time Matrix
    cout << "\nFlight Time Matrix (in hours):\n\t";
    for (int i = 1; i <= matrix_size; i++) {
        cout << i << "\t"; // Print column headers
    }
    cout << "\n";
    for (int i = 1; i <= matrix_size; i++) {
        cout << i << "\t"; // Print row headers
        for (int j = 1; j <= matrix_size; j++) {
            cout << mat[i][j] << "\t"; // Print time values
        }
        cout << "\n";
    }

    // Display Fuel Matrix
    cout << "\nFuel Matrix (in litres):\n\t";
    for (int i = 1; i <= matrix_size; i++) {
        cout << i << "\t"; // Print column headers
    }
    cout << "\n";
    for (int i = 1; i <= matrix_size; i++) {
        cout << i << "\t"; // Print row headers
        for (int j = 1; j <= matrix_size; j++) {
            cout << fuel[i][j] << "\t"; // Print fuel values
        }
        cout << "\n";
    }
}

// Function to display direct and indirect flight paths between source and destination
void Flight::StoD() {
    int s, d;
    display_cities();  // Show city list

    // Input source and destination codes
    cout << "\nEnter Source City Code: ";
    cin >> s;
    cout << "Enter Destination City Code: ";
    cin >> d;

    // Check for direct flight
    if (mat[s][d] != 0) {
        cout << "\nDirect flight found from " << cities[s] << " to " << cities[d] 
             << " taking " << mat[s][d] << " hours and consuming " 
             << fuel[s][d] << " litres of fuel.\n";
    } else {
        cout << "\nNo direct flight from " << cities[s] << " to " << cities[d] << ".\n";
    }

    // Check for indirect flights (one stop)
    bool found = false;
    for (int k = 1; k <= matrix_size; k++) {
        // Ensure intermediate city 'k' is not same as source or destination
        if (k != s && k != d && mat[s][k] != 0 && mat[k][d] != 0) {
            cout << "Indirect flight via " << cities[k] << ": "
                 << cities[s] << " -> " << cities[k] << " -> " << cities[d]
                 << " taking " << (mat[s][k] + mat[k][d]) << " hours and "
                 << (fuel[s][k] + fuel[k][d]) << " litres of fuel.\n";
            found = true;
        }
    }

    // If no indirect path found
    if (!found) {
        cout << "No indirect flight path found from " << cities[s] << " to " << cities[d] << ".\n";
    }
}

// Function to list all directly connected cities from a given city
void Flight::all() {
    int s;
    display_cities(); // Show city list

    cout << "\nEnter City Code to List All Directly Connected Cities: ";
    cin >> s;

    cout << "\nCities directly connected from " << cities[s] << ":\n";
    bool connected = false;

    // Iterate through row 's' to check all direct connections
    for (int i = 1; i <= matrix_size; i++) {
        if (mat[s][i] != 0) {  // If there is a flight
            cout << "- " << cities[i] << " (Time: " << mat[s][i] 
                 << " hours, Fuel: " << fuel[s][i] << " litres)\n";
            connected = true;
        }
    }

    // If no connected city found
    if (!connected) {
        cout << "No cities are directly connected from " << cities[s] << ".\n";
    }
}

// Main function with menu-driven interface
int main() {
    Flight F1;  // Create a Flight object
    int x;      // Menu choice variable

    do {
        // Display menu options
        cout << "\n***Select An Option***";
        cout << "\n1. Enter Cities";
        cout << "\n2. Display Cities With Their Unique Code";
        cout << "\n3. Read Flight Matrix";
        cout << "\n4. Display Flights Matrix";
        cout << "\n5. Source To Destination Details(Direct & Indirect)";
        cout << "\n6. All Connected Cities To A City";
        cout << "\n7. Exit";
        cout << "\n\nEnter Choice: ";
        cin >> x;

        // Perform selected operation
        switch (x) {
            case 1:
                F1.read_cities();
                break;
            case 2:
                F1.display_cities();
                break;
            case 3:
                F1.read_flight();
                break;
            case 4:
                F1.display_flight();
                break;
            case 5:
                F1.StoD();
                break;
            case 6:
                F1.all();
                break;
            default:
                // Handle invalid input
                if (x != 7)
                    cout << "Invalid Choice!\n\n";
        }
    } while (x != 7);  // Continue until user selects Exit

    return 0;
}



/*

***Select An Option***
1. Enter Cities
2. Display Cities With Their Unique Code
3. Read Flight Matrix
4. Display Flights Matrix
5. Source To Destination Details(Direct & Indirect)
6. All Connected Cities To A City
7. Exit

Enter Choice: 1

Enter Matrix Size: 
3

Enter City Name: pune
Unique Code For pune Is 1

Enter City Name: mumbai
Unique Code For mumbai Is 2

Enter City Name: delhi
Unique Code For delhi Is 3

***Select An Option***
1. Enter Cities
2. Display Cities With Their Unique Code
3. Read Flight Matrix
4. Display Flights Matrix
5. Source To Destination Details(Direct & Indirect)
6. All Connected Cities To A City
7. Exit

Enter Choice: 2

List of Cities with Their Unique Codes:
1. pune
2. mumbai
3. delhi

***Select An Option***
1. Enter Cities
2. Display Cities With Their Unique Code
3. Read Flight Matrix
4. Display Flights Matrix
5. Source To Destination Details(Direct & Indirect)
6. All Connected Cities To A City
7. Exit

Enter Choice: 3

List of Cities with Their Unique Codes:
1. pune
2. mumbai
3. delhi

Enter Code For Source City: 1
Enter Code For Destination City: 


2
Enter Time (in hours) from pune to mumbai: 2
Enter Fuel (in litres) from pune to mumbai: 150
Do you want to add another flight (y/n)? y

Enter Code For Source City: 2
Enter Code For Destination City: 3
Enter Time (in hours) from mumbai to delhi: 4
Enter Fuel (in litres) from mumbai to delhi: 250
Do you want to add another flight (y/n)? y

Enter Code For Source City: 1
Enter Code For Destination City: 3
Enter Time (in hours) from pune to delhi: 5
Enter Fuel (in litres) from pune to delhi: 300
Do you want to add another flight (y/n)? n

***Select An Option***
1. Enter Cities
2. Display Cities With Their Unique Code
3. Read Flight Matrix
4. Display Flights Matrix
5. Source To Destination Details(Direct & Indirect)
6. All Connected Cities To A City
7. Exit

Enter Choice: 4

List of Cities with Their Unique Codes:
1. pune
2. mumbai
3. delhi

Flight Time Matrix (in hours):
	1	2	3	
1	0	2	5	
2	0	0	4	
3	0	0	0	

Fuel Matrix (in litres):
	1	2	3	
1	0	150	300	
2	0	0	250	
3	0	0	0	

***Select An Option***
1. Enter Cities
2. Display Cities With Their Unique Code
3. Read Flight Matrix
4. Display Flights Matrix
5. Source To Destination Details(Direct & Indirect)
6. All Connected Cities To A City
7. Exit

Enter Choice: 5

List of Cities with Their Unique Codes:
1. pune
2. mumbai
3. delhi

Enter Source City Code: 1
Enter Destination City Code: 3

Direct flight found from pune to delhi taking 5 hours and consuming 300 litres of fuel.
Indirect flight via mumbai: pune -> mumbai -> delhi taking 6 hours and 400 litres of fuel.

***Select An Option***
1. Enter Cities
2. Display Cities With Their Unique Code
3. Read Flight Matrix
4. Display Flights Matrix
5. Source To Destination Details(Direct & Indirect)
6. All Connected Cities To A City
7. Exit

Enter Choice: 6

List of Cities with Their Unique Codes:
1. pune
2. mumbai
3. delhi

Enter City Code to List All Directly Connected Cities: 1

Cities directly connected from pune:
- mumbai (Time: 2 hours, Fuel: 150 litres)
- delhi (Time: 5 hours, Fuel: 300 litres)




| Operation                  | Time Complexity | Explanation                              |
| -------------------------- | --------------- | ---------------------------------------- |
| Enter cities               | O(n)            | Reads city names                         |
| Read flights               | O(E)            | E = number of flight connections entered |
| Display matrices           | O(n²)           | Prints full matrix                       |
| Source → Destination check | O(n)            | Checks direct & indirect paths           |
| All connected cities       | O(n)            | Traverses one row of matrix              |
*/






