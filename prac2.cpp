#include <iostream>
#include <pthread.h>
#include <queue>

using namespace std;

const int BUFFER_SIZE = 5;
const int NUM_PRODUCERS = 2;
const int NUM_CONSUMERS = 2;
const int NUM_ITEMS = 10;

queue<int> buffer;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_full = PTHREAD_COND_INITIALIZER;

void* Producer(void* producer_id) {
    int producer_num = *((int*)producer_id);
    for (int i = 0; i < NUM_ITEMS; ++i) {
        int item = i + 1;

        pthread_mutex_lock(&mutex);

        while (buffer.size() == BUFFER_SIZE) {
            pthread_cond_wait(&buffer_empty, &mutex);
        }

        cout << "Producer " << producer_num << " produces item " << item << endl;
        buffer.push(item);

        pthread_cond_signal(&buffer_full);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* Consumer(void* consumer_id) {
    int consumer_num = *((int*)consumer_id);
    for (int i = 0; i < NUM_ITEMS; ++i) {
        pthread_mutex_lock(&mutex);

        while (buffer.empty()) {
            pthread_cond_wait(&buffer_full, &mutex);
        }

        int item = buffer.front();
        buffer.pop();

        cout << "Consumer " << consumer_num << " consumes item " << item << endl;

        pthread_cond_signal(&buffer_empty);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];

    int producer_ids[NUM_PRODUCERS];
    int consumer_ids[NUM_CONSUMERS];

    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        producer_ids[i] = i + 1;
        pthread_create(&producers[i], NULL, Producer, &producer_ids[i]);
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        consumer_ids[i] = i + 1;
        pthread_create(&consumers[i], NULL, Consumer, &consumer_ids[i]);
    }

    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        pthread_join(consumers[i], NULL);
    }

    return 0;
}
