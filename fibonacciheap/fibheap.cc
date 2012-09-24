#include <iostream.h>
#include <assert.h>
#include "fibheap.h"

FibHeap::FibHeap()
{
	numNodes = 0;
	minRoot = NULL;
}

FibHeap::~FibHeap()
{
	FHNode *p;

	while ((p = ExtractMin()) != NULL)	// delete all nodes
		delete p;
}

void FibHeap::Insert(FHNode *newNode)
{
	newNode->degree = 0;
	newNode->mark = FALSE;

	if (!minRoot)
		minRoot = newNode->left = newNode->right = newNode;
	else
	{
		newNode->left = minRoot;
		newNode->right = minRoot->right;

		newNode->right->left = newNode;
		newNode->left->right = newNode;

		if (*newNode < *minRoot)
			minRoot = newNode;
	}

	numNodes++;
}

void FibHeap::Union(FibHeap *otherFibHeap)
{
    FHNode *minRoot2, *otherFibHeapTail;
	FHNode *minRoot1, *FibHeapTail;

	minRoot1 = minRoot;
	minRoot2 = otherFibHeap->minRoot;

	FibHeapTail = minRoot1->left;
	otherFibHeapTail = minRoot2->left;

	FibHeapTail->right = minRoot2;
	minRoot2->left = FibHeapTail;

	otherFibHeapTail->right = minRoot1;
	minRoot1->left = otherFibHeapTail;

	if (*minRoot2 < *minRoot)
       	minRoot = minRoot2;

	numNodes += otherFibHeap->numNodes;

	otherFibHeap->minRoot = NULL;
	otherFibHeap->numNodes = 0;

	delete otherFibHeap;
}

FHNode *FibHeap::Minimum()
{
	return minRoot;
}

FHNode *FibHeap::ExtractMin()
{
	FHNode *z = minRoot;
	FHNode *x, *w, *stop;

	if (z != NULL)
	{
		w = stop = z->child;

		if (w != NULL)
		{
			do
			{
				x = w;
				w = w->right;
				x->parent = NULL;
				AddToRoot(x);

			} while (w != NULL && w != stop);
		}

		z->left->right = z->right;
		z->right->left = z->left;
		z->child = NULL;

		if (z == z->right)
			minRoot = NULL;
		else
		{
			minRoot = z->right;
			Consolidate();
		}
		numNodes--;
		z->degree = 0;

	} // if

	return z;
}

int FibHeap::DecreaseKey(FHNode *targetNode, itemType newKey)
{
	FHNode *theParent;

	if (targetNode==NULL || targetNode->item < newKey)
	    return FALSE;

	*targetNode = newKey;
	
	theParent = targetNode->parent;
	if (theParent != NULL && *targetNode < *theParent)
	{
		Cut(targetNode, theParent);
		CascadingCut(theParent);
	}
	
	if (*targetNode < *minRoot)
		minRoot = targetNode;

	return TRUE;
}

int FibHeap::Delete(FHNode *targetNode)
{
	int Result;

	if (targetNode == NULL) return FALSE;
	
	Result = DecreaseKey(targetNode, negInf);

	if (Result == TRUE)
		if (ExtractMin() == NULL)
			Result = FALSE;

	if (Result == TRUE)
		delete targetNode;

	return Result;
}

void FibHeap::Consolidate()
{
	FHNode *A[DN_N];
	FHNode *w, *x, *y, *tmp;
	int i, d;

	for (i = 0; i < DN_N; i++)
		A[i] = NULL;

	minRoot->left->right = NULL;
	minRoot->left = NULL;

	w = minRoot;
	do
	{
		x = w;
		w = w->right;
		d = x->degree;

		while (A[d] != NULL)
		{
			y = A[d];
			if (*y < *x)
			{
				tmp = x;
				x = y;
				y = tmp;
			}
			Link(y, x);
			A[d] = NULL;
			d++;

		} // while
		A[d] = x;

	} while (w != NULL); 

	minRoot = NULL;
	for (i = 0; i < DN_N; i++)
		if (A[i] != NULL)
		{
			// add A[i] to the root list of H
			AddToRoot(A[i]);
			if (minRoot == NULL || *A[i] < *minRoot)
				minRoot = A[i];
		}
}

void FibHeap::AddToRoot(FHNode *theNode)
{
	if (minRoot == NULL)
	{
		theNode->left = theNode->right = theNode;
		minRoot = theNode;
	}
	else
	{
		theNode->left = minRoot;
		theNode->right = minRoot->right;

		theNode->left->right = theNode;
		theNode->right->left = theNode;
	}
	theNode->parent = NULL;
}

void FibHeap::Link(FHNode *srcNode, FHNode *destNode)
{
	if (srcNode == NULL || destNode == NULL)
		return;

	// 루트 리스트에서 srcNode를 제거한다.
	if (srcNode->right != NULL)
		srcNode->right->left = srcNode->left;
	if (srcNode->left != NULL)
		srcNode->left->right = srcNode->right;

	srcNode->left = srcNode->right = srcNode;

	// y를 x의 차일드로 만든다.
	srcNode->parent = destNode;

	if (destNode->child != NULL)
	{
		FHNode *p = destNode->child;

		srcNode->right = p;
		srcNode->left = p->left;

		srcNode->left->right = srcNode;
		srcNode->right->left = srcNode;

	}
	else
		destNode->child = srcNode;

	destNode->degree++;
	srcNode->mark = FALSE;
}

void FibHeap::Print()
{
	FHNode *p, *stop;

	p = stop = minRoot;

	if (p != NULL)
		do
		{
			cout << *p;
			if (p->child)
				cout << ": CHILD";
			cout << endl;

			p = p->right;
		} while (p != NULL && p != stop);
}

void FibHeap::Cut(FHNode *srcNode, FHNode *destNode)
{
	if (destNode->child == srcNode)
	    destNode->child = srcNode->right;
	if (destNode == srcNode)
	    destNode->child = NULL;

	destNode->degree --;

	srcNode->left->right = srcNode->right;
	srcNode->right->left = srcNode->left;
	
	AddToRoot(srcNode);
}

void FibHeap::CascadingCut(FHNode *destNode)
{
	FHNode *ParNode = destNode->parent;

	while (ParNode != NULL)
	{
		if (destNode->mark == 0)
		{
			destNode->mark = 1;
			ParNode = NULL;
		}
		else
		{
			Cut(destNode, ParNode);
			destNode = ParNode;
			ParNode = destNode->parent;
		}
	}
}
 
