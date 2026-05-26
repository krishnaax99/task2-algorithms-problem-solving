#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

// ================= MERGE SORT =================

// Time Complexity: O(n log n)

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// ================= BINARY SEARCH =================

// Time Complexity: O(log n)

int binarySearch(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return mid;

        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

// ================= KNAPSACK =================

// Time Complexity: O(n * W)

int knapsack(vector<int>& weights, vector<int>& values, int capacity, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(
                    values[i - 1] + dp[i - 1][w - weights[i - 1]],
                    dp[i - 1][w]
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][capacity];
}

// ================= MAIN =================

int main() {
    int choice;

    while (true) {
        cout << "\n===== ALGORITHM MENU =====\n";
        cout << "1. Merge Sort\n";
        cout << "2. Binary Search\n";
        cout << "3. Knapsack\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 4)
            break;

        auto start = high_resolution_clock::now();

        switch (choice) {

        case 1: {
            vector<int> arr = {12, 4, 7, 9, 1, 15, 3};

            cout << "Original Array: ";
            for (int x : arr)
                cout << x << " ";

            cout << endl;

            mergeSort(arr, 0, arr.size() - 1);

            cout << "Sorted Array: ";
            for (int x : arr)
                cout << x << " ";

            cout << endl;
            break;
        }

        case 2: {
            vector<int> arr = {1, 3, 5, 7, 9, 11, 15};

            int target;
            cout << "Enter number to search: ";
            cin >> target;

            int result = binarySearch(arr, target);

            if (result != -1)
                cout << "Element found at index " << result << endl;
            else
                cout << "Element not found.\n";

            break;
        }

        case 3: {
            vector<int> weights = {1, 3, 4, 5};
            vector<int> values = {1, 4, 5, 7};

            int capacity = 7;

            int result = knapsack(weights, values, capacity, weights.size());

            cout << "Maximum Value: " << result << endl;
            break;
        }

        default:
            cout << "Invalid choice.\n";
        }

        auto end = high_resolution_clock::now();

        duration<double> runtime = end - start;

        cout << "Execution Time: "
             << runtime.count()
             << " seconds\n";
    }

    cout << "Program Ended.\n";

    return 0;
}
