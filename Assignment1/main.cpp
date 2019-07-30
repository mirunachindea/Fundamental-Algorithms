/* CONCLUSIONS:
- after counting the total operations in the average case, we can say that insertion sort is the most
efficient method of sorting, bubble sort being the least efficient
- after counting the total operations in the best case, we observe that the most efficient sorting method
is bubble sort, and the least efficient one is selection sort
- after testing the algorithm in the worst case, we can say that insertion and selection sort are almost
equally efficient, bubble sort being the least efficient sorting method
 */




#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "Profiler.h"

using namespace std;
Profiler profiler("sorting algorithms");
int b_comparisons, b_assignments, i_comparisons, i_assignments, s_comparisons, s_assignments;

void swapping(int *a,int *b)
{
    int aux;
    aux=*a;
    *a=*b;
    *b=aux;
}

int searchpos(int a[], int li, int ls, int x)
{

    if (ls<=li)
    {
        if ( x> a[li] )
            return li+1;
        return li;
    }
    int m=(li+ls)/2;
    if( x == a[m])
        return m+1;
    if ( x > a[m] )
        return searchpos(a,m+1,ls,x);
    return searchpos(a,li,m-1,x);
}
void BubbleSort(int a[],int n)
{
    int i;
    bool swapped=true;
    while ( swapped )
    {
        swapped=false;
        for(i=0; i<=n-2; i++)
        {
            //profiler.countOperation("bubble_comp", n);
            b_comparisons++;
            if( a[i] > a[i+1] )
            {
                //profiler.countOperation("bubble_assign", n, 3);
                b_assignments+=3;
                swapping( &a[i], &a[i+1] );
                swapped=true;
            }

        }
    }
}

void InsertionSort(int a[],int n)
{
    int i,j, pos,aux;
    for(i=1; i<n; ++i)
    {
        j=i-1;
        aux=a[i];
        i_assignments++;

        pos=searchpos(a,0,j,aux);
        i_comparisons+=3;

        while(j>=pos && j>=0 )
        {
            a[j+1]=a[j];
            i_assignments++;
            j--;
        }
        a[j+1]=aux;
        i_assignments++;
    }
}

void InsertionSort2(int a[], int n)
{
    int i,j, aux;
    for(i=1; i<n; i++)
    {
        aux=a[i];
        //profiler.countOperation("insertion_assign",n);
        i_assignments++;

        j=i-1;
        while( j >= 0 && a[j] > aux)
        {
            //profiler.countOperation("insertion_assign",n);
            i_assignments++;
            //profiler.countOperation("insertion_comp",n);
            i_comparisons++;
            a[j+1]=a[j];
            j--;
        }
        a[j+1]=aux;
        //profiler.countOperation("insertion_assign",n);
        i_assignments++;
        //profiler.countOperation("insertion_comp",n);
        i_comparisons++;

    }
}

void SelectionSort(int a[], int n)
{

    int i, j, pmin;
    for(i=0; i<=n-2; i++)
    {
        pmin=i;
        for(j=i+1; j<=n-1; j++)
        {
            //profiler.countOperation("selection_comp",n);
            s_comparisons++;
            if ( a[j] < a[pmin])
                pmin=j;
        }

        swapping(&a[i],&a[pmin]);
        //profiler.countOperation("selection_assign",n,3);
        s_assignments+=3;

    }
}
void makecopy(int a1[], int a2[], int n)
{
    for(int i=0; i<n; i++)
        a2[i]=a1[i];
}

int main()
{
    int a1[10002],a2[10002], a3[10002], n, i, j;

//    for(j=0; j<4; j++)
//    {

        for(n=100; n<10000; n+=100)
        {

            b_comparisons=0;
            b_assignments=0;
            i_comparisons=0;
            i_assignments=0;
            s_comparisons=0;
            s_assignments=0;

//            FillRandomArray(a1,n,10,10000,true,UNSORTED);
//            FillRandomArray(a1,n,10,10000,true,1);
            for(i=0; i<n; i++)
                a1[i]=n-i;

            makecopy(a1,a2,n);
            makecopy(a1,a3,n);

            BubbleSort(a1,n);
            profiler.countOperation("bubble_comp",n,b_comparisons);
            profiler.countOperation("bubble_assign",n,b_assignments);

            InsertionSort(a2,n);
            profiler.countOperation("insertion_comp",n,i_comparisons);
            profiler.countOperation("insertion_assign",n,i_assignments);

            SelectionSort(a3,n);
            profiler.countOperation("selection_comp",n,s_comparisons);
            profiler.countOperation("selection_assign",n,s_assignments);

            printf("%d\n",n);

        }

//    }

//    profiler.divideValues("bubble_comp",5);
//    profiler.divideValues("bubble_assign",5);
//    profiler.divideValues("insertion_comp",5);
//    profiler.divideValues("insertion_assign",5);
//    profiler.divideValues("selection_comp",5);
//    profiler.divideValues("selection_assign",5);

    profiler.addSeries("bubble_operations","bubble_comp","bubble_assign");
    profiler.addSeries("insertion_operations","insertion_comp","insertion_assign");
    profiler.addSeries("selection_operations","selection_comp","selection_assign");

//    profiler.createGroup("AvgCaseComp","bubble_comp","insertion_comp","selection_comp");
//    profiler.createGroup("AvgCaseAssign","bubble_assign","insertion_assign","selection_assign");
//    profiler.createGroup("AvgCaseOperations","bubble_operations","insertion_operations","selection_operations");


//    profiler.createGroup("BestCaseComp","bubble_comp","insertion_comp","selection_comp");
//    profiler.createGroup("BestCaseAssign","bubble_assign","insertion_assign","selection_assign");
//    profiler.createGroup("BestCaseOperations","bubble_operations","insertion_operations","selection_operations");

//    profiler.createGroup("WorstCaseComp","bubble_comp","insertion_comp","selection_comp");
//    profiler.createGroup("WorstCaseAssign","bubble_assign","insertion_assign","selection_assign");
//    profiler.createGroup("WorstCaseOperations","bubble_operations","insertion_operations","selection_operations");

    profiler.showReport();


//example for a small array
    int b[100]= {-5,3,2,100,1,0,3,-3,6,7};
    //BubbleSort(b,10);
    //InsertionSort(b,10);
    //SelectionSort(b,10);

    for(i=0; i<10; i++)
        cout<<b[i]<<" ";


    return 0;
}
