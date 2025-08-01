 #include <iostream>
 #include <chrono>
 #include <omp.h>
 #include <random>
 using namespace std;
 int dotproduct(int *arr1,int *arr2,int n,int threadcount){
 int result=0;
 omp_set_num_threads(threadcount);
 #pragma omp parallel for reduction(+:result)
 for(int i=0;i<n;i++){
 result+=*(arr1+i) * *(arr2+i);
 }
  return result;
}
 int main()
 {
 std::random_device rd;
 std::mt19937 gen(rd());
 std::uniform_int_distribution<> distrib(1, 100);
 int n;
 cout<<"enter n:";
 cin>>n;
 int arr1[n];
 int arr2[n];
 int threads[]={4,5,6};
 for(int i=0;i<n;i++){
 arr1[i]=distrib(gen);
 arr2[i]=distrib(gen);
 }
 for(int i=0;i<3;i++){
 auto start = std::chrono::high_resolution_clock::now();
 int dot=dotproduct(&arr1[0],&arr2[0],n,threads[i]);
 auto end = std::chrono::high_resolution_clock::now();
 std::chrono::duration<double, std::milli> duration = end - start;
     cout<<"dot product:"<<dot<<" threadcount:"<<threads[i]<<endl;
     cout<<"time(ms):"<<duration.count()<<endl;
   }
return 0;
}
