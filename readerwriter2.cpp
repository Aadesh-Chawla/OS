#include<bits/stdc++.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

using namespace std;


int h=0,m=0,s=0;
sem_t s1,s2;

void* reader(void* ret){
    // cout<<"Reader thread is running.";
    while(true){

    sem_post(&s1);
    cout<<"Reader enters the critical region"<<endl;
    cout << "Time: " << h << ":" << m << ":" << s <<endl;
    sem_wait(&s1);
    sleep(1);
    }
}

void* writer(void* ret){
    // cout<<"writer thread is running.";
    while(true){

    sem_post(&s2);
    cout<<"Writer enters the critical region"<<endl;

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
    sem_wait(&s2);
        sleep(1);
    }
}

int main(){
    pthread_t rth,wth;
    int r1,r2;

    r1=pthread_create(&rth,NULL,reader,NULL);
    r2=pthread_create(&wth,NULL,writer,NULL);

    if (r1 || r2) {
        cerr << "Error creating threads" <<endl;
        return 1;
    }

    sem_init(&s1, 0, 0);
    sem_init(&s2, 0, 0);

    // cout<<s1<<endl;
    // cout<<s2<<endl;

    // sleep(5);

    pthread_join(rth,NULL);
    pthread_join(wth,NULL);


    sem_destroy(&s1);
    sem_destroy(&s2);
    

    return 0;
}
