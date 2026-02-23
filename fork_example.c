#include <stdio.h>
#include <unistd.h> /*POSIX standard header file in C that provides access to operating system services*/
#include <sys/types.h>  /*POSIX / UNIX header file that defines data types used in system calls and low-level OS programming.*/

int main() {
    pid_t pid; //declares a variable pid of type pid_t, which is used to store a process ID.
    pid = fork();   // create a new process

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } 
    else if (pid == 0) {
        // Child process
        printf("Child Process:\n");
        printf("   Child PID: %d\n", getpid());/* get the Process ID (PID) of the currently running process.*/
        printf("   Parent PID: %d\n", getppid()); /*Parent Process ID (PPID) of the current process.*/
    } 
    else {
        // Parent process
        printf("Parent Process:\n");
        printf("   Parent PID: %d\n", getpid());
        printf("   Child PID: %d\n", pid);
        sleep(30);  // delay so pstree can show both processes
    }
    return 0;
}
