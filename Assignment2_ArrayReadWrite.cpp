#include<iostream>
#include <omp.h>
#include <immintrin.h>
#include <iostream>
#include<chrono>
#include<ctime>

using namespace std;
using namespace std::chrono;

__m256 avx_memoryRead(float* array, int size) 
{
	int j=0;
	__m256 sum = _mm256_set1_ps(0);

	for (int i = 0; i < (size * sizeof(int)) / sizeof(__m256i); i++)
    {
		__m256 vect = _mm256_loadu_ps(&array[i]);
        _mm256_store_ps((float*)&vect,sum);
    }

return sum;
}
int main()
{
#pragma omp parallel
{
	int size=50000000;
    float *array=(float*)malloc(sizeof(float) * size);
    for(int j=0;j<size;j++)
		array[j]=1;
    long bw=0;
    __m256 val= _mm256_set1_ps(0);

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    for(int i=0;i<100;i++)
    {
		val=avx_memoryRead(array,size);
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>> (t2 - t1);
    bw = (size*4*100)/(1000000000 * time_span.count());
	printf(" Time taken for 100 operations of %d bytes : %lf BW = %lf GB/s\n",size*4,time_span.count(), bw);
    printf("value %f\n",val[0]);

}
    return 0;
}
