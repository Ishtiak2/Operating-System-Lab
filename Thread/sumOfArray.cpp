#include <iostream>
#include <thread>
using namespace std;

// Global variable to store the sum

int sum = 0;

// Thread function to compute sum of an array

void compute_sum(int arr[], int n) {
    
    sum = 0;  // initialize
    
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
}

int main() {
    
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Create a thread to compute sum
    
    thread t1(compute_sum, arr, n);

    // Wait for thread to finish
    
    t1.join();

    cout << "Sum of array = " << sum << endl;

    return 0;
}

/*
thread name(function,arg1,arg2...)
*/