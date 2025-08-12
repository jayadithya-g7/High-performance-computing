#include <iostream>
#include <fstream>
#include <string>
#include <omp.h>
#include <chrono>

using namespace std;

void encrypt(string& text,int shift,int num_threads) {
    int length=text.length();

    #pragma omp parallel for num_threads(num_threads)
    for(int i=0;i<length;++i){
        if(isalpha(text[i])) {
            char base=isupper(text[i])?'A':'a';
            text[i]=(text[i]-base+shift)%26+base;
        }
    }
}

void decrypt(string& text,int shift,int num_threads) {
    encrypt(text,26-shift,num_threads);  // decryption is just reverse shift
}

string generateText(int size){
    string result;
    result.reserve(size);
    for (int i=0;i<size;++i) {
        result+='A'+(rand()%26);
    }
    return result;
}

int main(){
  

    int text_size;
    int shift=3;
    int threadnum;
    
    cout<<"enter textsize:";
    cin>>text_size;
    string text=generateText(text_size);

   cout<<"enter number of threads:";
   cin>>threadnum;

    auto start=std::chrono::high_resolution_clock::now();

    
    encrypt(text,shift,threadnum);
    
    decrypt(text,shift,threadnum);
    

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dur=end-start;

    std::cout<<"Time taken for encryption and decryption :"<<dur.count()<<" seconds using "<<threadnum<<" threads\n";

    return 0;
}
