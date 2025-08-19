#include<iostream>
#include<ctime>
#include<cstdlib>
#include<omp.h>

using namespace std;

const int MAXN=1000;
int image[MAXN][MAXN];
int backup[MAXN][MAXN];

void generateImage(int n){

  for(int i=0;i<n;i++){ 
    for(int j=0;j<n;j++){
    image[i][j]=rand()%2;
   }
 }
 
}

void copyImage(int src[MAXN][MAXN],int dest[MAXN][MAXN],int n){
for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
       dest[i][j]=src[i][j];
   }
  }
}

void floodFill(int x,int y,int targetColor,int replacementColor){
   if(x<0||x>=MAXN||y<0||y>=MAXN){
     return;
}
    if(image[x][y]!=targetColor){
   return;
  }
image[x][y]=replacementColor;
floodFill(x+1,y,targetColor,replacementColor);
floodFill(x-1,y,targetColor,replacementColor);
floodFill(x,y+1,targetColor,replacementColor);
floodFill(x,y-1,targetColor,replacementColor);

}

void parallelFloodFill(int x,int y,int targetColor,int replacementColor){
#pragma omp parallel
{
#pragma omp single
{
floodFill(x,y,targetColor,replacementColor);
}
}
}

int main(){
int sizes[]={100,200,300,400,500};

for(int k=0;k<5;k++){
  int n=sizes[k];

   generateImage(n);

  copyImage(image,backup,n);
  
  double start=omp_get_wtime();
  
  floodFill(0,0,image[0][0],3);
  
  double stop=omp_get_wtime();
  
  cout<<"serial n="<<n<<",time:"<<stop-start<<"s"<<endl;
  
  copyImage(backup,image,n);
  
  start=omp_get_wtime();
  
  parallelFloodFill(0,0,image[0][0],3);
  
  stop=omp_get_wtime();
  cout<<"parallel n="<<n<<",time:"<<stop-start<<"s"<<endl;
}
return 0;
}
