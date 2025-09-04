#include <bits/stdc++.h>
#include <thread>
using namespace std;

// Compute maximum in a part of array

void maximum(int arr[], int start, int end, int &result) {
    
    result = arr[start]; // start with first element
    
    for (int i = start + 1; i < end; i++) {
        if (arr[i] > result)
            result = arr[i];
    }
}

int main() {
    int arr[6] = {1, 3, 2, 5, 9, 4};
    int n = 6;

    int max1 = 0, max2 = 0;

    // Each thread writes to its own max variable

    thread t1(maximum, arr, 0, n/2, ref(max1));
    thread t2(maximum, arr, n/2, n, ref(max2));

    t1.join();
    t2.join();

    // Compute final maximum
    int final_max = max(max1, max2);

    cout << "Maximum = " << final_max << endl;

    return 0;
}

/*
Use seperate max variable for the two threads.
Using a single max -> Both threads are reading and writing max at the same time → race condition.
*/