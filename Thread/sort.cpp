#include <iostream>
#include <thread>
#include <algorithm> // for std::sort and std::merge

using namespace std;

// Function to sort a part of the array

void sort_part(int arr[], int start, int end) {
    sort(arr + start, arr + end); // sort from arr[start] to arr[end-1]
}

int main() {
    
    int arr[] = {9, 3, 7, 1, 8, 2, 6, 4};
    int n = sizeof(arr)/sizeof(arr[0]);

    int mid = n / 2;

    // Create threads to sort each half

    thread t1(sort_part, arr, 0, mid);
    thread t2(sort_part, arr, mid, n);

    t1.join();
    t2.join();

    // Merge the two sorted halves into a new array

    int sorted_arr[n];
    merge(arr, arr + mid, arr + mid, arr + n, sorted_arr);

    // Copy sorted result back to original array

    for (int i = 0; i < n; i++)
        arr[i] = sorted_arr[i];

    // Print sorted array

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
