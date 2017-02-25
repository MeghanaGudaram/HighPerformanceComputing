#include<stdio.h>
#include<omp.h>
#include<immintrin.h>
#include<iostream>
#include<chrono>
#include<ctime>

using namespace std;
using namespace std::chrono;

__m256 avx_memoryRead(float* array, int size) 
{
  __m256 sum = _mm256_set1_ps(0);
  
  for (int i = 0; i < size ; i=i+8)
  {
        sum= _mm256_add_ps(_mm256_loadu_ps(&array[i]),sum); // Adding elements to sum, impying read from memory
  }
        sum=_mm256_hadd_ps(sum,sum); // Horizonatal addition of vector values i.e. vect1=vect0+vect0
        sum=_mm256_hadd_ps(sum,sum); // Horizonatal addition of vector values i.e. vect2 =vect1+vect1
        sum=_mm256_hadd_ps(sum,sum); // Horizonatal addition of vector values i.e. vect3=vect2+vect2

return sum;
}

int main()
{

  #pragma omp parallel
  {
    int size=262144; // 256KB is taken as size
    float *array;
    int status=posix_memalign((void**) &array, 32 , size*sizeof(float)); // Allocating memory
    for(int j=0;j<size;j++) // Initialize array to 1
    array[j]=1;
    double bw=0;
    __m256 val= _mm256_set1_ps(0);
  
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    for(int i=0;i<100;i++)
    {
       val=avx_memoryRead(array,size); // function call to make sure loops are not optimized
    }
       high_resolution_clock::time_point t2 = high_resolution_clock::now();
       duration<double> time_span = duration_cast<duration<double>> (t2 - t1);
       bw = (size*4*100)/(1000000000 * time_span.count()); // Bandwidth is size in bytes / time in seconds i.e. scaled to GB/s
       printf(" Time taken for 100 operations of %d bytes : %lf BW = %lf GB/s\n", size*4, time_span.count(), bw);
       printf("value %f\n",val[0]);

  }

return 0;
}
  
