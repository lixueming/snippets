// fibheap.h - fibonacci heap header

#ifndef __FIBHEAP_H
#define __FIBHEAP_H

#include <iostream.h>
#include <limits.h>

enum BOOLEAN {FALSE, TRUE};

const int negInf = INT_MIN;
const int DN_N = 64;	// if (ln(n) == 64) then n == 2^64

typedef int itemType;

class FibHeap;

class FHNode
{
    friend class FibHeap;

protected:
    FHNode *left, *right, *parent, *child;
    int degree;
    int mark;
    int negInfinity;
    itemType item;

public:
    FHNode();
    FHNode(int newItem);
    ~FHNode();

    FHNode &operator=(int newItem);
    int operator==(const FHNode &rfhn);
    int operator<(const FHNode &rfhn);
    friend ostream &operator<<(ostream &os, const FHNode &rfhn);

    operator int();
};

class FibHeap
{
protected:
    FHNode *minRoot;
    int numNodes;

    void Consolidate();
    void Link(FHNode *srcNode, FHNode *destNode);
    void Cut(FHNode *srcNode, FHNode *destNode);
    void CascadingCut(FHNode *destNode);
	void AddToRoot(FHNode *theNode);

public:
    FibHeap();
    ~FibHeap();

    void Insert(FHNode *newNode);
    void Union(FibHeap *otherFibHeap);

    FHNode *Minimum();
    FHNode *ExtractMin();

    int DecreaseKey(FHNode *targetNode, itemType newKey);
    int Delete(FHNode *targetNode);

    void Print(void);
};

#endif  // fibheap.h
