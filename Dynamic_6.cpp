#include <iostream>
using namespace std;

int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n; // Input number of items
    cout << "Enter knapsack capacity W: ";
    cin >> W; // Input total capacity of knapsack

    int wt[100], val[100]; // Arrays to store weights and values of items (max 100 items)
    for (int i = 0; i < n; i++) {
        cout << "Enter weight and value of item " << (i+1) << ": ";
        cin >> wt[i] >> val[i]; // Input weight and value for each item
    }

    static int dp[101][10001]; // dp[i][w] = max value for first i items and capacity w
    // Using static so large array stays in global memory (avoids stack overflow)

    // Build DP table using bottom-up approach
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0; // Base case: no items or zero capacity → value = 0
            else if (wt[i-1] <= w)
                // If current item weight <= current capacity:
                // Choose max between including or excluding the item
                dp[i][w] = max(dp[i-1][w],dp[i-1][w-wt[i-1]]+val[i-1]);
            else
                // If current item weight > current capacity → cannot include item
                dp[i][w] = dp[i-1][w];
        }
    }

    // The result is stored at dp[n][W] → max value possible for n items and capacity W
    cout << "Maximum value = " << dp[n][W] << endl;

    return 0; // End of program
}



/*Enter number of items: 3
Enter knapsack capacity W: 50
Enter weight and value of item 1: 10 60
Enter weight and value of item 2: 20 100
Enter weight and value of item 3: 30 120
Maximum value = 220


=== Code Execution Successful ===

🧠 Explanation
Item	Weight	Value
1	10	60
2	20	100
3	30	120

Knapsack capacity W = 50

The combinations possible:

Item 1 + Item 2 → weight = 30, value = 160

Item 2 + Item 3 → weight = 50, value = 220  (Best)

Item 1 + Item 3 → weight = 40, value = 180

Hence, the maximum value = 220

 Time and Space Complexity

Time Complexity: O(n × W)
→ Each item processed for each weight value.

Space Complexity: O(n × W)
→ 2D DP array.*/