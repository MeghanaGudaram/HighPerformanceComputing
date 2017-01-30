#include <stdio.h>
#include <omp.h>
#include <immintrin.h>
#include <iostream>
#include<chrono>
#include<ctime>

__m256 iop()
  {
    __m256 x = _mm256_setr_ps (1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2);
    __m256 y = _mm256_setr_ps (10.1, 20.1, 30.1, 40.1, 50.1, 60.1, 70.1, 80.1);
    __m256 z = _mm256_setr_ps (1.1, 2.1, 3.1, 4.1, 5.1, 6.1, 7.1, 8.1);
   for (long long i=0; i< 10000000; ++i)
    {
      z = _mm256_addsub_ps(x,y);
    }
   return z;
  }

int main ()
{
  using namespace std::chrono;
#pragma omp parallel
  {
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    __m256 a=iop();

    high_resolution_clock::time_point t2 = high_resolution_clock::now();

   duration<double> time_span = duration_cast<duration<double>> (t2 - t1);
   std::cout << "Time taken for 10^7 operations : " << time_span.count()*1000000 << " useconds.";
   std::cout<<std::endl;
  }

 return 0;
}

