#include<stdio.h>
#include<stdint.h>
#include<malloc.h>
#include<stdlib.h>
#include<math.h>

float *Xval=(float *) malloc(2000*sizeof(float));
float *Yval=(float *) malloc(2000*sizeof(float));
int *Tval=(int *) malloc(2000*sizeof(int));
int *Fval=(int *) malloc(2000*sizeof(int));

float ks(float u, float v)
{
        return ((3.14/2)*(1-u)*(1-u)*(1-v)*(1-v));
}

float kt(float w)
{
        return (0.75 * (1-w) * (1-w));
}

int main(int argc, char *argv[])
{
        FILE *fin;
        fin=fopen(argv[1],"r");
        long int i=0;
        float hs=1.0, xi=1.0, yi=1.0;
        int ht=7, ti=7; //low res low bw

        while(fscanf(fin,"%f %f %d",&Xval[i], &Yval[i], &Tval[i])==3)
        {
                i++;
        }

        for(int k=0; k<i; k++)
        {
                Fval[k]=ks((Xval[k]-xi)/hs, (Yval[k]-yi)/hs)*kw((Tval[k]-ti)/ht);
        }
        return 0;
}
