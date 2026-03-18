#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5 // Buffer size as per your notes

int buffer[N];
int in = 0, out = 0;
int writer_waiting_count = 0;

sem_t mutex, empty, full, read_gate;
pthread_mutex_t count_lock = PTHREAD_MUTEX_INITIALIZER;

void* producer(void* arg) {
    int item;
    while(1) {
        item = 100 + (rand() % 900);
        
        // Writer Priority: Block the "gate" for readers
        pthread_mutex_lock(&count_lock);
        writer_waiting_count++;
        if (writer_waiting_count == 1) sem_wait(&read_gate); 
        pthread_mutex_unlock(&count_lock);

        sem_wait(&empty);
        sem_wait(&mutex);
        
        buffer[in] = item;
        printf("Writer (Producer) added: %d at %d\n", item, in);
        in = (in + 1) % N;
        
        sem_post(&mutex);
        sem_post(&full);

        pthread_mutex_lock(&count_lock);
        writer_waiting_count--;
        if (writer_waiting_count == 0) sem_post(&read_gate); 
        pthread_mutex_unlock(&count_lock);
        
        sleep(1);
    }
}

void* consumer(void* arg) {
    int item;
    while(1) {
        // Reader Priority: Check if gate is open
        sem_wait(&read_gate);
        sem_post(&read_gate);

        sem_wait(&full);
        sem_wait(&mutex);
        
        item = buffer[out];
        printf("Reader (Consumer) removed: %d from %d\n", item, out);
        out = (out + 1) % N;
        
        sem_post(&mutex);
        sem_post(&empty);
        
        sleep(2);
    }
}

int main() {
    pthread_t p, c;
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);
    sem_init(&read_gate, 0, 1);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    return 0;
}