#include <iostream>
#include <thread>
using namespace std;

// Thread function: compute sum of an array

void compute_sum(int arr[], int n, int &result) {
    result = 0;  // initialize
    for (int i = 0; i < n; i++) {
        result += arr[i];
    }
}

int main() {
    
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int sum = 0;

    // Pass sum by reference using ref
    
    thread t1(compute_sum, arr, n, ref(sum));

    t1.join();  // wait for thread to finish

    cout << "Sum of array = " << sum << endl;

    return 0;
}
