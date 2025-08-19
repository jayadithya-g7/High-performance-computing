#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

const int MAXN=100000;
int cutoff=10;

void insertionSort(vector<int>& arr,int left,int right) {
    for (int i=left+1;i<=right;i++) {
        int key=arr[i];
        int j=i-1;
        while(j>=left && arr[j]>key) {
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
}

void merge(vector<int>& arr,int left,int mid,int right) {
    int n1=mid-left+1;
    int n2=right-mid;

    vector<int> L(n1),R(n2);
    for(int i=0;i<n1;i++){ 
    L[i]=arr[left+i];
    }
    for(int j=0;j<n2;j++){ 
    R[j]=arr[mid+1+j];
    }

    int i=0,j=0,k=left;
    while(i<n1 && j<n2){
        if(L[i]<=R[j]){
         arr[k++]=L[i++];
         }
        else{
         arr[k++]=R[j++];
         }
    }
    while(i<n1){ 
    arr[k++]=L[i++];
    }
    while(j<n2){
     arr[k++]=R[j++];
     }
}

void mergeSort(vector<int>& arr,int left,int right) {
    if(right-left+1<=cutoff){
        insertionSort(arr,left,right);
        return;
    }
    if(left<right){
        int mid=left+(right-left)/2;
        mergeSort(arr,left,mid);
        mergeSort(arr,mid+1,right);
        merge(arr,left,mid,right);
    }
}

void generateRandomArray(vector<int>& arr,int n) {
    arr.clear();
    arr.resize(n);
    for(int i=0;i<n;i++){
        arr[i]=rand()%100000;
    }
}

int main(){
    srand(time(0));
    int n=50000;
    vector<int> arr,temp;

    int cutoffs[]={0,5,10,20,50,100};

    for (int i=0;i<6;i++) {
        cutoff=cutoffs[i];
        generateRandomArray(arr,n);
        temp=arr;

        auto start=high_resolution_clock::now();
        mergeSort(arr,0,n-1);
        auto stop=high_resolution_clock::now();

        auto duration=duration_cast<milliseconds>(stop-start);
        cout<<"cutoff = "<<cutoff<<",time: "<<duration.count()<<"ms"<<endl;
    }

    return 0;
}  
