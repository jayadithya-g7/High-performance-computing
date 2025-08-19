#include <iostream>
#include <omp.h>
int main() {
 int shared_var=10;
 int private_var=20;
 int firstprivate_var=30;
 int lastprivate_var=40;
 std::cout<<"Before parallel region:"<<std::endl;
 std::cout<<"shared_var = "<<shared_var<<std::endl;
 std::cout<<"private_var = "<<private_var<<std::endl;
 std::cout<<"firstprivate_var = "<<firstprivate_var<<std::endl;
 std::cout<<"lastprivate_var = "<<lastprivate_var<<std::endl;
 #pragma omp parallel for \
 shared(shared_var) \
 private(private_var) \
 firstprivate(firstprivate_var) \
 lastprivate(lastprivate_var)
 for(int i=0;i<omp_get_max_threads();i++){
 int default_var=100;

 shared_var+=i;
 private_var+=i;
 firstprivate_var+=i;
 lastprivate_var=i;
 default_var+=i;
 #pragma omp critical
 {
 std::cout<<"Thread "<<omp_get_thread_num()<<": "
 <<"shared_var = "<<shared_var<<", "
 <<"private_var = "<<private_var<<", "
 <<"firstprivate_var = "<<firstprivate_var<<", "
 <<"lastprivate_var = "<<lastprivate_var<<", "
 <<"default_var = "<<default_var<<std::endl;
 }
 }
 std::cout << "\nAfter parallel region:" << std::endl;
 std::cout << "shared_var = " << shared_var << std::endl;
 std::cout << "private_var = " << private_var << " (unchanged in master thread)" << std::endl;
 std::cout << "firstprivate_var = " << firstprivate_var << " (unchanged in master thread)" <<
std::endl;
 std::cout << "lastprivate_var = " << lastprivate_var << " (value from last iteration/thread)" <<
std::endl;
 return 0;
}