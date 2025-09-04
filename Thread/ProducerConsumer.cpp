#include <iostream>
#include <thread>
#include<unistd.h>

using namespace std;

int buffer[10];
int buffer_count = 0; // rename

void producer() {
    for (int i = 1; i <= 10; i++) {
        buffer[buffer_count++] = i; // use renamed variable
        cout << "Produced: " << i << endl;
        sleep(2);
    }
}

void consumer() {
    int consumed = 0;
    while (consumed < 10) {
        if (buffer_count > 0) {
            int val = buffer[--buffer_count]; // remove from buffer
            cout << "Consumed: " << val << endl;
            consumed++;
        }
        sleep(1);
    }
}

int main() {
    thread t1(producer);
    thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}
