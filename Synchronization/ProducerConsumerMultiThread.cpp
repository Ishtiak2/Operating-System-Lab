#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h> // for sleep()

using namespace std;

#define BUFFER_SIZE 5
#define TOTAL_ITEMS 10

int buffer[BUFFER_SIZE]; // shared buffer
int in = 0;              // index where producer will put next item
int out = 0;             // index where consumer will take next item
int count = 0;           // current number of items in buffer

mutex mtx;

void producer()
{
    int item = 0;
    while (item < TOTAL_ITEMS)
    {
        mtx.lock();
        if (count < BUFFER_SIZE)
        {
            int value = rand() % 100;
            buffer[in] = value;
            in = (in + 1) % BUFFER_SIZE;
            count++;
            item++;
            cout << "Produced: " << value << " | Buffer count: " << count << endl;
        }
        
        else
        {
            cout << "⚠️ Buffer full! Producer waiting...\n";
        }

        mtx.unlock();
        sleep(1);
    }
}

void consumer()
{
    int consumed = 0;
    while (consumed < TOTAL_ITEMS)
    {
        mtx.lock();
        if (count > 0)
        {
            int value = buffer[out];
            out = (out + 1) % BUFFER_SIZE;
            count--;
            consumed++;
            cout << "Consumed: " << value << " | Buffer count: " << count << endl;
        }
        
        else
        {
            cout << "Buffer empty! Consumer waiting...\n";
        }
        mtx.unlock();
        sleep(2);
    }
}

int main()
{
    srand(time(NULL));

    thread t1(producer);
    thread t2(consumer);

    t1.join();
    t2.join();

    cout << "Finished! All " << TOTAL_ITEMS << " items produced and consumed.\n";
    return 0;
}