// bintree.cc - Binary Tree Class

#include <iostream.h>
#include "bintree.h"

BinTree::BinTree()
{
    root = NULL;
}

BinTree::~BinTree()
{
    RecursiveDelete(root);	// 할당됐던 모든 node를 delete 한다.
}

void BinTree::Print()
{
    RecursivePrint(root);	// inorder로 node를 출력한다. (재귀적)
    cout << '\n';
}

void BinTree::RecursiveDelete(node *p)
{
    if (p)
    {
        RecursiveDelete(p->leftChild);
        RecursiveDelete(p->rightChild);
        delete p;
    }
}

void BinTree::RecursivePrint(node *p)
{
    if (p)
    {
        RecursivePrint(p->leftChild);
        cout << p->data << '\t';
        RecursivePrint(p->rightChild);
    }
}

int BinTree::Search(DataType key)
{
    node *p = root;

    while (p && p->data != key)
        p = (key < p->data) ? p->leftChild : p->rightChild;

    // p가 null일 경우 0을 리턴한다.
    // p가 null 인 경우 : node가 하나도 없을 때
    //		          key 값이 없을 때
    return (p) ? 1 : 0;
}

DataType BinTree::Minimum()
{
    node *p = root;

    while (p && p->leftChild)
        p = p->leftChild;

    // p가 null일 경우 0을 리턴한다.
    // p가 null 인 경우 : node가 하나도 없을 때
    return (p) ? p->data : 0;
}

DataType BinTree::Maximum()
{
    node *p = root;

    while (p && p->rightChild)
        p = p->rightChild;

    // p가 null일 경우 0을 리턴한다.
    // p가 null 인 경우 : node가 하나도 없을 때
    return (p) ? p->data : 0;
}

void BinTree::Insert(DataType key)
{
    node *t = new node;     // 새로 만들어 지는 node 포인터 
    node *p = root;
    node *parent = NULL;
    int direction;

    if (Search(key))	// binary tree는 같은 값을 갖는 node가 없어야
        return;		// 한다.

    t->data = key;
    t->leftChild = t->rightChild = NULL;
    
    // 새 node가 삽입될 위치를 찾고, 그것의 부모 node를 parent에
    // 넣는다.
    while (p)
    {
       parent = p;
       
       if (key < p->data)
       {
           direction = 1;
           p = p->leftChild;
       }
       else
       {
           direction = 0;
           p = p->rightChild;
       }
    }

    // 기존 node가 없으면 새 node를 root로 만들고, 아니면 새 node의
    // 부모 node가 새 node를 가르키게 한다.
    if (!parent)
        root = t;
    else
        if (direction)
            parent->leftChild = t;
        else
            parent->rightChild = t;
}

int BinTree::Delete(DataType key)
{
    node *p = root;
    node *parent = NULL;
    node *realDeleteNode = NULL;
    node *parentOfRealDeleteNode = NULL;
    node *childOfRealDeleteNode = NULL;

    // key 값에 맞는 삭제될 node를 찾는다.
    while (p && p->data != key)
    {
        parent = p;
        p = (key < p->data) ? p->leftChild : p->rightChild;
    }

    if (!p)     // key 값에 맞는 node가 없으면 함수 종료
        return 0;

    // 실제로 지워질(delete) node를 찾는다.
    if (!(p->leftChild && p->rightChild))
    {
        parentOfRealDeleteNode = parent;
        realDeleteNode = p;
    }
    else
        // 자식이 둘인 경우 오른쪽 자식 트리의 최소값이 실제 지워질
        // node다.
        for (parentOfRealDeleteNode = p, realDeleteNode = p->rightChild;
            realDeleteNode->leftChild;
            parentOfRealDeleteNode = realDeleteNode,
            realDeleteNode = realDeleteNode->leftChild)
            ;

    // 실제 지워질 노드의 자식 노드를 보관한다.
    if (realDeleteNode->leftChild)
        childOfRealDeleteNode = realDeleteNode->leftChild;
    else
        childOfRealDeleteNode = realDeleteNode->rightChild;

    // 실제 지워질 노드의 부모가 실제 지워질 노드의 자식을 가르키게
    // 한다. 실제 지워질 노드의 부모가 없으면 실제 지워질 노드의 자식
    // 을 root로 한다.
    if (!parentOfRealDeleteNode)
        root = childOfRealDeleteNode;
    else
        if (realDeleteNode == parentOfRealDeleteNode->leftChild)
            parentOfRealDeleteNode->leftChild = childOfRealDeleteNode;
        else
            parentOfRealDeleteNode->rightChild = childOfRealDeleteNode;

    // 데이터 값을 복사해서 key 값을 지닌 노드가 지워지는 효과를 얻는다.
    if (realDeleteNode != p)
        p->data = realDeleteNode->data;

    delete realDeleteNode;

    return 1;
}
