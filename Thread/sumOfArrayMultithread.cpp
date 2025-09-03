#include <iostream>
#include <thread>
using namespace std;

// Thread function to compute partial sum

void partial_sum(int arr[], int start, int end, int &result) {
    
    result = 0;
    
    for (int i = start; i < end; i++) {
        result += arr[i];
    }

}

int main() {
    
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = sizeof(arr) / sizeof(arr[0]);

    int sum1 = 0, sum2 = 0;  // local variables for each thread

    // Create two threads for two halves
    
    thread t1(partial_sum, arr, 0, n/2, ref(sum1));
    thread t2(partial_sum, arr, n/2, n, ref(sum2));

    // Wait for threads to finish

    t1.join();
    t2.join();

    int total_sum = sum1 + sum2;
    cout << "Total sum of array = " << total_sum << endl;

    return 0;
}
