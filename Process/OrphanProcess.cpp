#include <iostream>
#include <unistd.h>
#include <sys/types.h>
using namespace std;

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        cerr << "Fork failed!" << endl;
        return 1;
    }

    if (pid == 0) {
        // Child process

        sleep(5); // wait to let parent terminate
        cout << "Child process PID: " << getpid()  << ", Parent PID: " << getppid() << " (adopted by init)" << endl;
    } 
    else {
        // Parent process

        cout << "Parent process PID: " << getpid() << " exiting immediately." << endl;
        return 0; // parent exits immediately
    }

    return 0;
}

/*
An orphan process is a process whose parent has terminated before it finishes.

Orphan process → parent terminates first.
Zombie process → child terminates first, parent hasn’t waited.
Orphan processes are automatically adopted by init (PID = 1).
Useful to understand process hierarchy in OS.
*/