#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h> // for sleep()

using namespace std;

int datas = 0;      // shared data
int readCount = 0; // number of active readers

mutex mtx;        // protects readCount
mutex writeMutex; // ensures exclusive access for writer

void reader(int id)
{
    for (int i = 0; i < 3; i++)
    { // read 3 times
        mtx.lock();
        readCount++;
        if (readCount == 1)
            writeMutex.lock(); // first reader locks writer
        mtx.unlock();

        // Reading (critical section)
        cout << "👁️ Reader " << id << " reads data = " << datas << endl;
        sleep(1);

        mtx.lock();
        readCount--;
        if (readCount == 0)
            writeMutex.unlock(); // last reader unlocks writer
        mtx.unlock();

        sleep(1); // simulate time between reads
    }
}

void writer(int id)
{
    for (int i = 0; i < 3; i++)
    {                      // write 3 times
        writeMutex.lock(); // exclusive access
        datas = rand() % 100;
        cout << "✏️ Writer " << id << " writes data = " << datas << endl;
        sleep(2);
        writeMutex.unlock();
        sleep(1); // simulate time between writes
    }
}

int main()
{
    srand(time(NULL));

    thread r1(reader, 1);
    thread r2(reader, 2);
    thread w1(writer, 1);

    r1.join();
    r2.join();
    w1.join();

    cout << "\nFinished Reading and Writing.\n";
    return 0;
}