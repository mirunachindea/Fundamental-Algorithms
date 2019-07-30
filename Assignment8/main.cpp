/*
    @Student: Chindea Miruna
    @Group: 30424
    Subject: Disjoint Sets and Kruskal's algorithm for Minimum Spanning Tree
    Conclusions: Kruskal's MST algorithm has the time complexity ElogV 
    ( E = nb of edges, V = nb of nodes), therefore, for our problem, where
    V = n, E = n*4, the time complexity is nlogn.

*/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Profiler.h"
using namespace std;
Profiler profiler("Disjoint sets");
int nbOfNodes, nbOfEdges, operations;

typedef struct Set
{
	struct Set* parent;
	int value;
	int rank;
}Set;

typedef struct Edge
{
    Set* start;
    Set* end;
    int weight;
};

Set* makeSet(int value)
{
    Set* pSet = (Set*)malloc(sizeof(Set));
    pSet->parent = pSet;
    pSet->value = value;
    pSet->rank = 0;
    operations+=4;
    return pSet;
}

void link(Set* n1, Set* n2)
{
    operations++;
	if( n1->rank > n2->rank )
	{
	    operations++;
	    n2->parent = n1;
	}
	else
    {
        operations++;
        n1->parent = n2;
    }
    operations++;
	if( n1->rank == n2->rank )
    {
        operations++;
        n2->rank ++;
    }
}

Set* findSet(Set* pSet)
{
    operations++;
	if( pSet != pSet->parent )
	{
        operations++;
	    pSet->parent = findSet(pSet->parent);
	}
	return pSet->parent;
}

void unionSet(Set* n1, Set* n2)
{
	link(findSet(n1), findSet(n2));
}

Edge* makeEdge( Set* start, Set* end, int weight)
{
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->start = start;
    edge->end = end;
    edge->weight = weight;
    return edge;
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

void swapping( Edge* e1, Edge* e2 )
{
    Edge aux;
    aux = *e1;
    *e1 = *e2;
    *e2 = aux;
}

int Partition(Edge* edges[], int p_start, int p_end)
{
    Edge* x=edges[p_end];
    int i;
    //operations++;
    int index=p_start-1;
    for( i = p_start; i < p_end; i++)
    {
        //operations++;
        if( edges[i]->weight < x->weight )
    {
        index++;
        swapping(edges[i], edges[index]);
        //operations+=3;
    }
    }
    swapping(edges[p_end], edges[index+1]);
    //operations+=3;
    return index+1;

}

void QuickSort(Edge* edges[], int p_start, int p_end)
{
    int p;
    if( p_start < p_end)
    {
        p=Partition( edges, p_start, p_end);
        QuickSort(edges, p_start, p-1);
        QuickSort(edges, p+1, p_end);
    }

}

void Kruskal(Set* vertex[], Edge* edges[])
{
    Edge* MST[10001];
    int mstsize = 1;
    int cost = 0;
    int i;
    QuickSort(edges,1,nbOfEdges);
    for(i=1; i<=nbOfEdges && mstsize < nbOfEdges; i++)
    {
        if( findSet(edges[i]->start) != findSet(edges[i]->end) )
        {
            MST[mstsize++] = edges[i];
            unionSet(edges[i]->start, edges[i]->end);
            cost += edges[i]->weight;
        }
    }
    for( i=1; i<mstsize; i++)
    {
        cout<<"("<<MST[i]->start->value<<", "<<MST[i]->end->value<<")"<<endl;
    }
    cout<<"total cost: "<<cost;
}

void testKruskal()
{
    Set* vertex[7];
    Edge* edges[10];
    int i;
    nbOfNodes = 6;
    nbOfEdges = 8;
    for( i=1; i<=6; i++)
    {
        vertex[i] = makeSet(i);
    }
    edges[1] = makeEdge(vertex[1], vertex[2], 4);
    edges[2] = makeEdge(vertex[2], vertex[3], 6);
    edges[3] = makeEdge(vertex[3], vertex[4], 3);
    edges[4] = makeEdge(vertex[4], vertex[5], 2);
    edges[5] = makeEdge(vertex[5], vertex[6], 4);
    edges[6] = makeEdge(vertex[1], vertex[6], 2);
    edges[7] = makeEdge(vertex[2], vertex[6], 5);
    edges[8] = makeEdge(vertex[3], vertex[6], 1);
    cout<<endl<<"Kruskal's MST:"<<endl;
    Kruskal(vertex,edges);
}

void testSets()
{
    Set* sets[11];
    for( int i=1; i<=10; i++)
    {
        sets[i] = makeSet(i);
    }
    unionSet(sets[1],sets[2]);
    unionSet(sets[3],sets[4]);
    unionSet(sets[5],sets[7]);
    unionSet(sets[10],sets[7]);
    for( int i=1; i<=10; i++)
    {
        cout<<"value: "<<sets[i]->value<<" representative: "<<sets[i]->parent->value<<endl;
    }
}

void createRandomGraph( Set* vertex[], Edge* edges[])
{
    int i, j, cntp, randNodes[4], weight;
    operations = 0;
    for( i=1; i <= nbOfNodes; i++)
        {
             vertex[i] = makeSet(i);
        }
    for( i=1; i < nbOfNodes; i++)
        {
            weight = rand() % 50;
            edges[i] = makeEdge(vertex[i], vertex[i+1], weight);
        }
    cntp = nbOfNodes; // to keep track of the nb of edges
    for( i=1; i<= nbOfNodes && cntp <= nbOfEdges; i++ )
    {
        FillRandomArray(randNodes, 4, i+1, nbOfNodes, true, UNSORTED);
        for( j=0; j <= 3  && cntp <= nbOfEdges ; j++ )
        {
            weight = rand() % 50;
            edges[cntp++] = makeEdge(vertex[i], vertex[randNodes[j]], weight);
        }
    }
}

int main()
{
    Set* vertex[10001];
    Edge* edges[40001];
    int randNodes[4];
    int i, j, weight, cntp;
    srand(time(NULL));
//    for( nbOfNodes = 100; nbOfNodes <= 10000; nbOfNodes += 100)
//    {
//        nbOfEdges = nbOfNodes * 4;
//        createRandomGraph(vertex,edges);
//        Kruskal(vertex, edges);
//        profiler.countOperation("operations", nbOfNodes, operations);
//        cout<<nbOfNodes<<endl;
//    }
//    profiler.showReport();

   testSets();
   testKruskal();

}
