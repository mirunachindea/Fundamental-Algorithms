/*
    @Name: Chindea Miruna
    @Group: 30424
    Subject: Dynamic Order Statistics: Select and Delete
    Conclusions: The time complexity for this algorithm is O(nlogn),
    because we perform the selection and deletion (both O(logn)) n times.
*/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define NIL 9999999
#include "Profiler.h"
using namespace std;
int operations;
Profiler profiler ("OST");

typedef struct N
{
    int value;
    int n_size;
    struct N *pLeft;
    struct N *pRight;
} Node;

Node* BuildTree(int a[], int left, int right)
{
    if (left <= right)
    {
         Node *pNode = (Node*)malloc(sizeof(Node));
         int m = (left + right)/2;
         pNode->value = a[m];
         pNode->n_size = right-left+1;
         pNode->pLeft = BuildTree(a, left, m-1);
         pNode->pRight = BuildTree(a, m+1, right);
         return pNode;
    }
    else return NULL;
}

void showTree(Node *pRoot, int space)
{
    if (pRoot == NULL)
      {
          return;
      }
    space += 4;
    showTree(pRoot->pRight, space);
    printf("\n");
    for (int i = 1; i < space; i++)
       {
           printf(" ");
       }
    printf("%d\n", pRoot->value);
    showTree(pRoot->pLeft, space);
}

void showSize(Node *pRoot)
{
    if (pRoot == NULL)
     {
         return;
     }
    cout<<"size of node "<<pRoot->value<<" is: "<<pRoot->n_size<<endl;
    showSize(pRoot->pLeft);
    showSize(pRoot->pRight);
}

Node* OS_Select(Node *pRoot, int k)
{
    operations++;
    if (pRoot != NULL)
    {
        int n_rank;
        operations++;
        if (pRoot->pLeft !=NULL )
        {
            n_rank=pRoot->pLeft->n_size + 1;
            operations++;
        }
        else
        {
            n_rank = 1;
        }
        if ( k == n_rank )
        {
            return pRoot;
        }
        if ( n_rank > k )
        {
            return OS_Select(pRoot->pLeft, k);
        }
        return OS_Select(pRoot->pRight, k-n_rank);
    }
    if( k == 1)
    {
        return pRoot;
    }
}

Node* findTreeMin(Node *pRoot)
{
    while(pRoot->pLeft!=NULL)
    {
       operations+=2;
       pRoot=pRoot->pLeft;
    }
    operations++;
    return pRoot;
}

Node* findSuccessor(Node *pRoot)
{
    return findTreeMin(pRoot->pRight);
}

Node* searchNode(Node *pRoot, int value)
{
    operations++;
    if( pRoot == NULL || value == pRoot->value)
      {
          return pRoot;
      }
    else
        if ( value < pRoot->value )
    {
        operations++;
        searchNode(pRoot->pLeft, value);
    }
    else
    {
        operations++;
        searchNode(pRoot->pRight, value);
    }
}

Node* OS_Delete(Node *pRoot, Node *nodeToDelete )
{
    operations++;
    if ( pRoot == NULL )
      {
          return pRoot;
      }
    // if the key to be deleted < root's key, look in the left subtree
    operations++;
    if ( nodeToDelete->value < pRoot->value )
    {
        operations+=2;
        pRoot->n_size--;
        pRoot->pLeft = OS_Delete( pRoot->pLeft, nodeToDelete);
    }
    else
        // look in the right subtree
          if ( nodeToDelete->value > pRoot->value )
        {
            operations++;
            pRoot->n_size--;
            pRoot->pRight = OS_Delete( pRoot->pRight, nodeToDelete);
        }

    else
    {
        operations++;
        if ( pRoot->pLeft == NULL )
        {
            operations++;
            Node *temp = pRoot->pRight;
            free(pRoot);
            return temp;
        }
        else
          {
              operations++;
              if ( pRoot-> pRight == NULL)
            {
                operations++;
                Node *temp = pRoot->pLeft;
                free(pRoot);
                return temp;
            }
          }
        operations+=4;
        Node *temp = findSuccessor(pRoot);
        pRoot->value = temp->value;
        pRoot->pRight = OS_Delete(pRoot->pRight, temp);
        pRoot->n_size--;
    }
    return pRoot;
}

void test()
{
    int a[]={1,2,3,4,5,6,7,8,9,10,11};
    int n=11, x, i;
    Node* pRoot =  BuildTree(a,0,n-1);
    cout<<"INITIAL TREE: "<<endl;
    showTree(pRoot,0);
    showSize(pRoot);
    cout<<"---------------------------------------"<<endl;
    Node* nodeToDelete = OS_Select(pRoot,6);
    cout<<"Node to delete: "<<nodeToDelete->value;
    pRoot = OS_Delete(pRoot, nodeToDelete);
    showTree(pRoot,0);
    showSize(pRoot);
    cout<<"---------------------------------------"<<endl;
    nodeToDelete = OS_Select(pRoot,3);
    cout<<"Node to delete: "<<nodeToDelete->value;
    pRoot = OS_Delete(pRoot, nodeToDelete);
    showTree(pRoot,0);
    showSize(pRoot);
    cout<<"---------------------------------------"<<endl;
    nodeToDelete = OS_Select(pRoot,9);
    cout<<"Node to delete: "<<nodeToDelete->value;
    pRoot = OS_Delete(pRoot, nodeToDelete);
    showTree(pRoot,0);
    showSize(pRoot);


}

int main()
{
    srand(time(NULL));
//    int a[10001],b[10001], n, k, i;
//    for( k=0; k<=4; k++)
//    {
//        for( n=100; n<=10000; n+=100)
//        {
//            operations = 0;
//            FillRandomArray(a,n,1,n,true,1);
//            Node *pRoot = BuildTree(a,0,n-1);
//            int x=n;
//            cout<<n<<endl;
//            for( i=0; i<n-1; i++ )
//            {
//                int posToDelete = rand() % x + 1;
//                //cout<<posToDelete<<endl;
//                Node *nodeToDelete = OS_Select(pRoot,posToDelete);
//                pRoot=OS_Delete(pRoot, nodeToDelete);
//                x--;
//            }
//            pRoot=OS_Delete(pRoot, pRoot);
//            profiler.countOperation("total operations",n, operations);
//
//        }
//    }
//
//
//   profiler.divideValues("total operations",5);
//   profiler.showReport();
    test();

    return 0;
}
