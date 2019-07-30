/*
    @Student: Chindea Miruna
    @Group: 30424
    Subject: Depth-First Search, Topological Sort and Tarjan's SCC Algorithm
    Conclusions: The DFS algorithm has the time complexity of O(V+E), where
    V = nb of nodes, E = nb of edges.
    In the first case, the nb of nodes is constant => time complexity is O(E).
    In the second case, the nb of edges is constant => time complexity is O(V).
*/
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stack>
#include "Profiler.h"
using namespace std;
Profiler profiler("DFS");
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
List* TopL;
bool visited[201];
int nbOfNodes, nbOfEdges;
int op;
std::stack<int> S;
int disc_time[201];
int low_link[201];
bool on_stack[201];


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

void listPush( List *pL, int data )
{
   Node* pNode = createNode(data);
   if( pL->pFirst == NULL)
   {
       pL->pFirst = pNode;
       pL->pLast = pNode;
   }
   else
   {
       pNode->pNext = pL->pFirst;
       pL->pFirst = pNode;
   }
}

void DFS_Comp( Node* srcNode)
{
    cout<<srcNode->data<<" ";
    visited[srcNode->data] = true;
    op++;
    Node* aux = srcNode;
    while(aux != NULL)
    {
        op+=2;
        if( visited[aux->data] == false)
        {
            DFS_Comp(AdjList[aux->data]->pFirst);
        }
        aux = aux->pNext;
        op+=2;
    }
    op++;
    listPush(TopL, srcNode->data);

}

void DFS()
{
    for( int i=1; i<=nbOfNodes; i++)
    {
        visited[i] = false;
    }
    for( int i=1; i<=nbOfNodes; i++)
    {
        if ( visited[i] == false)
        {
            DFS_Comp( AdjList[i]->pFirst);
            cout<<endl;
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

void scc_visit( int node )
{
    static int time = 0;
    disc_time[node] = low_link[node] =  ++time;
    on_stack[node] = true;
    S.push(node);
    Node* aux = AdjList[node]->pFirst->pNext;
    while ( aux != NULL)
    {
        int neigh = aux->data;
        if ( disc_time[neigh] == -1)
        {
            scc_visit(neigh);
            low_link[node] = min(low_link[node], low_link[neigh]);
        }
        else if ( on_stack[neigh] == true )
        {
            low_link[node] = min( low_link[node], disc_time[neigh]);
        }
        aux = aux->pNext;
    }
    int w = 0;
    if( low_link[node] == disc_time[node])
    {
        cout<<"start scc: ";
        while ( S.top() != node)
        {
            w = (int)S.top();
            cout<<w<<" ";
            on_stack[w] == false;
            S.pop();
        }
        w = (int)S.top();
        cout<<w<<"\n";
        on_stack[w] = false;
        S.pop();
    }
}

void Tarjan()
{
    for( int i=1; i <= nbOfNodes; i++)
    {
        disc_time[i] = -1;
        low_link[i] = -1;
        on_stack[i] = false;
    }
    for( int i=1; i <= nbOfNodes; i++)
    {
        if (disc_time[i] == -1)
        {
            scc_visit(i);
        }
    }
}

void test()
{
    int i;
    TopL = initList();
    nbOfNodes = 9;
    nbOfEdges = 14;
    for(  i=1; i <= nbOfNodes; i++)
    {
       AdjList[i] = initList();
       insertNode(AdjList[i], i);
    }
    insertNode(AdjList[1], 3);
    insertNode(AdjList[1], 6);
    insertNode(AdjList[2], 3);
    insertNode(AdjList[2], 5);
    insertNode(AdjList[3], 4);
    insertNode(AdjList[4], 2);
    insertNode(AdjList[4], 3);
    insertNode(AdjList[5], 4);
    insertNode(AdjList[6], 1);
    insertNode(AdjList[6], 2);
    insertNode(AdjList[7], 8);
    insertNode(AdjList[7], 9);
    insertNode(AdjList[8], 9);
    insertNode(AdjList[9], 7);
    cout<<"Adjacency lists:\n";
    for( i=1; i <= nbOfNodes; i++)
    {
       showList(AdjList[i]);
    }
    cout<<"DFS:\n";
    DFS();
    cout<<"Tarjan:\n";
    Tarjan();
}

void case1()
{
    nbOfNodes = 100;
    for( nbOfEdges = 1000; nbOfEdges <= 4500; nbOfEdges+=100)
    {
        op = 0;
        generateRandomGraph();
        DFS();
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
        DFS();
        profiler.countOperation("operations", nbOfNodes, op);
        //cout<<nbOfNodes<<endl;
    }

}

void test2()
{
    cout<<"--------------------------\n";
    int i;
    TopL = initList();
    nbOfNodes = 9;
    nbOfEdges = 7;
    for(  i=1; i <= nbOfNodes; i++)
    {
       AdjList[i] = initList();
       insertNode(AdjList[i], i);
    }

    insertNode(AdjList[1], 3);
    insertNode(AdjList[3], 4);
    insertNode(AdjList[5], 4);
    insertNode(AdjList[6], 1);
    insertNode(AdjList[6], 2);
    insertNode(AdjList[7], 8);
    insertNode(AdjList[8], 9);
    cout<<"Adjacency lists:\n";
    for( i=1; i <= nbOfNodes; i++)
    {
       showList(AdjList[i]);
    }
    cout<<"DFS:\n";
    DFS();
    cout<<"Topological sort:\n";
    showList(TopL);
    //cout<<"Tarjan:\n";
    //Tarjan();
}

int main()
{
    test();
    test2();
    //case1();
    //case2();
    //profiler.showReport();

}
