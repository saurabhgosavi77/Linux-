#include <iostream>
using namespace std;

// Function to swap two integers using reference variables
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// ------------------------------------------------------------
// Function to restore (reheap down) the MAX HEAP property
// ------------------------------------------------------------
void reheapDownMax(int a[], int n, int i) {
    int j, temp;
    // Continue while current node has at least a left child
    while (2*i + 1 < n) {
        j = 2*i + 1; // Left child index
        // If right child exists and is greater than left child, select right
        if (j+1 < n && a[j+1] > a[j])
            j = j + 1; // Right child index

        // If parent is already greater than or equal to child, heap is valid
        if (a[i] >= a[j])
            break;
        else {
            // Otherwise, swap parent with larger child and move down
            swap(a[i], a[j]);
            i = j;
        }
    }
}

// ------------------------------------------------------------
// Function to restore (reheap down) the MIN HEAP property
// ------------------------------------------------------------
void reheapDownMin(int a[], int n, int i) {
    int j;
    // Continue while current node has at least a left child
    while (2*i + 1 < n) {
        j = 2*i + 1; // Left child index
        // If right child exists and is smaller than left child, select right
        if (j+1 < n && a[j+1] < a[j])
            j = j + 1; // Right child index

        // If parent is already smaller than or equal to child, heap is valid
        if (a[i] <= a[j])
            break;
        else {
            // Otherwise, swap parent with smaller child and move down
            swap(a[i], a[j]);
            i = j;
        }
    }
}

// ------------------------------------------------------------
// Function to build a MAX HEAP from an unsorted array
// ------------------------------------------------------------
void buildMaxHeap(int a[], int n) {
    // Start from last non-leaf node and move upwards
    for (int i = n/2 - 1; i >= 0; i--)
        reheapDownMax(a, n, i);
}

// ------------------------------------------------------------
// Function to build a MIN HEAP from an unsorted array
// ------------------------------------------------------------
void buildMinHeap(int a[], int n) {
    // Start from last non-leaf node and move upwards
    for (int i = n/2 - 1; i >= 0; i--)
        reheapDownMin(a, n, i);
}

// ------------------------------------------------------------
// Main function
// ------------------------------------------------------------
int main() {
    int marks[50], n;
    cout << "Enter number of students: ";
    cin >> n; // Input number of students

    // Input marks of all students
    for (int i = 0; i < n; i++) {
        cout << "Enter marks obtained by student " << i << " :";
        cin >> marks[i];
    }

    int choice;
    // Menu-driven program
    do {
        cout << "\nMenu\n1. Find Maximum marks\n2. Find Minimum marks\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Build max heap → root (index 0) will have maximum marks
                buildMaxHeap(marks, n);
                cout << "Maximum marks obtained: " << marks[0] << endl;
                break;

            case 2:
                // Build min heap → root (index 0) will have minimum marks
                buildMinHeap(marks, n);
                cout << "Minimum marks obtained: " << marks[0] << endl;
                break;

            case 3:
                // Exit the program
                cout << "Exiting program.\n";
                break;

            default:
                // If user enters an invalid choice
                cout << "Invalid choice! Try again.\n";
                break;
        }
    } while (choice != 3); // Repeat until user chooses Exit

    return 0;
}


/*Enter number of students: 
5
Enter marks obtained by student 0 :45
Enter marks obtained by student 1 :78
Enter marks obtained by student 2 :62
Enter marks obtained by student 3 :90
Enter marks obtained by student 4 :55

Menu
1. Find Maximum marks
2. Find Minimum marks
3. Exit
Enter your choice: 1
Maximum marks obtained: 90


⚙️ Complexity Analysis
Operation	Time Complexity	Space Complexity
Build Max/Min Heap	O(n)	O(1)
Access Max/Min	O(1)	O(1)
 */