#include <iostream>
#include <vector>
#include <limits>
#include <sstream>

using namespace std;

// FIFO (First-In, First-Out) Page Replacement Algorithm
int fifo(vector<int>& reference, int frames) {
    vector<int> frame(frames, -1);
    int page_faults = 0;
    int index = 0;

    for (int i = 0; i < reference.size(); i++) {
        int page = reference[i];
        int is_fault = 1;

        for (int j = 0; j < frames; j++) {
            if (frame[j] == page) {
                is_fault = 0;
                break;
            }
        }

        if (is_fault) {
            page_faults++;
            frame[index] = page;
            index = (index + 1) % frames;
        }
    }

    return page_faults;
}

// LRU (Least Recently Used) Page Replacement Algorithm
int lru(vector<int>& reference, int frames) {
    vector<int> frame(frames, -1);
    vector<int> counter(frames, 0);
    int page_faults = 0;

    for (int i = 0; i < reference.size(); i++) {
        int page = reference[i];
        int is_fault = 1;

        for (int j = 0; j < frames; j++) {
            if (frame[j] == page) {
                is_fault = 0;
                counter[j] = i;
                break;
            }
        }

        if (is_fault) {
            page_faults++;
            int min_count = counter[0], replace = 0;

            for (int j = 1; j < frames; j++) {
                if (counter[j] < min_count) {
                    min_count = counter[j];
                    replace = j;
                }
            }

            frame[replace] = page;
            counter[replace] = i;
        }
    }

    return page_faults;
}

// Optimal Page Replacement Algorithm
int optimal(vector<int>& reference, int frames) {
    vector<int> frame(frames, -1);
    int page_faults = 0;

    for (int i = 0; i < reference.size(); i++) {
        int page = reference[i];
        int is_fault = 1;

        for (int j = 0; j < frames; j++) {
            if (frame[j] == page) {
                is_fault = 0;
                break;
            }
        }

        if (is_fault) {
            page_faults++;
            int replace = -1;

            for (int j = 0; j < frames; j++) {
                int k;

                for (k = i + 1; k < reference.size(); k++) {
                    if (reference[k] == frame[j]) {
                        if (k > replace)
                            replace = k;
                        break;
                    }
                }

                if (k == reference.size()) {
                    replace = j;
                    break;
                }
            }

            frame[replace] = page;
        }
    }

    return page_faults;
}

int main() {
    int frames, pages;
    
    cout << "Enter the number of frames: ";
    cin >> frames;
    cout << "Enter the number of pages: ";
    cin >> pages;

    cin.ignore(); // Consume the newline character.

    vector<int> reference;

    cout << "Enter the reference string (space-separated): ";
    string input;
    getline(cin, input);
    istringstream iss(input);
    int page;

    while (iss >> page) {
        reference.push_back(page);
    }

    int fifo_faults = fifo(reference, frames);
    int lru_faults = lru(reference, frames);
    int optimal_faults = optimal(reference, frames);

    cout << "Total page faults using FIFO: " << fifo_faults << endl;
    cout << "Total page faults using LRU: " << lru_faults << endl;
    cout << "Total page faults using Optimal: " << optimal_faults << endl;

    return 0;
}
