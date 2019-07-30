/*
    @Student: Chindea Miruna
    @Group: 30424

    Subject: Comparing the 2 Build-Heap methods, Bottom-up and Top-down
    in the average and worst cases

    Conclusions:
    - we can see that in the average case, the bottom-up method is more
    efficient than the top-down building method
    - analysing the worst case charts, it is clear that the bottom-up one
    is much more efficient than the other build-heap method

*/


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include "Profiler.h"
#define NMIN -9999
using namespace std;
Profiler profiler("sorting algorithms");
int n,m;
long bottomup_assign, bottomup_comp, topdown_assign, topdown_comp;

void swapping( int *a, int *b )
{
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

int parent( int i )
{
    return i/2;
}

int left( int i )
{
    return 2*i;
}

int right( int i )
{
    return 2*i+1;
}

void MaxHeapify( int a[], int i, int *heapsize )
{
    int l=left(i), r=right(i), largest;
    bottomup_comp ++ ;
    if( a[l] > a[i] && l < *heapsize )
      {
          largest=l;
      }
    else
    {
        largest=i;
    }

    bottomup_comp ++ ;
    if ( a[r] > a[largest] && r < *heapsize )
     {
         largest=r;
     }

    if ( largest != i )
    {
        swapping( &a[i], &a[largest] );
        bottomup_assign += 3;
        MaxHeapify( a, largest, heapsize );
    }
}

void BuildHeapBU( int a[], int n )
{
    int heapsize = n;
    for( int i=n/2; i>=1; i-- )
    {
        MaxHeapify( a, i, &heapsize );
    }
}

int maximum( int a[] )
{
    return a[0];
}

void IncreaseKey( int a[], int i, int key )
{
    topdown_comp ++ ;
    if( a[i] <= key )
    {
        a[i]=key;
        while( i > 1 && a[parent(i)] < a[i])
        {
            topdown_comp ++ ;
            swapping( &a[parent(i)], &a[i] );
            topdown_assign += 3;
            i = parent(i);
        }
        topdown_comp ++ ;
    }
}

void HeapInsert( int a[], int key, int *heapsize )
{
    (*heapsize) ++ ;
    int n = (*heapsize);
    a[(*heapsize)] = NMIN;
    topdown_assign ++ ;
    IncreaseKey( a, n, key );
}

void BuildHeapTD( int n, int a[],int source[] )
{
    int heapsize = 0;
    for( int i=1; i<=n; i++ )
    {
        HeapInsert( a, source[i], &heapsize );
    }
}

void test()
{
    int c[10]= {NULL,1,5,2,1,3,7,2,4,3}, d[10], n=9, i;
    cout<<"The original array:\n";
    for( i=1; i<= n; i++)
        cout<<c[i]<<" ";
    BuildHeapTD( n, d, c );
    cout<<"\nThe array after applying Top-Down Build-Heap:\n";
    for( i=1; i<=n; i++ )
        cout<<d[i]<<" ";
    BuildHeapBU( c, n );
    cout<<"\nThe array after applying Bottom-Up Build-Heap:\n";
    for( i=1; i<=n; i++ )
        cout<<c[i]<<" ";
}

void resetCount()
{
    bottomup_assign=0;
    bottomup_comp=0;
    topdown_assign=0;
    topdown_comp=0;
}

void countOperation(int n)
{
    profiler.countOperation("topdown_assignments",n,topdown_assign);
    profiler.countOperation("topdown_comparisons",n,topdown_comp);
    profiler.countOperation("bottomup_assignments",n,bottomup_assign);
    profiler.countOperation("bottomup_comparisons",n,bottomup_comp);
}

void divideValues()
{
    profiler.divideValues("bottomup_assignments",5);
    profiler.divideValues("bottomup_comparisons",5);
    profiler.divideValues("topdown_assignments",5);
    profiler.divideValues("topdown_comparisons",5);
}

void addSeries()
{
    profiler.addSeries("bottomup_operations","bottomup_assignments","bottomup_comparisons");
    profiler.addSeries("topdown_operations","topdown_assignments","topdown_comparisons");
}

void createGroupAvg()
{
    profiler.createGroup("assignments average case","bottomup_assignments","topdown_assignments");
    profiler.createGroup("comparisons average case","bottomup_comparisons","topdown_comparisons");
    profiler.createGroup("total operations average case","bottomup_operations","topdown_operations");
}

void createGroupWorst()
{
    profiler.createGroup("assignments","bottomup_assignments","topdown_assignments");
    profiler.createGroup("comparisons","bottomup_comparisons","topdown_comparisons");
    profiler.createGroup("total operations","bottomup_operations","topdown_operations");

}
int main()
{
    int a[10001], b[10001], i, j, key;
//    for(j=0; j<5; j++)
//    {
//        for(n=100; n<=10000; n+=100)
//        {
//            resetCount();
//            srand(time(NULL));
//            for(i=1;i<=n;i++)
//             {
//                 average case
//                 a[i]=rand();
//
//                 worst case
//                 a[i]=i-1;
//
//                 best case
//                 a[i]=n-i;
//             }
//            a[0]=NULL;
//            BuildHeapTD(n,b,a);
//            BuildHeapBU(a,n);
//            countOperation(n);
//            printf("%d\n",n);
//        }
//  }
//    divideValues();
//    addSeries();
//    createGroupAvg();
//    createGroupWorst();
//    profiler.showReport();

//   example for a small input:
     test();
    return 0;
}

