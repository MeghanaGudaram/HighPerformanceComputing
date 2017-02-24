#include<stdio.h>
#include<omp.h>
#include<immintrin.h>
#include<iostream>
#include<chrono>
#include<ctime>

using namespace std;
using namespace std::chrono;

__m256 avx_memoryWrite(float* array, int size) 
{
    __m256 sum = _mm256_set_ps(0,0,0,0,0,0,0,0);

    for (int i = 0; i < size; i=i+8)
    {
	_mm256_store_ps(&array[i],sum); // strore a value implies writing into memory
    }

    return sum;
}
int main()
{
#pragma omp parallel
{

    static int size=1000000; // size of 4000000 bytes and not 40MB
    float *array=(float*)malloc(sizeof(float) * size);
    for(int j=0;j<size;j++)
    array[j]=1;
    float bw=0;
    __m256 val= _mm256_set1_ps(0);

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    for(int i=0;i<100;i++)
    {
		val=avx_memoryWrite(array,size); // function call to make sure code is not optimized
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>> (t2 - t1);

    bw = (size*4*100)/(1000000000 * time_span.count());
    printf(" Time taken for 100 operations of %d bytes : %lf BW = %lf GB/s\n",size*4,time_span.count(), bw);
    printf("value %f\n",val[0]);

}

    return 0;
}
