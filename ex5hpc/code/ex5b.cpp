#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>
#include <cassert>
void prefix_sum_serial(const std::vector<int>& input, std::vector<int>& output) {
 output[0]=input[0];
 for (size_t i=1;i<input.size();i++) {
 output[i]=output[i-1]+input[i];
 }

}
void prefix_sum_parallel(const std::vector<int>& input, std::vector<int>& output) {
 int n=input.size();
 int num_threads=1;
 #pragma omp parallel
 {
 #pragma omp single
 num_threads=omp_get_num_threads();
 }
 std::vector<int> partial_sums(num_threads+1,0);
 #pragma omp parallel
 {
 int tid=omp_get_thread_num();
 int chunk_size=(n+num_threads-1)/num_threads;
 int start=tid*chunk_size;
 int end=std::min(start+chunk_size,n);
 if(start<n){
 output[start]=input[start];

 for (int i=start+1;i<end;i++) {
 output[i]=output[i-1]+input[i];
 }
 partial_sums[tid+1]=output[end-1]; // store sum of this chunk
 }
 }

 for (int i=1;i<num_threads+1;i++){
 partial_sums[i]+=partial_sums[i - 1];
 }

 #pragma omp parallel
 {
 int tid=omp_get_thread_num();
 int chunk_size=(n+num_threads-1)/num_threads;
 int start=tid*chunk_size;
 int end=std::min(start+chunk_size,n);
 if(tid>0&&start<n){
 int add_value=partial_sums[tid];
 for(int i=start;i<end;i++){
 output[i]+=add_value;
 }
 }
 }
}
int main() {
 std::vector<int> sizes={10,100,1000,10000,100000,1000000};
 for (int n : sizes){
 std::vector<int> input(n);
 std::vector<int> output_serial(n);
 std::vector<int> output_parallel(n);

 for (int i=0;i<n;i++) {
 input[i] = i+1;
 }

 auto start_serial=std::chrono::high_resolution_clock::now();
 prefix_sum_serial(input, output_serial);
 auto end_serial=std::chrono::high_resolution_clock::now();

 auto start_parallel=std::chrono::high_resolution_clock::now();
 prefix_sum_parallel(input, output_parallel);
 auto end_parallel=std::chrono::high_resolution_clock::now();

 bool correct=true;
 for (int i=0;i<n;i++) {
 if(output_serial[i]!=output_parallel[i]) {
 correct=false;
 break;
 }
 }
 auto serial_time=std::chrono::duration<double, std::milli>(end_serial - start_serial).count();
 auto parallel_time=std::chrono::duration<double, std::milli>(end_parallel -
start_parallel).count();
 std::cout<<"Array size: "<<n<<"\n";
 std::cout<<"Serial time: "<<serial_time<<" ms\n";
 std::cout<<"Parallel time: "<<parallel_time<<" ms\n";
 std::cout<<"Results match? "<<(correct ? "Yes" : "No")<<"\n\n";
 }
 return 0;
}
