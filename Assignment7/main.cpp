/*
    @Student: Chindea Miruna
    @Group: 30424
    Subject: Multi-way Trees
    Conclusions:
*/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define NIL 9999999
using namespace std;

int count[15]={0};

struct NodeV2
{
    int value;
    struct NodeV2* children[10];
};

struct NodeV3
{
    int value;
    struct NodeV3* left_child;
    struct NodeV3* right_sibling;
}Node3;

void addChildren( NodeV2* v2, NodeV3* v3 )
{
    NodeV3* current = (NodeV3*)malloc(sizeof(NodeV3));
    if( count[v2->value] != 0)
    {
        v3->left_child = (NodeV3*)malloc(sizeof(NodeV3));
        v3->left_child->value = v2->children[0]->value;
        v3->left_child->left_child = NULL;
        v3->left_child->right_sibling = NULL;
        current = v3->left_child;
        addChildren(v2->children[0], v3->left_child);
        for( int i=1; i < count[v2->value]; i++ )
        {
            current->right_sibling = (NodeV3*)malloc(sizeof(NodeV3));
            current->right_sibling->value = v2->children[i]->value;
            current->right_sibling->left_child = NULL;
            current->right_sibling->right_sibling = NULL;
            addChildren( v2->children[i], current->right_sibling);
            current = current->right_sibling;
        }
    }
}

NodeV3* transform( NodeV2* root)
{
    NodeV3* current = (NodeV3*)malloc(sizeof(NodeV3));
    current->value = root->value;
    addChildren(root, current);
    return current;
}

void showTree(NodeV3 *pRoot, int space, int r)
{
    if ( pRoot == NULL )
        {
          return;
        }

    if( r == 0 )
        {
            space += 3;
        }
    showTree(pRoot->right_sibling, space, 1);
    printf("\n");
    for ( int i = 1; i < space; i++ )
        {
           printf(" ");
        }

    printf("%d\n", pRoot->value);
    showTree(pRoot->left_child, space, 0);

}

void showTree2(NodeV3 *pRoot, int space)
{
    if ( pRoot == NULL )
        {
          return;
        }

    space += 3;

    showTree2(pRoot->right_sibling, space);
    printf("\n");
    for ( int i = 1; i < space; i++ )
        {
           printf(" ");
        }

    printf("%d\n", pRoot->value);
    showTree2(pRoot->left_child, space);

}
int main()
{
    int input[] = {NULL, 2, 7, 5, 2, 7, 7, -1, 5, 2};
    int  i, n = 9;
    NodeV2* Nodes[15];
    NodeV2* pRoot2;
    NodeV3* pRoot3;
    for ( i=1; i <= 9; i++ )
    {
        NodeV2 *pNode = (NodeV2*)malloc(sizeof(NodeV2));
        pNode->value = i;
        Nodes[i] = pNode;
    }
    for( i=1; i <= 9; i++ )
    {
        if( input[i] == -1)
        {
            pRoot2 = Nodes[i];
        }
        else
        {
            int ctnode = input[i];
            Nodes[ctnode]->children[count[ctnode]] = Nodes[i];
            count[ctnode]++;
        }

    }

    pRoot3 = transform(pRoot2);
    showTree(pRoot3, 0, 0);
    cout<<"----------------------";
    showTree2(pRoot3,0);
    return 0;
}
