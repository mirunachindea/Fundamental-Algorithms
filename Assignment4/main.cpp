/*
    @Student: Chindea Miruna
    @Group: 30424
    Subject: Merge k sorted lists efficiently
    Conclusions: I merged k lists with a total of n elements using a heap, so
    the time complexity of my algorithm is O(nlogk).
    In the first case, k is constant, so the time complexity is O(n).
    In the sencond case, when n is constant, the time complexity is O(logk).
*/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "Profiler.h"
using namespace std;
Profiler profiler("demo");
long assignments, comparisons,operations;

typedef struct StructureT
{
    int key;
    int listNr;
}Structure;

void swappingStructure(Structure &a, Structure &b)
{
   int aux = a.key;
   a.key = b.key;
   b.key = aux;

   aux = a.listNr;
   a.listNr = b.listNr;
   b.listNr = aux;

}

void makecopy(int source[], int dest[], int n)
{
    for(int i=1; i<=n; i++){
        dest[i] = source[i];
    }
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

typedef struct NodeT
{
    int key;
    struct NodeT* pNext;
} Node;

typedef struct ListT
{
    Node* pFirst;
    Node* pLast;
} List;

Node* createNode(int keyToInsert)
{
    Node *pNode = (Node*)malloc(sizeof(Node));
    comparisons ++;
    if (pNode)
    {
        assignments +=2;
        pNode->key = keyToInsert;
        pNode->pNext = NULL;
    }
    return pNode;
}

void insertNode( List *pL, int key)
{
    Node *pNode = createNode(key);
    pNode->pNext = NULL;
    assignments+=2;
    comparisons++;
    if (pL->pFirst != NULL)
     {
         pL->pLast->pNext = pNode;
         assignments++;
     }
    else
    {
        pL->pFirst = pNode;
        assignments++;
    }
    pL->pLast = pNode;
    assignments +=1;
}

List* initList(int n)
{
    List* pL = new List;
    pL->pFirst = NULL;
    assignments+=1;
    int key1 = rand()%10;
    insertNode(pL, key1);
    for(int i=2; i<=n; i++)
    {
        int key = rand()% n + key1 ;
        insertNode(pL, key);
        key1 = key;
    }
    return pL;
}

int removeFirst( List *pL )
{
    Node* pNode;
    comparisons++;
    if( pL->pFirst != NULL)
    {
        pNode = pL->pFirst;
        pL->pFirst = pL->pFirst->pNext;
        assignments+=2;
        free(pNode);
        if( pL->pFirst == NULL )
        {
            pL->pLast = NULL;
            assignments++;
        }
        comparisons++;
        return pNode->key;
    }
    return 0;
}

void showList( List *pL )
{
    Node *pNode = pL->pFirst;
    if( pL->pFirst == NULL ){
        cout<<"There are no nodes in the list";
    }
    while( pNode != NULL)
    {
        cout<<pNode->key<<" ";
        pNode = pNode->pNext;
    }
    cout<<endl;
}

void swapping( int *a, int *b )
{
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

void heapify( Structure a[], int i, int *heapsize )
{
    int l=left(i), r=right(i), smallest;
    comparisons++;
    if( a[l].key < a[i].key && l <= *heapsize )
      {
          smallest = l;
      }
    else
    {
        smallest = i;
    }

    comparisons++;
    if ( a[r].key < a[smallest].key && r <= *heapsize )
     {
         smallest = r;
     }

    if ( smallest != i )
    {
        swappingStructure( a[i], a[smallest]);
        assignments+6;
        heapify( a, smallest, heapsize );
    }
}

void BuildHeapBU( Structure a[], int n )
{
    int heapsize = n;
    for( int i=n/2; i>=1; i-- )
    {
        heapify( a, i, &heapsize );
    }
}

void purgeList(List *pL)
{
    Node *pNode;
    while( pL->pFirst != NULL)
    {
        pNode = pL->pFirst;
        pL->pFirst = pL->pFirst->pNext;
        free(pNode);
    }
    pL->pLast = NULL;
}

void mergeLists(int a[10001], List *Lists[10001], int nbOfLists, int &totalElements)
 {
    Structure heap[10001];
    int  i, k, source;
    for( i=1; i<= nbOfLists; i++)
    {
        heap[i].key = removeFirst(Lists[i]);
        heap[i].listNr = i;
        assignments+=2;
    }
    int heapsize = nbOfLists;
    BuildHeapBU(heap, heapsize);
    k = 1;
    while( heapsize >= 2)
    {
        a[k] = heap[1].key;
        source = heap[1].listNr;
        assignments+=2;
        k++;
        comparisons++;
        if( Lists[source]->pFirst != NULL)
        {
            heap[1].key = removeFirst(Lists[source]);
            assignments++;
        }
        else
        {
            heap[1] = heap[heapsize];
            assignments++;
            heapsize--;
        }
        heapify(heap,1,&heapsize);
    }
    a[k] = heap[1].key;
    source=heap[1].listNr;
    assignments+=2;
    while( Lists[source]->pFirst != NULL )
    {
        k++;
        a[k] = removeFirst(Lists[source]);
        comparisons++;
        assignments++;
    }
    comparisons++;
    totalElements = k;
    //cout<<"the nr of elements is "<<k;
    }

void test(int n, int k)
{
    List *Lists[10000];
    int  nbOfElements,i, a[10000], totalElements = 0;
    nbOfElements = n/k;
    int rest = n%k;
    for(i=1; i<=k-rest; i++)
        {
            Lists[i] = initList(nbOfElements);
        }
    for(i=k-rest+1; i<=k; i++)
    {
        Lists[i] = initList(nbOfElements+1);
    }
    for(i=1; i<=k; i++)
       {
           cout<<"List nr "<<i<<": ";
           showList(Lists[i]);
       }
    mergeLists(a, Lists, k, totalElements);
    cout<<"Merged list: ";
    for(int i=1; i<=totalElements; i++)
    {
        cout<<a[i]<<" ";
    }
}

void applyAlg(int n, int k, List *Lists[10001], int a[10001])
{

    int  nbOfElements, i, totalElements=0;
    nbOfElements = n/k;
    int rest = n%k;

    for(i=1; i<=k-rest; i++)
        {
            Lists[i] = initList(nbOfElements);
        }
    for(i=k-rest+1; i<=k; i++)
        {
            Lists[i]=initList(nbOfElements+1);
        }
    mergeLists(a, Lists, k, totalElements);

}

void resetCounter()
{
    assignments = 0;
    comparisons = 0;
    operations = 0;
}

void countOp1(int n)
{
    operations=assignments+comparisons;
    profiler.countOperation("operations_k1",n,operations);
}

void countOp2(int n)
{
    operations=assignments+comparisons;
    profiler.countOperation("operations_k2",n,operations);
}

void countOp3(int n)
{
    operations=assignments+comparisons;
    profiler.countOperation("operations_k3",n,operations);
}

void countOp4(int k)
{
    operations = assignments + comparisons;
    profiler.countOperation("operations",k,operations);
}

void createGroup()
{
    profiler.createGroup("operations", "operations_k1", "operations_k2", "operations_k3" );
}
int main()
{
    srand(time(NULL));
    List *Lists[10000];
    int n,k;
    int a[10001];
    // Case #1: k constant
    for( n=100; n<=10000; n+=100)
    {
        resetCounter();
        applyAlg(n,5, Lists, a);
        countOp1(n);

        resetCounter();
        applyAlg(n,10,Lists, a);
        countOp2(n);

        resetCounter();
        applyAlg(n,100,Lists,a);
        countOp3(n);

        cout<<n<<endl;
    }

    createGroup();

    // Case #2: n constant
    n=10000;
    for(k=10; k<=500; k+=10)
    {
        resetCounter();
        applyAlg(n,k,Lists,a);
        countOp4(k);
    }

    profiler.showReport();

    // Test on a small-sized input
    test(22,4);
    return 0;
}
