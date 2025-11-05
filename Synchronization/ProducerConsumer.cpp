
//This is simulation. Not the actual thing

#include <iostream>
using namespace std;

int bufferSize;      // maximum capacity of buffer
int items = 0;       // current number of items in buffer
bool mutex_ = false; // for mutual exclusion
bool isFull = false; // true when buffer is full
bool isEmpty = true; // true when buffer is empty

void producer()
{
    mutex_ = true;
    isEmpty = false;

    items++;
    cout << "\nProducer produced item-" << items;

    if (items == bufferSize)
        isFull = true; // buffer is now full

    mutex_ = false;
}

void consumer()
{
    mutex_ = true;
    isFull = false;

    cout << "\nConsumer consumed item-" << items << endl;
    items--;

    if (items == 0)
        isEmpty = true; // buffer is now empty

    mutex_ = false;
}

int main()
{
    cout << "Enter the buffer size: ";
    cin >> bufferSize;

    int choice;
    do
    {
        cout << "\n\n     SELECT OPERATION\n"
             << "-----------------------------\n"
             << "1) Produce an item\n"
             << "2) Consume an item\n"
             << "3) Check if full\n"
             << "4) Check if empty\n"
             << "5) Exit\n"
             << "-----------------------------\n"
             << "Enter your choice: ";
        cin >> choice;

        if (choice == 1 && !mutex_) //important
        {
            if (!isFull)
                producer();
            else
                cout << "\nThe buffer is full!\n";
        }
        else if (choice == 2 && !mutex_) //important
        {
            if (!isEmpty)
                consumer();
            else
                cout << "\nThe buffer is empty!\n";
        }
        else if (choice == 3)
        {
            cout << (isFull ? "\nThe buffer is full!\n"
                            : "\nThe buffer has more space...\n");
        }
        else if (choice == 4)
        {
            cout << (isEmpty ? "\nThe buffer is empty!\n"
                             : "\nThe buffer has more items...\n");
        }
        else if (choice == 5)
        {
            cout << "\nExiting program...\n";
        }
        else
        {
            cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 5);

    return 0;
}