/*
    @Student: Chindea Miruna
    @Group: 30424
    Subject: Breadth First Search
    Conclusions: The time complexity for the BFS algorithm is O(V+E); V = number of nodes, E = number of edges.
    In the first case, when the nb of nodes is constant, the time complexity is O(E).
    In the second case, when the nb of edges is constant, the time complexity is O(V).
*/
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Profiler.h"
#define NMAX 9999
using namespace std;
Profiler profiler("BFS");
int op;

typedef struct Nodetype
{
    int data;
    struct Nodetype *pNext;
} Node;

typedef struct ListT
{
    Node* pFirst;
    Node* pLast;
} List;

List* AdjList[201];
bool visited[201];
int d[201];
int nbOfNodes, nbOfEdges;
typedef struct Q
{
    Node *pFirst;
    Node *pLast;
} Queue;

Node *createNode(int data)
{
    Node *p = (Node*)malloc(sizeof(Node));
    if(p)
    {
        p->data = data;
        p->pNext = NULL;
    }
    return p;
}

void insertNode( List *pL, int key)
{
    Node *pNode = createNode(key);
    if (pL->pFirst != NULL)
     {
         pL->pLast->pNext = pNode;
     }
    else
    {
        pL->pFirst = pNode;
    }
    pL->pLast = pNode;
    pL->pLast->pNext = NULL;
}

List* initList()
{
    List* pL = (List*)malloc(sizeof(List));
    pL->pFirst = NULL;
    pL->pLast = NULL;
    return pL;
}

void showList( List *pL )
{
    Node *pNode = pL->pFirst;
    if( pL->pFirst == NULL ){
        cout<<"There are no nodes in the list";
    }
    while( pNode != NULL)
    {
        cout<<pNode->data<<" ";
        pNode = pNode->pNext;
    }
    cout<<endl;
}

Queue *createEmptyQueue()
{
    Queue *pL = (Queue*)malloc(sizeof(Queue));
    if( pL )
    {
        pL->pFirst = NULL;
        pL->pLast = NULL;
    }
    return pL;
}

void enqueue(Queue *pL, int data)
{
    Node *pNode = createNode(data);
    if( pL->pLast != NULL )
    {
        pL->pLast->pNext = pNode;
    }
    if( pL->pFirst == NULL )
    {
        pL->pFirst = pNode;
    }
    pL->pLast = pNode;
}

int dequeue(Queue *pL)
{
    Node *p = pL->pFirst;
    int a = p->data;
    pL->pFirst = p->pNext;
    free(p);
    if( pL->pFirst == NULL )
      {
          pL->pLast = NULL;
      }
    return a;
}

void BFSComponent( Node* srcNode)
{
    Queue* Q = createEmptyQueue();
    enqueue(Q, srcNode->data);
    visited[srcNode->data] = true;
    d[srcNode->data] = 0;
    op++;
    int i = 0;
    while( Q->pFirst != NULL)
    {
        op++;
        int ctVertexIndex =  dequeue(Q);
        Node* ctVertex = AdjList[ctVertexIndex]->pFirst;
        op++;
        while ( ctVertex != NULL)
        {
            op+=2;
            int adjvertex = ctVertex->data;
            if( visited[adjvertex] == false)
            {
                op++;
                visited[adjvertex] = true;
                enqueue(Q, adjvertex);
                d[adjvertex] = d[ctVertexIndex] + 1;
            }
            ctVertex = ctVertex->pNext;
            op++;
        }
        op++;
    }
    op++;
}

void showBFS()
{
    for( int i=1; i <=nbOfNodes; i++)
    {
        for( int j=0; j<=d[i]; j++)
        {
            cout<<"  ";
        }
        cout<<i<<endl;
    }
}

void BFS()
{
     for( int i=1; i<=nbOfNodes; i++)
    {
        visited[i] = false;
        d[i] = NMAX;
    }
    for( int i=1; i<=nbOfNodes; i++)
    {
        if ( visited[i] == false)
        {
            BFSComponent( AdjList[i]->pFirst);
        }
    }
}

void generateRandomGraph()
{
    int a[40000];
    int i;
    int maxNbOfEdges = nbOfNodes*(nbOfNodes-1) / 2;
    FillRandomArray(a,nbOfEdges, 1, maxNbOfEdges, true, UNSORTED);
    for( i=1; i <= nbOfNodes; i++)
    {
       AdjList[i] = initList();
       insertNode(AdjList[i], i);
    }

    for( i = 0; i < nbOfEdges; i++)
    {
        int k = a[i];
        //cout<<"pos is "<<k<<" ";
        int index = nbOfNodes - 1;
        int prevIndex;
        int j = 1;
        if( k <= index)
        {
            insertNode(AdjList[1], k+1);
            insertNode(AdjList[k+1], 1);
           //cout<<"nodes are 1 "<<k+1<<endl;
        }
        else
       {
           while ( k > index)
        {
            j++;
            prevIndex = index;
            index += nbOfNodes - j;
        }
        int node1 = j;
        int node2 = k - prevIndex + node1;
        insertNode(AdjList[node1], node2);
        insertNode(AdjList[node2], node1);
        //cout<<"nodes are "<<node1<<" "<<node2<<endl;
       }
    }
}

void test()
{
    int i;
    nbOfNodes = 8;
    nbOfEdges = 8;
    for(  i=1; i <= nbOfNodes; i++)
    {
       AdjList[i] = initList();
       insertNode(AdjList[i], i);
    }
    insertNode(AdjList[1], 2);
    insertNode(AdjList[1], 4);
    insertNode(AdjList[2], 1);
    insertNode(AdjList[2], 3);
    insertNode(AdjList[3], 2);
    insertNode(AdjList[3], 5);
    insertNode(AdjList[4], 1);
    insertNode(AdjList[4], 5);
    insertNode(AdjList[5], 3);
    insertNode(AdjList[5], 4);
    insertNode(AdjList[6], 7);
    insertNode(AdjList[6], 8);
    insertNode(AdjList[7], 6);
    insertNode(AdjList[7], 8);
    insertNode(AdjList[8], 6);
    insertNode(AdjList[8], 7);
    cout<<"Adjacency lists:\n";
    for( i=1; i <= nbOfNodes; i++)
    {
       showList(AdjList[i]);
    }
    cout<<"\nBFS Traversal:\n";
    BFS();
    showBFS();
}

void case1()
{
    nbOfNodes = 100;
    for( nbOfEdges = 1000; nbOfEdges <= 4500; nbOfEdges+=100)
    {
        op = 0;
        generateRandomGraph();
        BFS();
        profiler.countOperation("operations", nbOfEdges, op);
        //cout<<nbOfEdges<<endl;
    }
}

void case2()
{
    nbOfEdges = 4500;
    for( nbOfNodes = 100; nbOfNodes <= 200; nbOfNodes += 10)
    {
        op = 0;
        generateRandomGraph();
        BFS();
        profiler.countOperation("operations", nbOfNodes, op);
        //cout<<nbOfNodes<<endl;
    }

}
int main()
{
    int i;
    test();
    //case1();
    //case2();
    profiler.showReport();
    return 0;
}
