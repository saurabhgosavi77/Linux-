#include <iostream>
using namespace std;

int main() {
    int n, capacity;
    cout << "Enter number of items: ";
    cin >> n; // input number of items

    float value[20], weight[20], ratio[20];
    cout << "Enter capacity of knapsack: ";
    cin >> capacity; // input knapsack capacity

    // Input value and weight for each item and calculate value/weight ratio
    for (int i = 0; i < n; i++) {
        cout << "Enter value and weight of item " << i + 1 << ": ";
        cin >> value[i] >> weight[i];
        ratio[i] = value[i] / weight[i]; // ratio = value per unit weight
    }

    // Display value, weight, and ratio of each item
    cout << "\nCalculating value/weight ratio for each item:\n";
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << ": value = " << value[i] << ", weight = " << weight[i] 
             << ", ratio = " << ratio[i] << endl;
    }

    // Sort items by ratio in descending order (so highest value/weight comes first)
    cout << "\nSorting items by value/weight ratio in descending order:\n";
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (ratio[i] < ratio[j]) { // if next item has higher ratio, swap
                // swap all 3 arrays together to maintain item relation
                float temp = ratio[i];
                ratio[i] = ratio[j];
                ratio[j] = temp;

                temp = value[i];
                value[i] = value[j];
                value[j] = temp;

                temp = weight[i];
                weight[i] = weight[j];
                weight[j] = temp;

                cout << "Swapped item " << i + 1 << " with item " << j + 1 << endl;
            }
        }
    }

    // Display items after sorting by ratio
    cout << "\nItems after sorting:\n";
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << ": value = " << value[i] << ", weight = " << weight[i] 
             << ", ratio = " << ratio[i] << endl;
    }

    float totalValue = 0, currentWeight = 0; // initialize total value and weight of knapsack

    // Start filling the knapsack with sorted items
    cout << "\nFilling the knapsack:\n";
    for (int i = 0; i < n; i++) {
        if (currentWeight + weight[i] <= capacity) {
            // if item can be fully taken
            currentWeight += weight[i];
            totalValue += value[i];
            cout << "Taking full item " << i + 1 << " (weight = " << weight[i]
                 << ", value = " << value[i] << "). Current weight: " << currentWeight 
                 << ", total value: " << totalValue << endl;
        } else {
            // if only a fraction of item can be taken
            float remain = capacity - currentWeight; // remaining capacity
            totalValue += ratio[i] * remain; // take proportional value
            cout << "Taking fractional part of item " << i + 1 << " (weight = " << remain
                 << ", value = " << ratio[i] * remain << "). Knapsack is full now." << endl;
            break; // knapsack is full
        }
    }

    // Display final maximum value that can be achieved
    cout << "\nMaximum value that can be obtained = " << totalValue << endl;

    return 0;
}





/*Enter number of items: 3
Enter capacity of knapsack: 50
Enter value and weight of item 1: 60 10
Enter value and weight of item 2: 100 20
Enter value and weight of item 3: 120 30

Calculating value/weight ratio for each item:
Item 1: value = 60, weight = 10, ratio = 6
Item 2: value = 100, weight = 20, ratio = 5
Item 3: value = 120, weight = 30, ratio = 4

Sorting items by value/weight ratio in descending order:

Items after sorting:
Item 1: value = 60, weight = 10, ratio = 6
Item 2: value = 100, weight = 20, ratio = 5
Item 3: value = 120, weight = 30, ratio = 4

Filling the knapsack:
Taking full item 1 (weight = 10, value = 60). Current weight: 10, total value: 60
Taking full item 2 (weight = 20, value = 100). Current weight: 30, total value: 160
Taking fractional part of item 3 (weight = 20, value = 80). Knapsack is full now.

Maximum value that can be obtained = 240


=== Code Execution Successful ===*/




/*#include <iostream>
using namespace std;

int main() {
    int n, capacity;
    cout << "Enter number of items: ";
    cin >> n;

    float value[20], weight[20], ratio[20];
    cout << "Enter capacity of knapsack: ";
    cin >> capacity;

    // Input values and weights
    for (int i = 0; i < n; i++) {
        cout << "Enter value and weight of item " << i + 1 << ": ";
        cin >> value[i] >> weight[i];
        ratio[i] = value[i] / weight[i];  // value/weight ratio
    }

    // Sort items in descending order of ratio
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (ratio[i] < ratio[j]) {
                swap(ratio[i], ratio[j]);
                swap(value[i], value[j]);
                swap(weight[i], weight[j]);
            }
        }
    }

    float totalValue = 0, currentWeight = 0;

    // Fill knapsack
    for (int i = 0; i < n; i++) {
        if (currentWeight + weight[i] <= capacity) {
            // Take full item
            currentWeight += weight[i];
            totalValue += value[i];
        } else {
            // Take fractional part
            float remain = capacity - currentWeight;
            totalValue += ratio[i] * remain;
            break;  // Knapsack is full
        }
    }

    cout << "\nMaximum value that can be obtained = " << totalValue << endl;

    return 0;
}
*/