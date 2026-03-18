#include <stdio.h>

// Simulated semaphores
int mutex = 1;
int wrt = 1;
int readTry = 1;
int readcount = 0;

// wait (P operation)
void wait(int *s) {
    while (*s <= 0); // busy wait
    (*s)--;
}

// signal (V operation)
void signal(int *s) {
    (*s)++;
}

// Reader process
void reader(int id) {
    // Entry section
    wait(&readTry);
    wait(&mutex);

    readcount++;
    if (readcount == 1)
        wait(&wrt);

    signal(&mutex);
    signal(&readTry);

    // Critical section
    printf("Reader %d is reading\n", id);

    // Exit section
    wait(&mutex);

    readcount--;
    if (readcount == 0)
        signal(&wrt);

    signal(&mutex);
}

// Writer process
void writer(int id) {
    // Entry section
    wait(&readTry);
    wait(&wrt);

    // Critical section
    printf("Writer %d is writing\n", id);

    // Exit section
    signal(&wrt);
    signal(&readTry);
}

int main() {
    // Simulated execution order
    reader(1);
    reader(2);
    writer(1);
    reader(3);
    writer(2);

    return 0;
}