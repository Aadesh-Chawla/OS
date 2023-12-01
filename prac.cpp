#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <vector>

using namespace std;

const int BUFFER_SIZE = 5; // Size of the shared buffer
const int NUM_PRODUCERS = 2;
const int NUM_CONSUMERS = 2;
const int NUM_ITEMS = 10; // Total number of items to produce/consume

vector<int> buffer(BUFFER_SIZE);
sem_t emt;  // Semaphore to track empty slots in the buffer
sem_t full;   // Semaphore to track filled slots in the buffer
pthread_mutex_t mutex; // Mutex to protect the buffer

int itemCount = 0; // Counter for the number of items produced

void* Producer(void* id) {
    int producerId = *((int*)id);

    for (int i = 0; i < NUM_ITEMS; i++) {
        // Produce item
        int item = rand() % 100;

        // Wait for an empty slot in the buffer
        sem_wait(&emt);
        pthread_mutex_lock(&mutex);

        // Add item to the buffer
        buffer[itemCount] = item;
        itemCount++;

        cout << "Producer " << producerId << " produced item " << item << endl;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }

    pthread_exit(NULL);
}

void* Consumer(void* id) {
    int consumerId = *((int*)id);

    for (int i = 0; i < NUM_ITEMS; i++) {
        // Wait for a filled slot in the buffer
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        // Remove item from the buffer
        int item = buffer[itemCount - 1];
        itemCount--;

        cout << "Consumer " << consumerId << " consumed item " << item << endl;

        pthread_mutex_unlock(&mutex);
        sem_post(&emt);
    }

    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));
    
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];

    sem_init(&emt, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    int producerIds[NUM_PRODUCERS];
    int consumerIds[NUM_CONSUMERS];

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        producerIds[i] = i + 1;
        pthread_create(&producers[i], NULL, Producer, &producerIds[i]);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        consumerIds[i] = i + 1;
        pthread_create(&consumers[i], NULL, Consumer, &consumerIds[i]);
    }

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    sem_destroy(&emt);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

