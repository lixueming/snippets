// bintree.h - binary tree 헤더 파일

#ifndef __BINTREE_H
#define __BINTREE_H

typedef int DataType;

class BinTree
{
protected:
    struct node
    {
        DataType data;
        struct node *leftChild, *rightChild;
    };

    node *root;

    void RecursiveDelete(node *p);
    void RecursivePrint(node *p);

public:
    BinTree();

    virtual ~BinTree();

    virtual void Print();
    virtual int Search(DataType key);
    virtual DataType Minimum();
    virtual DataType Maximum();
    virtual void Insert(DataType key);
    virtual int Delete(DataType key);
};

#endif  /* bintree.h */
