#include <iostream>
#include <unistd.h>   // fork(), getpid(), getppid()
#include <sys/wait.h> // wait()

using namespace std;

int main() {
    
    const int num_children = 3;
    
    pid_t pid;

    for (int i = 0; i < num_children; i++) {
        
        pid = fork(); // create child process

        if (pid < 0) {
            cerr << "Fork failed!" << endl;
            return 1;
        }

        if (pid == 0) {
            // Child process
            cout << "Child " << i+1 << " PID: " << getpid() << ", Parent PID: " << getppid() << endl;
            
            return 0; // child exits
        }
        
        // Parent continues loop to create next child
    }

    // Parent process waits for all children
    for (int i = 0; i < num_children; i++) {
        wait(NULL);
    }

    cout << "Parent process PID: " << getpid() << " finished waiting for children." << endl;

    return 0;
}
