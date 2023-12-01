#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;

#define DISK_SIZE 170

void fcfs(int request[], int n, int head);
void sstf(int request[], int n, int head);
void scan(int request[], int n, int head, int direction);
void cscan(int request[], int n, int head);
void look(int request[], int n, int head, int direction);
void clook(int request[], int n, int head);

int higherSeek(int request[], int n, int* pHead);
int lowerSeek(int request[], int n, int* pHead);

int main() {
    int n, head, direction;

     cout << "Enter number of requests:";
     cin >> n;

    int* request = nullptr;
    request = new int[n];
    assert(request != nullptr);

     cout << "Enter requests:";
    for (int i = 0; i < n; ++i) {
         cin >> request[i];
    }

     cout << "Enter initial head position:";
     cin >> head;
    if (head < 0 || head >= DISK_SIZE) {
         cout << "Invalid head position!" <<  endl;
        exit(EXIT_FAILURE);
    }

     cout << "Enter the direction (0 for higher values and 1 for lower values):";
     cin >> direction;

    if (direction != 0 && direction != 1) {
         cout << "Invalid direction!" <<  endl;
        exit(EXIT_FAILURE);
    }

    fcfs(request, n, head);
    sstf(request, n, head);
    scan(request, n, head, direction);
    look(request, n, head, direction);
    cscan(request, n, head);
    clook(request, n, head);

    delete[] request;

    exit(0);
}

void fcfs(int request[], int n, int head) {
    int totalSeekTime = 0;

     cout << "\n---FCFS Algorithm---" <<  endl;
     cout << "Head position:\t" << head <<  endl;
    for (int i = 0; i < n; ++i) {
        totalSeekTime +=  abs(head - request[i]);
        head = request[i];
         cout << "Request processed:\t" << head <<  endl;
    }

     cout << "\nTotal Seek Time = " << totalSeekTime <<  endl;
     cout << "---End of FCFS---" <<  endl;
}

void sstf(int request[], int n, int head) {
    int totalSeekTime = 0;
     cout << "\n---SSTF Algorithm---" <<  endl;
     cout << "Head position:\t" << head <<  endl;

    int* visited = nullptr;
    visited = new int[n];
    assert(visited != nullptr);

    for (int i = 0; i < n; ++i)
        visited[i] = 0;

    for (int i = 0; i < n; ++i) {
        int minDistance = DISK_SIZE;
        int index = -1;

        for (int j = 0; j < n; ++j) {
            if (!visited[j] &&  abs(head - request[j]) < minDistance) {
                index = j;
                minDistance =  abs(head - request[j]);
            }
        }

        visited[index] = 1;
        totalSeekTime += minDistance;
        head = request[index];
         cout << "Request processed:\t" << head <<  endl;
    }

     cout << "\nTotal Seek Time = " << totalSeekTime <<  endl;
     cout << "---End of SSTF---" <<  endl;

    delete[] visited;
}

void scan(int request[], int n, int head, int direction) {
     cout << "\n---SCAN Algorithm---" <<  endl;
     cout << "Head Position:\t" << head <<  endl;

    int currentHead;
    int totalSeekTime = 0;

    if (direction == 0) {
        currentHead = head;
        totalSeekTime += higherSeek(request, n, &currentHead);
        totalSeekTime += 2 * (DISK_SIZE - currentHead);
        totalSeekTime +=  abs(head - currentHead);
        currentHead = head;
        totalSeekTime += lowerSeek(request, n, &currentHead);
    } else {
        currentHead = head;
        totalSeekTime += lowerSeek(request, n, &currentHead);
        totalSeekTime += 2 * (currentHead);
        totalSeekTime +=  abs(head - currentHead);
        currentHead = head + 1;
        totalSeekTime += higherSeek(request, n, &currentHead);
    }

     cout << "\nTotal Seek Time = \t" << totalSeekTime <<  endl;
     cout << "---End of SCAN---" <<  endl;
}

void cscan(int request[], int n, int head) {
     cout << "\n---CSCAN Algorithm---" <<  endl;
     cout << "Head Position:\t" << head <<  endl;

    int currentHead = head;
    int totalSeekTime = 0;

    totalSeekTime += higherSeek(request, n, &currentHead);
    totalSeekTime +=  abs(DISK_SIZE - currentHead);

    currentHead = head;

    for (int currentIndex = 0; currentIndex <= currentHead; ++currentIndex) {
        for (int i = 0; i < n; i++) {
            if (currentIndex == request[i]) {
                totalSeekTime +=  abs(head - request[i]);
                head = request[i];
                 cout << "Request processed:\t" << head <<  endl;
            }
        }
    }

     cout << "Total Seek Time = " << totalSeekTime <<  endl;
     cout << "---End of CSCAN---" <<  endl;
}

void look(int request[], int n, int head, int direction) {
     cout << "\n---LOOK Algorithm---" <<  endl;
     cout << "Head Position\t" << head <<  endl;

    int currentHead;
    int totalSeekTime = 0;

    if (direction == 0) {
        currentHead = head;
        totalSeekTime += higherSeek(request, n, &currentHead);
        totalSeekTime += higherSeek(request, n, &currentHead);
        totalSeekTime +=  abs(currentHead - head);
        currentHead = head;
        totalSeekTime += lowerSeek(request, n, &currentHead);
    } else {
        currentHead = head;
        totalSeekTime += lowerSeek(request, n, &currentHead);
        totalSeekTime +=  abs(currentHead - head);
        currentHead = head + 1;
        totalSeekTime += higherSeek(request, n, &currentHead);
    }

     cout << "\nTotal Seek Time = " << totalSeekTime <<  endl;
     cout << "---End of LOOK---" <<  endl;
}

void clook(int request[], int n, int head) {
     cout << "\n---CLOOK Algorithm---" <<  endl;
     cout << "Head Position:\t" << head <<  endl;

    int currentHead = head;
    int totalSeekTime = 0;

    totalSeekTime += higherSeek(request, n, &currentHead);
    totalSeekTime +=  abs(DISK_SIZE - currentHead);

    currentHead = head;

    for (int currentIndex = 0; currentIndex <= currentHead; ++currentIndex) {
        for (int i = 0; i < n; i++) {
            if (currentIndex == request[i]) {
                totalSeekTime +=  abs(head - request[i]);
                head = request[i];
                 cout << "Request processed:\t" << head <<  endl;
            }
        }
    }

     cout << "Total Seek Time = " << totalSeekTime <<  endl;
     cout << "---End of CLOOK---" <<  endl;
}

int higherSeek(int request[], int n, int* pHead) {
    int totalSeekTime = 0;
    int currentIndex;
    int head = *pHead;

    for (currentIndex = head; currentIndex < DISK_SIZE; ++currentIndex) {
        for (int i = 0; i < n; ++i) {
            if (currentIndex == request[i] && request[i] > *pHead) {
                totalSeekTime +=  abs(request[i] - head);
                head = request[i];
                 cout << "Request processed:\t" << head <<  endl;
            }
        }
    }

    *pHead = head;
    return totalSeekTime;
}

int lowerSeek(int request[], int n, int* pHead) {
    int totalSeekTime = 0;
    int currentIndex;
    int head = *pHead;

    for (currentIndex = head; currentIndex >= 0; --currentIndex) {
        for (int i = 0; i < n; ++i) {
            if (currentIndex == request[i] && request[i] < *pHead) {
                totalSeekTime +=  abs(request[i] - head);
                head = request[i];
                 cout << "Request processed:\t" << head <<  endl;
            }
        }
    }

    *pHead = head;
    return totalSeekTime;
}
