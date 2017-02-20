#include<stdio.h>
#include<iostream>
#include <omp.h>
#include <immintrin.h>
#include <iostream>
#include<chrono>
#include<ctime>

using namespace std;
using namespace std::chrono;

main()
{
	#pragma omp parallel
	{
		int size=100000;
		int *randa = (int*)malloc(sizeof(int) * size);
		int *randb = (int*)malloc(sizeof(int) * size);
		int *next = (int*)malloc(sizeof(int) * size);
		int i=0,rnd,current=0;

		for(int j=0;j<size;j++)
		{
			randa[j]=0;
			randb[j]=0;
			next[j]=0;
		}

		while(i<size)
		{
			rnd=rand() %size;
			if(randa[rnd]==0)
			{
				randb[i++]=rnd;
				randa[rnd]=1;
			}
		}

		for(int j=0;j<size;j++)
		{
			next[j]=j+1;
		}
	
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		while(current < size)
		{
			current=next[current++];
		}
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		duration<double> time_span = duration_cast<duration<double>> (t2 - t1);
		printf("time taken is %lf \n",time_span.count());


		high_resolution_clock::time_point t3 = high_resolution_clock::now();
		current=0;
		for( int k=0;k<size;k++)
		{
			current=randb[current];
		}
		high_resolution_clock::time_point t4 = high_resolution_clock::now();
		duration<double> time_span1 = duration_cast<duration<double>> (t4 - t3);
		printf("time taken in random is %lf \n",time_span1.count());

	}
}
