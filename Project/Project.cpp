#include<stdio.h>
#include<stdint.h>
#include<malloc.h>
#include<stdlib.h>
#include<math.h>

float *Xval=(float *) malloc(2000*sizeof(float));
float *Yval=(float *) malloc(2000*sizeof(float));
int *Tval=(int *) malloc(2000*sizeof(int));
float *Fval=(float *) malloc(2000*sizeof(float));

float ks(float u, float v)
{
        return ((3.14/2)*(1-u)*(1-u)*(1-v)*(1-v));
}

float kt(float w)
{
        return (0.75 * (1-w) * (1-w));
}

float euclDist(float x, float x1, float y, float y1)
{
        return (sqrt((x-x1)*(x-x1) + (y-y1) * (y-y1)));
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
        float hsx, hsy, X, Y, lowbx, lowby, highbx, highby, resx, resy, nhsht;
        int ht, T, lowbt, highbt, rest; //low res low bw
        
        fscanf(fin1,"%f, %f, %f, %f, %d, %d",&lowbx, &highbx, &lowby, &highby, &lowbt, &highbt);
        fscanf(fin2,"%f, %f, %d, %f, %f, %d",&resx, &resy, &rest, &hsx, &hsy, &ht);
        while(fscanf(fin3,"%f %f %d",&Xval[i], &Yval[i], &Tval[i])==3)
        {
                i++;
        }
        //printf("%f %f %f %f %d %d\n",lowbx, highbx, lowby, highby, lowbt, highbt);
        //printf("%f, %f, %d, %f, %f, %d\n",resx, resy, rest, hsx, hsy, ht);
        //printf();
		//fcloseall();
		nhsht = hsx * hsy * ht;
        for(int k=0; k<i; k++)
        {
			int n=0;
			for(X=lowbx; X < highbx; X+=resx)
			{
				for(Y=lowby; Y < highby; Y+=resy)
				{
					for(T=lowbt; T < highbt; T+=rest)
					{
						//printf("Xval[k]-X=%f Yval[k]-Y=%f..Tval[k]-T=%d \n",Xval[k]-X, Yval[k]-Y, Tval[k]-T );
						if((euclDist(Xval[k], X, Yval[k], Y) < hsx) && fabs(Tval[k]-T) < ht)
						{
							//printf("Hi..\n");
							Fval[k]=Fval[k]+ks((X-Xval[k])/hsx, (Y-Yval[k])/hsy)*kt((T-Tval[k])/ht);
						}
						n++;
					}		
				}
			}
			printf("%d\n", n);
			Fval[k] = Fval[k]/(n*nhsht);
        }

        for(int j=0; j < i; j++)
        printf("Fval[%d]=%f\n",j, Fval[j]);
        return 0;
}

