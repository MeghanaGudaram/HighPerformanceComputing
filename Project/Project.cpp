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
        if(argc < 3)
        {
                printf("Pattern is: \nboundary.txt res_bw.txt file.txt\n");
                return 0;
        }
        FILE *fin1, *fin2, *fin3;
        fin1=fopen(argv[1],"r");
        fin2=fopen(argv[2],"r");
        fin3=fopen(argv[3],"r");
        long int i=0;
        float hsx, hsy, X, Y, lowbx, lowby, highbx, highby, resx, resy;
        int ht, T, lowbt, highbt, rest; //low res low bw
        fscanf(fin1,"%f %f %d %f %f %d",&lowbx, &highbx, &lowby, &highby, &lowbt, &highbt);
        fscanf(fin2,"%f %f %d %f %f %d",&resx, &resy, &rest, &hsx, &hsy, &ht)
        while(fscanf(fin3,"%f %f %d",&Xval[i], &Yval[i], &Tval[i])==3)
        {
                i++;
        }

        for(int k=0; k<i; k++)
        {
                for(X=lowbx, Y=lowby, T=lowbt;();X+=resx, Y+=resy, T+=rest)
                {
                        Fval[k]=ks((X-Xval[k])/hs, (Y-Yval[k])/hs)*kw((T-Tval[k])/ht);
                }
        }
        return 0;
}
