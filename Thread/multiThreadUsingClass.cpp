#include <iostream>
#include <thread>
using namespace std;

class ThreadData {
public:
    int* array;
    int start;
    int end;
    int result;

    ThreadData(int* array, int start, int end) {
        this->array = array;
        this->start = start;
        this->end = end;
        this->result = 0;
    }
};

// Thread function outside the class

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

    // Create ThreadData objects

    ThreadData data1(array, 0, n/2);
    ThreadData data2(array, n/2, n);

    // Create threads passing pointer to ThreadData
    
    thread t1(partial_sum, &data1);
    thread t2(partial_sum, &data2);

    t1.join();
    t2.join();

    cout << "Sum of first half: " << data1.result << endl;
    cout << "Sum of second half: " << data2.result << endl;
    cout << "Total sum: " << data1.result + data2.result << endl;

    return 0;
}
