#include <iostream>
#include <random>
#include <chrono>
#include <omp.h>
double monte_carlo_serial(long long num_points) {
 std::mt19937_64 rng(42);
 std::uniform_real_distribution<double> dist(0.0, 1.0);
 long long inside_circle=0;
 long long i=0;
 while(i<num_points){
 double x=dist(rng);
 double y=dist(rng);
 if(x*x+y*y<=1.0)
 inside_circle++;
 i++;
 }
 return 4.0*inside_circle/num_points;
}
double monte_carlo_parallel(long long num_points, int num_threads) {
 long long inside_circle = 0;
 #pragma omp parallel num_threads(num_threads)
 {
 std::mt19937_64 rng(42 + omp_get_thread_num());
 std::uniform_real_distribution<double> dist(0.0, 1.0);
 long long local_count=0;
 #pragma omp for
 for (long long i=0;i<num_points;i++) {
 double x=dist(rng);
 double y=dist(rng);
 if (x*x+y*y<=1.0)
 local_count++;
 }
 #pragma omp atomic
 inside_circle+=local_count;
 }
 return 4.0*inside_circle/num_points;
}
int main(){
 long long num_points=1e8;
 int num_threads=4;
 std::cout<<"Estimating pi using "<<num_points<<" points\n";
 std::cout<<"Using "<<num_threads<<" threads for parallel version\n\n";
 auto start_serial=std::chrono::high_resolution_clock::now();
 double pi_serial=monte_carlo_serial(num_points);
 auto end_serial=std::chrono::high_resolution_clock::now();
 std::chrono::duration<double> time_serial=end_serial-start_serial;
 std::cout<<"Serial pi ≈ "<<pi_serial<<"\n";
 std::cout<<"Serial Time: "<<time_serial.count()<<" seconds\n\n";

 auto start_parallel=std::chrono::high_resolution_clock::now();
 double pi_parallel=monte_carlo_parallel(num_points, num_threads);
 auto end_parallel=std::chrono::high_resolution_clock::now();
 std::chrono::duration<double> time_parallel=end_parallel-start_parallel;
 std::cout<<"Parallel pi ≈ "<<pi_parallel<<"\n";
 std::cout<<"Parallel Time: "<<time_parallel.count()<<" seconds\n";

 double speedup=time_serial.count()/time_parallel.count();
 std::cout<<"\nSpeedup: "<<speedup<<"×\n";
 return 0;
}