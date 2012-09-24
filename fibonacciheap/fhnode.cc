#include <iostream.h>
#include "fibheap.h"

FHNode::FHNode()
{
    left = right = this;
    parent = child = NULL;
    degree = 0;
    mark = negInfinity = FALSE;
    item = 0;
}

FHNode::FHNode(int newItem)
{
    left = right = this;
    parent = child = NULL;
    degree = 0;
    mark = negInfinity = FALSE;
    item = newItem;
}

FHNode::~FHNode()
{
}

FHNode &FHNode::operator=(int newItem)
{
    if (newItem == negInf)
	negInfinity = TRUE;
    else
    {
	negInfinity = FALSE;
	item = newItem;
    }

    return *this;
}

int FHNode::operator==(const FHNode &rfhn)
{
    if (negInfinity && rfhn.negInfinity)
    {
        cerr << "Fatal error: Comparision between negInf." << endl;
        exit(1);
    }

    if (negInfinity || rfhn.negInfinity)
		return FALSE;
    else
		return (item == rfhn.item) ? TRUE : FALSE;
}

int FHNode::operator<(const FHNode &rfhn)
{
    if (negInfinity && rfhn.negInfinity)
    {
        cerr << "Fatal error: Comparision between negInf." << endl;
        exit(1);
    }

    if (negInfinity)
		return TRUE;
    else
		if (rfhn.negInfinity)
            return FALSE;
        else
            return (item < rfhn.item) ? TRUE : FALSE;
}

ostream &operator<<(ostream &os, const FHNode &rfhn)
{
    if (rfhn.negInfinity)
	os << "negInf";
    else
        os << rfhn.item;

    return os;
}

FHNode::operator int()
{
    return item;
}

