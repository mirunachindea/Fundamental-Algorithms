/*
    @Name: Chindea Miruna
    @Group: 30424
    Subject: Hash tables - insertion and search
    Conclusions: As the filling factor increases, the effort for searching
    a value in the table increases too. Also, the effort for searching a
    value that is not in the table is significantly bigger than the one for
    searching a value that is in the table.

*/
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <iomanip>
#define NIL 9999999
#include "Profiler.h"
using namespace std;
int N, operations, max_op_f, max_op_nf, tot_op_f, tot_op_nf;
typedef struct
{
    int id;
    char name[30];
}Entry;

//int h(int id, int i)
//{
//    int x = (5*id + 3*i) % N;
//    return x;
//}

int h(int id, int i)
{
    int x = (id + 3*i + 2*i*i) % N;
    return x;
}

int hashInsert(Entry T[], Entry k)
{
    int i = 0;
    do
    {
        int j = h(k.id, i);
        if (T[j].id == NIL)
        {
            T[j].id = k.id;
            strcpy(T[j].name, k.name);
            return j;
        }
        else
        {
            if( T[j].id == k.id)
            {
                 strcpy(T[j].name, k.name);
                 return j;
            }
            else
            {
                i++;
            }
        }
    } while(i < N);
    return 0;
}

int hashSearch(Entry T[], int key)
{
    int i = 0, j;
    do{
        j = h(key, i);
        operations++;
        if (T[j].id == key)
        {
            cout<<T[j].name<<endl;
            return j ;
        }
        i++;
    }while ( T[j].id != NIL && i < N);
    cout<<"not found"<<endl;
    return NIL;
}

void Test()
{
    Entry T[10], k[5];
    int i;
    N = 10;
    for(i=0; i<N; i++)
        T[i].id = NIL;
    k[0].id = 2;
    k[1].id = 12;
    k[2].id = 22;
    k[3].id = 3;
    k[4].id = 2;
    for(i=0; i<=4; i++)
    {
        strcpy(k[i].name, "element found");
        hashInsert(T, k[i]);
    }
    for(i=0; i<N; i++)
    {
        if(T[i].id < NIL)
         {
             cout<<T[i].id<<" ";
         }
        else
        {
            cout<<"- ";
        }
    }
    cout<<endl;
    for(i=0; i<=4; i++)
    {
        operations=0;
        hashSearch(T, k[i].id);
        cout<<"Search "<<k[i].id<<" operations: "<<operations<<endl;
    }
    hashSearch(T, 4);
}

void initTable(Entry T[])
{
    for(int i=0; i<N; i++)
    {
        T[i].id = NIL;
    }
}

void insertInTable(Entry T[], Entry k[], int nbOfValues, int a[])
{
    FillRandomArray(a, nbOfValues+1500, 1, 12000, true, UNSORTED);
    for(int i=0; i<nbOfValues; i++)
    {
        k[i].id = a[i];
        strcpy(k[i].name, "found");
        hashInsert(T, k[i]);
    }
}

void searchFound(Entry T[], Entry k[])
{
    max_op_f = 0;
    for(int i=0; i<1500; i++)
    {
        operations = 0;
        hashSearch(T, k[i*4].id);
        tot_op_f += operations;
        if(max_op_f < operations)
        {
            max_op_f = operations;
        }
    }
}

void searchNotFound(Entry T[], int a[], int n)
{
    max_op_nf = 0;
    for(int i=n; i<=n + 1500; i++)
    {
        operations = 0;
        hashSearch(T, a[i]);
        tot_op_nf += operations;
        if( max_op_nf < operations)
         {
             max_op_nf = operations;
         }
    }
}

int main()
{
    Test();
    srand(time(NULL));
    Entry T[10008], k[10008];
    int a[11500], n[5];
    float fillFactor[] = {0.8, 0.85, 0.9, 0.95, 0.99};
    N=10007;
    cout<<"fill factor \t avg ops found \t max found \t avg ops not found \t max not found "<<endl;
    for(int i=0; i<=4; i++)
    {
        n[i] = floor(N * fillFactor[i]);
        initTable(T);
        insertInTable(T, k, n[i], a);
        for(int j=0; j<=4; j++)
        {
            searchFound(T,k);
            searchNotFound(T,a,n[i]);
        }
        float avg_op_f = (float)tot_op_f/5/1500;
        float avg_op_nf = (float)tot_op_nf/5/1500;

        cout<<setprecision(4)<<fillFactor[i]<<"\t\t "<<avg_op_f<<"\t\t "<<max_op_f<<"\t\t "<<avg_op_nf<<"\t\t\t "<<max_op_nf<<endl;
    }

return 0;
}
