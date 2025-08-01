 #include <iostream>
 #include <omp.h>
 #include <unistd.h>
 using namespace std;
 int main(){
 #pragma omp parallel
 {
 int threadid=omp_get_thread_num();
 int totalthreads=omp_get_num_threads();
 sleep(totalthreads-threadid);
 printf("Hello Threadid:%d num_threads:%d\n",threadid,totalthreads);
 }
 return 0;
 }
