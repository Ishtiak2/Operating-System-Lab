#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        cerr << "Fork failed!" << endl;
        return 1;
    }

    if (pid == 0) {
        // Child process
        cout << "Child process PID: " << getpid() << " exiting immediately." << endl;
        exit(0); // terminate child
    } 
    else {
        // Parent process
        cout << "Parent process PID: " << getpid() << " sleeping..." << endl;
        sleep(10); // parent sleeps without waiting
        cout << "Parent wakes up and can now call wait()" << endl;

        // Wait for child to clean up (optional)
        wait(NULL);
    }

    return 0;
}

/*
A zombie happens when the child has exited but parent hasn’t called wait().
Zombie processes do not consume CPU, only a process table entry.
To remove a zombie, the parent must call wait() or terminate.

How to Observe Zombie

Compile and run:

While the parent is sleeping (during sleep(10)), open another terminal and run: ps -l

You will see the child process with Z state → Zombie.
Once the parent calls wait(NULL), the zombie disappears.
S = Z or <defunct> indicates zombie process.

Example:   501  9696  9695     2006   0   0  0        0      0 -      Z+                  0 ttys010    0:00.00 <defunct>
*/