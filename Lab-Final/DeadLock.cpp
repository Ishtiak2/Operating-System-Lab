#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h> // for sleep

using namespace std;

mutex mtx1;
mutex mtx2;

void thread1_fun() {
    
    cout << "Thread 1: Trying to lock mtx1" << endl;
    
    mtx1.lock(); // Thread 1 owns resource 1
    cout << "Thread 1: Locked mtx1" << endl;

    sleep(1); // wait so that thread 2 can lock mtx2

    cout << "Thread 1: Trying to lock mtx2" << endl;
    mtx2.lock();
    cout << "Thread 1: Locked mtx2" << endl;

    // Unlock (will never reach if deadlock occurs)
    mtx2.unlock();
    mtx1.unlock();
}

void thread2_fun() {
    cout << "Thread 2: Trying to lock mtx2" << endl;
    
    mtx2.lock(); // Thread 2 owns resource 2
    cout << "Thread 2: Locked mtx2" << endl;

    sleep(1); // wait so that thread 1 can lock mtx1

    cout << "Thread 2: Trying to lock mtx1" << endl;
    mtx1.lock();
    cout << "Thread 2: Locked mtx1" << endl;

    // Unlock (will never reach if deadlock occurs)
    mtx1.unlock();
    mtx2.unlock();
}

int main() {
    cout << "Main: Starting threads" << endl;

    thread t1(thread1_fun);
    thread t2(thread2_fun);

    t1.join();
    t2.join();

    cout << "Main: Threads finished" << endl;

    return 0;
}