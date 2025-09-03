#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){

    pid_t pid = fork();

    if(pid==0){
        printf("Child : My pid is %d\n",getpid());
        sleep(10);
        
        printf("Child : I am exiting now \n");
        
        exit(42);
    }
    
    else if(pid > 0) {
        int status;
        
        wait(&status);
        
        printf("Parent: Child exited with status %d\n",WEXITSTATUS(status));
    }

 }

 /*
 sleep(2); → pauses the current process for 2 seconds. During this time, the CPU can execute other processes.
 exit(42) -> The child process terminates and returns 42 to the parent.
 
 wait(&status) -> Parent is blocked (paused) until child finishes. Its exit code or termination reason is stored in status variable.
 WEXITSTATUS(status): “Get the exit code of the child from the status returned by wait()"
 */