#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include "Profiler.h"
#define NMIN -9999
using namespace std;
Profiler profiler("sorting algorithms");
int heap_comp, heap_assign, quick_comp, quick_assign;

void makecopy(int source[], int dest[], int n)
{
    for(int i=1; i<=n; i++)
        dest[i]=source[i];
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

void swapping( int *a, int *b )
{
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

void heapify( int a[], int i, int *heapsize )
{
    int l=left(i), r=right(i), largest;
    heap_comp ++ ;
    if( a[l] > a[i] && l < *heapsize )
      {
          largest=l;
      }
    else
    {
        largest=i;
    }

    heap_comp ++ ;
    if ( a[r] > a[largest] && r < *heapsize )
     {
         largest=r;
     }

    if ( largest != i )
    {
        swapping( &a[i], &a[largest] );
        heap_assign += 3;
        heapify( a, largest, heapsize );
    }
}

void BuildHeapBU( int a[], int n )
{
    int heapsize = n;
    for( int i=n/2; i>=1; i-- )
    {
        heapify( a, i, &heapsize );
    }
}

void HeapSort( int a[], int n, int *heapsize)
{
    BuildHeapBU(a,n);
    for( int i=n; i>=2; i--)
    {
        swapping(&a[i],&a[1]);
        (*heapsize)--;
        heapify(a,1, heapsize);
    }

}

int Partition(int a[], int p_start, int p_end)
{
    int x=a[p_end], i;
    quick_assign++;
    int index=p_start-1;
    for( i=p_start;i<p_end;i++)
    {
        quick_comp++;
        if( a[i]<x )
    {
        index++;
        swapping(&a[i], &a[index]);
        quick_assign+=3;
    }
    }
    swapping(&a[p_end], &a[index+1]);
    quick_assign+=3;
    return index+1;

}

void QuickSort(int a[], int p_start, int p_end)
{
    int p;
    if( p_start < p_end)
    {
        p=Partition( a, p_start, p_end);
        QuickSort(a, p_start, p-1);
        QuickSort(a, p+1, p_end);
    }

}

int QuickSelect(int v[],int first, int last,int i)
{
    if(first == last)
    {
        return v[first];
    }
    int p = Partition(v,first,last);
    int relPos = p-first+1;
    if(relPos == i)
    {
        return v[p];
    }
    else if(i < relPos)
    {
        return QuickSelect(v, first, p-1, i);
    }
    else
        {
           return QuickSelect(v, p+1, last,i-relPos );
        }
}

void test()
{
    int a[20]={NULL, 3, 2, 0, 10, 7, 4, 20, 1}, n=8,
    b[20]={NULL, 3, 2, 0, 10, 7, 4, 20, 1};
    cout<<"The initial array: "<<endl;
    for(int i=1;i<=n;i++)
        cout<<a[i]<<" ";
    cout<<endl<<"The sorted array with quicksort: "<<endl;
    QuickSort(a,1,n);
    for(int i=1;i<=n;i++)
        cout<<a[i]<<" ";
    cout<<endl<<"The sorted array with heapsort: "<<endl;
    int heapsize=n;
    HeapSort(b,n,&heapsize);
    for(int i=1;i<=n;i++)
        cout<<b[i]<<" ";

}

void resetCount()
{
    heap_assign=0;
    heap_comp=0;
    quick_assign=0;
    quick_comp=0;
}

void countOperation(int n)
{
    profiler.countOperation("heap_assignments",n,heap_assign);
   profiler.countOperation("heap_comparisons",n,heap_comp);
    profiler.countOperation("quick_assignments",n,quick_assign);
    profiler.countOperation("quick_comparisons",n,quick_comp);
}

void divideValues()
{
    profiler.divideValues("heap_assignments",5);
    profiler.divideValues("heap_comparisons",5);
    profiler.divideValues("quick_assignments",5);
    profiler.divideValues("quick_comparisons",5);
}

void addSeries()
{
    profiler.addSeries("heap_operations","heap_assignments","heap_comparisons");
    profiler.addSeries("quick_operations","quick_assignments","quick_comparisons");
}

void createGroupAvg()
{
    profiler.createGroup("assignments average case","heap_assignments","quick_assignments");
    profiler.createGroup("comparisons average case","heap_comparisons","quick_comparisons");
    profiler.createGroup("total operations average case","heap_operations","quick_operations");
}

void createGroupWorst()
{
    profiler.createGroup("assignments worst case","heap_assignments","quick_assignments");
    profiler.createGroup("comparisons worst case","heap_comparisons","quick_comparisons");
    profiler.createGroup("total operations worst case","heap_operations","quick_operations");
}

void createGroupBest()
{
    profiler.createGroup("assignments best case","heap_assignments","quick_assignments");
    profiler.createGroup("comparisons best case","heap_comparisons","quick_comparisons");
    profiler.createGroup("total operations best case","heap_operations","quick_operations");
}

void testQuickSelect()
{
    int a[20]={NULL,20,5,1,4,0,17};
    cout<<endl<<endl;
    cout<<"The unsorted array: ";
    for(int i=1;i<=6;i++)
        cout<<a[i]<<" ";
    int x=QuickSelect(a,1,6,2);
    cout<<endl<<"Position "<<2<<":"<<x;
}

int main()
{

    int a[10001], b[10001], i, j,n;

//     for(j=0; j<5; j++)
//    {
//        for(n=100; n<=10000; n+=100)
//        {
//            resetCount();
//            srand(time(NULL));
//            for(i=1;i<=n;i++)
//             {
//                 average case
//               a[i]=rand();
//                 worst case
//                 a[i]=i-1;
//                 best case
//                a[i]=n;
//             }
//            a[0]=NULL;
//            makecopy(a,b,n);
//            int heapsize=n;
//            HeapSort(a,n,&heapsize);
//            QuickSort(b,1,n);
//            countOperation(n);
//            printf("%d\n",n);
//        }
//  }
//    divideValues();
//      addSeries();
//    createGroupAvg();
//   createGroupWorst();
//    createGroupBest();
//    profiler.showReport();

   test();
   testQuickSelect();

    return 0;

}
