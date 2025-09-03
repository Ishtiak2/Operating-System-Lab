// to demonstrate the use of fork system call 

#include <stdio.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/wait.h>


int main() {
    pid_t pid = fork();   // create a new process

    if (pid > 0) {
        printf("I am the parent. My PID is %d. My child’s PID is %d\n", getpid(), pid);
    } 
    
    else if (pid == 0) {
        printf("I am the child. My PID is %d, my parent’s PID is %d\n", getpid(), getppid());
    } 
    
    else {
        printf("Fork failed!\n");
    }

    return 0;
}


/*
In the parent process, fork() returns the child’s process ID (PID) (a positive number).
In the child process, fork() returns 0.
If fork() fails (e.g., system resource limit), it returns -1.

getpid() → returns your own PID
getppid() → returns your parent’s PID

Output appears twice because two processes(parent & child) run the same code after fork().

*/