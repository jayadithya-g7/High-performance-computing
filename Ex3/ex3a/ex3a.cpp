 #include <iostream>
 #include <omp.h>
 using namespace std;
 int main(){
 #pragma omp parallel
 {
 int threadid=omp_get_thread_num();
 int totalthreads=omp_get_num_threads();
 printf("Hello  Threadid:%d num_threads:%d\n",threadid,totalthreads);
 }
 #pragma omp parallel
 {
 int threadid=omp_get_thread_num();
 int totalthreads=omp_get_num_threads();
 cout<<"Hello  Threadid:"<<threadid <<"num_threads:"<<totalthreads<<endl;
 }
return 0;
 }
