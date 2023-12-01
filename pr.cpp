#include<iostream>
#include<vector>
#include<limits>
#include<sstream>
using namespace std;

int fifo(vector<int>& reference, int frames){
    vector<int> frame(frames, -1);
    int pagefault=0;
    int index=0;

    for(int i=0; i<reference.size(); i++){
        int page=reference[i];
        int is_fault=1;

        for(int j=0; j<frames; j++){
            if(frame[j]==page){
                is_fault=0;
                break;
            }
        }

        if(is_fault){
            pagefault++;
            frame[index]=page;
            index=(index+1)%frames;
        }

    }

    return pagefault;
}

int lru(vector<int>& reference, int frames){
    vector<int> frame(frames, -1);
    vector<int> counter(frames, 0);
    int pagefault=0;

    for(int i=0; i<reference.size(); i++){
        int page=reference[i];
        int is_fault=1;

        for(int j=0; j<frames; j++){
            if(frame[j]==page){
                is_fault=0;
                counter[j]=i;
                break;
            }
        }

        if(is_fault){
            pagefault++;
            int min_count=counter[0], replace=0;

            for(int j=1; j<frames; j++){
                if(counter[j]<min_count){
                    min_count=counter[j];
                    replace=j;
                }
            }
            frame[replace]=page;
            counter[replace]=1;
        }
    }

    return pagefault;

}

int optimal(vector<int> reference, int frames){
    vector<int> frame(frames, -1);
    int page_fault=0;

    for(int i=0; i<reference.size(); i++){
        int page=reference[i];
        int is_fault=1;

        for(int j=0; j<reference.size(); i++){
            if(frame[j]==page){
                is_fault=0;
                break;
            }
        }

        if(is_fault){
            page_fault++;
            int replace=-1;

            for(int j=0; j<frames; j++){
                int k;

                for(k=i+1; k<reference.size(); k++){
                    if(reference[k]==frame[j]){
                        if(reference[k]==frame[j]){
                            if(k>replace){
                                replace=k;
                                break;
                            }
                        }
                    }
                }

                if(k==reference.size()){
                    replace=j;
                    break;
                }
            }

            frame[replace]==page;
        }
    }
    return page_fault;
}


int main(){
    int frames, pages;
    cout<<"enter frames : \n";
    cin>>frames;
    cout<<"enter pages : \n";
    cin>>pages;

    vector<int> reference;

    string input;
    cout<<"enter reference : \n";
    cin>>input;

    for(int i=0; i<input.size(); i++){
        reference.push_back(input[i]);
    }

    int fifo_faults=fifo(reference, frames);
    int lru_faults=lru(reference, frames);
    int optimal_faults=optimal(reference, frames);

    cout<<"Total faults using FIFO : "<<fifo_faults<<endl;
    cout<<"Total faults using LRU : "<<lru_faults<<endl;
    cout<<"Total faults using Optimal : "<<optimal_faults<<endl;


    return 0;
}