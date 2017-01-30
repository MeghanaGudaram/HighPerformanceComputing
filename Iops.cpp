#include <stdio.h>
#include <omp.h>
#include <immintrin.h>
#include <iostream>
#include<chrono>
#include<ctime>

__m256i iop()
  {
    __m256i x = _mm256_set_epi16 (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    __m256i y = _mm256_set_epi16 (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,16);
    __m256i z;
   for (long long i=0; i< 10000000; ++i)
    {
      z = _mm256_adds_epu16(x,y);
    }
   return z;
  }

int main ()
{
  using namespace std::chrono;

  #pragma omp parallel
  {
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    __m256i a=iop();

    high_resolution_clock::time_point t2 = high_resolution_clock::now();

   duration<double> time_span = duration_cast<duration<double>> (t2 - t1);
   std::cout << "Time taken for 10^7 operations : " << time_span.count()*1000000 << " useconds.";
   std::cout<<std::endl;
  }

 return 0;
}

