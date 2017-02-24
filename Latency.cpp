#include<stdio.h>
#include <iostream>
#include<chrono>
#include<ctime>

using namespace std;
using namespace std::chrono;

int main()
{
        int size=52428800,rnd=0,i=0,current=0; // data size taken 200MB
        int *randa=(int*)malloc(sizeof(int) * size); // Array considered to fill random values in randb
        int *randb=(int*)malloc(sizeof(int) * size); // Array of unique random values
        int *next=(int*)malloc(sizeof(int) * size); // Array considered to traverse linearly
        int resize=size; // resize the length of randa
        for(int j=0;j<size;j++) // Array initialization
        {
                randa[j]=j;
                randb[j]=0; // so that when *last reaches randa[0], remaining randb is 0
                next[j]=j;
        }
        int *last=&randa[size-1]; // pointer to the last element of randa

        while(*last!=0) // until pointer becomes randa[0]
        {
                rnd = rand()%resize--; // random variable according to resize of randa[]
                randb[i++]=randa[rnd]; // assign randb with random value
                randa[rnd]=*last--; // swap the last element of array with randa[rnd], also shift pointer from last element to last element-1
}

        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        for(int k=0;k<size;k++)
        {
                current=next[current]; // traversing linearly
        }
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double>> (t2 - t1);
        printf("Time taken for linear is %lf \n",time_span.count());

        current=0;
        high_resolution_clock::time_point t3 = high_resolution_clock::now();
        for(int k=0;k<size;k++)
        {
                current=randb[current]; // traversing randomly
        }
        high_resolution_clock::time_point t4 = high_resolution_clock::now();

        duration<double> time_span1 = duration_cast<duration<double>> (t4 - t3);
        printf("Time taken for random is %lf \n",time_span1.count());
return 0;
}
