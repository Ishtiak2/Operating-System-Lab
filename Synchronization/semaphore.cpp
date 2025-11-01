#include <thread>
#include <semaphore.h>
#include <cstdio>
#include <unistd.h>

using namespace std;

int shared = 4;
sem_t s;

void thread_fun_1()
{
    sem_wait(&s); // Wait (decrement) the semaphore
    printf("Thread 1: Entering critical section\n");
    int temp = shared;
    sleep(1); // Simulate some work in the critical section
    shared = temp + 1;
    printf("Thread 1: Exiting critical section, shared = %d\n", shared);
    sem_post(&s); // Signal (increment) the semaphore
}

void thread_fun_2()
{
    sem_wait(&s); // Wait (decrement) the semaphore
    printf("Thread 2: Entering critical section\n");
    int temp = shared;
    sleep(1); // Simulate some work in the critical section
    shared = temp + 2;
    printf("Thread 2: Exiting critical section, shared = %d\n", shared);
    sem_post(&s); // Signal (increment) the semaphore
}

int main()
{
    sem_init(&s, 0, 1); // Initialize semaphore with value 1
    
    thread thread1(thread_fun_1);
    thread thread2(thread_fun_2);
    
    thread1.join();
    thread2.join();
    
    printf("Final value of shared variable: %d\n", shared);
    sem_destroy(&s); // Destroy the semaphore
    return 0;
}