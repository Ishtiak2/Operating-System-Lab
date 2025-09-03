#include <iostream>
#include <thread>
#include <unistd.h> // for sleep

using namespace std;

void thread_fun() {
    cout << "Inside thread" << endl;
    for (int j = 0; j < 5; j++) {
        cout << j << endl;
        sleep(1);
    }
}

int main() {
    // create a thread
    thread t1(thread_fun);

    // wait for the thread to finish
    t1.join();

    cout << "Back to main process" << endl;
    for (int i = 15; i < 20; i++) {
        cout << i << endl;
        sleep(1);
    }

    return 0;
}
