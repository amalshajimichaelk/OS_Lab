#include <stdio.h>

#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;

// Simulated semaphores
int mutex = 1;
int empty = SIZE;
int full = 0;

// wait (P)
void wait(int *s) {
    while (*s <= 0);   // busy wait
    (*s)--;
}

// signal (V)
void signal(int *s) {
    (*s)++;
}

// Producer
void producer(int item) {
    wait(&empty);
    wait(&mutex);

    buffer[in] = item;
    printf("Produced: %d at position %d\n", item, in);
    in = (in + 1) % SIZE;

    signal(&mutex);
    signal(&full);
}

// Consumer
void consumer() {
    wait(&full);
    wait(&mutex);

    int item = buffer[out];
    printf("Consumed: %d from position %d\n", item, out);
    out = (out + 1) % SIZE;

    signal(&mutex);
    signal(&empty);
}

int main() {
    int choice, item;

    while (1) {
        printf("\n--- Producer Consumer Menu ---\n");
        printf("1. Produce\n");
        printf("2. Consume\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (empty == 0) {
                    printf("Buffer Full! Cannot produce.\n");
                } else {
                    printf("Enter item to produce: ");
                    scanf("%d", &item);
                    producer(item);
                }
                break;

            case 2:
                if (full == 0) {
                    printf("Buffer Empty! Cannot consume.\n");
                } else {
                    consumer();
                }
                break;

            case 3:
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
