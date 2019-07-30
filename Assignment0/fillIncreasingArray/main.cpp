#include <iostream>
#define NMAX 999
#include "Profiler.h"
using namespace std;
Profiler profiler("demo");

void generateRandomArray(int a[NMAX], int n)
{
    int i;
    srand(time(NULL));
    for(i=0;i<n;i++)
    {
        a[i]=rand();
        profiler.countOperation("randomArray",n);
    }

}

void fillIncreasingArray(int a[NMAX], int n, int low, int high)
{
    int i;
    srand(time(NULL));
    a[0]=rand() % (high-n+1-low) + low;
    profiler.countOperation("increasingArray",n);

    for(i=1;i<n;i++)
    {  a[i]=rand() % (high-n+1+i-a[i-1]) + a[i-1]+1 ;
    profiler.countOperation("increasingArray",n);
    }


}


int main()
{
    int a1[NMAX],a2[NMAX], n, low, high, i;
    printf("Enter low and high:");
    scanf("%d%d",&low,&high);
    for(n=1;n<20;n++)
    {
        //we will generate a random sequence of numbers
        generateRandomArray(a1,n);
        //we will generate an increasing sequence of random numbers and we'll print them in a file
        fillIncreasingArray(a1,n,low,high);
        FILE *pf=fopen("output.txt","w");
        for(i=0;i<n;i++)
           {
               fprintf(pf,"%d ",a1[i]);
               profiler.countOperation("writeToFile",n);
           }
        fprintf(pf,"\n");
        fclose(pf);

        // we will read the sequence from the file
        FILE *pg=fopen("output.txt","r");
        printf("\n");
        for(i=0;i<n;i++)
           {
               fscanf(pg,"%d ",&a2[i]);
               printf("%d ",a2[i]);
               profiler.countOperation("readFromFile",n);
           }
        fclose(pg);
    }
    profiler.createGroup("Assignment","randomArray","increasingArray","writeToFile","readFromFile");
    profiler.showReport();



   return 0;
}


