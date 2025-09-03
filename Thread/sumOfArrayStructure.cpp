#include <iostream>
#include <thread>
#include <vector>
using namespace std;

// Structure to hold thread data

struct ThreadData {
    int *array;
    int start;
    int end;
    int result; // store sum of this part
};

// Thread function to compute partial sum

void partial_sum(ThreadData* data) {
    data->result = 0;
    for (int i = data->start; i < data->end; i++) {
        data->result += data->array[i];
    }
}

int main() {
    const int n = 100;
    
    int array[n];
    
    for (int i = 0; i < n; i++)
        array[i] = i + 1;

    // Create ThreadData for two halves
    
    ThreadData data1 {array, 0, n/2, 0};
    ThreadData data2 {array, n/2, n, 0};

    // Create threads
    
    thread t1(partial_sum, &data1);
    thread t2(partial_sum, &data2);

    // Wait for threads to finish
    t1.join();
    t2.join();

    
    cout << "Sum of first half: " << data1.result << endl;
    cout << "Sum of second half: " << data2.result << endl;
    cout << "Total sum: " << data1.result + data2.result << endl;

    return 0;
}
