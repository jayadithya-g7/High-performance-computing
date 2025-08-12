#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <omp.h>


using namespace std;


string readFile(const string& filename) {
    ifstream file(filename,ios::binary);
    
    
    return string((istreambuf_iterator<char>(file)),
                       istreambuf_iterator<char>());
}

void frequencyCritical(const string& data,vector<int>& histogram,int num_threads) {
    #pragma omp parallel for num_threads(num_threads)
    for (int i=0;i<data.size();++i) {
        unsigned char ch=data[i];
        #pragma omp critical
        {
            histogram[ch]++;
        }
    }
}


void frequencyReduction(const string& data,vector<int>& histogram,int num_threads) {
    vector<vector<int>> local_hist(num_threads,vector<int>(256,0));
    
    #pragma omp parallel num_threads(num_threads)
    {
        int tid=omp_get_thread_num();
        #pragma omp for
        for (int i=0;i<data.size();++i) {
            unsigned char ch=data[i];
            local_hist[tid][ch]++;
        }
    }

   
    for(int t=0;t<num_threads;++t)
        for(int i=0;i<256;++i)
            histogram[i]+=local_hist[t][i];
}

int main() {
    

    
    
    int num_threads;
    cout<<"enter no of threads:";
    cin>>num_threads;
    
    string data=readFile("random_data_file_1048576.bin");
    std::vector<int> histogram1(256,0);
    std::vector<int> histogram2(256,0);

    auto start = std::chrono::high_resolution_clock::now();

    
        frequencyCritical(data,histogram1,num_threads);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time = end - start;
 
    std::cout<<"Time for critical  with "<<num_threads<<" threads: " << time.count()<<" seconds\n";

 
 
start = std::chrono::high_resolution_clock::now();
        frequencyReduction(data,histogram2,num_threads);
    end = std::chrono::high_resolution_clock::now();
time = end - start;
    
   
    std::cout<<"Time for reduction  with "<<num_threads<<" threads: " << time.count()<<" seconds\n";

    return 0;
}
