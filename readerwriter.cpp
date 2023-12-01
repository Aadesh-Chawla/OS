#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> 

int h = 0, m = 0, s = 0;
sem_t s1, s2;

void* read(void* ret) {
    while (true) {
        sem_wait(&s2);
        system("cls");
        std::cout << "Time: " << h << ":" << m << ":" << s << std::endl;
        sem_post(&s2);
        sleep(1);
    }
}

void* write(void* ret) {
    while (true) {
        sem_wait(&s1);
        s++;
        if (s == 60) {
            s = 0;
            m++;
            if (m == 60) {
                m = 0;
                h++;
                if (h == 24) {
                    h = 0;
                }
            }
        }
        sem_post(&s1);
        sleep(1);
    }
}

int main() {
    pthread_t rth, wth;
    int r1, r2;

    r1 = pthread_create(&rth, NULL, read, NULL);
    r2 = pthread_create(&wth, NULL, write, NULL);

    if (r1 || r2) {
        std::cerr << "Error creating threads" << std::endl;
        return 1;
    }

    sem_init(&s1, 0, 1);
    sem_init(&s2, 0, 1);

    // Allow threads to run for a certain time
    sleep(15);

    sem_destroy(&s1);
    sem_destroy(&s2);

    return 0;
}
