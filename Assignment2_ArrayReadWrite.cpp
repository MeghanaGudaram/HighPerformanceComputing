#include<stdio.h>
#include <omp.h>
#include <immintrin.h>
#include <iostream>
#include<chrono>
#include<ctime>

using namespace std;
using namespace std::chrono;

__m256 avx_memoryRead(float* array, int size) 
{
	__m256 sum = _mm256_set1_ps(0);
	for (int i = 0; i < size ; i=i+8)
    	{
		__m256 vect = _mm256_load_ps(&array[i]); // load and store implies read and write operations
        	_mm256_store_ps((float*)&vect,sum);
    	}

return sum;
}
int main()
{
#pragma omp parallel
	{
		int size=1000; // Size is 4000 bytes and not 4KB
		float *array=(float*)malloc(sizeof(float) * size);
		for(int j=0;j<size;j++)
			array[j]=1;
		__m256 val= _mm256_set1_ps(0);

		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		for(int i=0;i<100;i++)
    		{
			val=avx_memoryRead(array,size);
    		}
    		high_resolution_clock::time_point t2 = high_resolution_clock::now();
    		duration<double> time_span = duration_cast<duration<double>> (t2 - t1);
		printf(" Time taken for 100 operations of %d bytes : %lf BW = %lf GB/s\n",size*4,time_span.count(), (size*4*100)/(1000000000 * time_span.count()));
    		printf("value %f\n",val[0]);

	}
    return 0;
}
