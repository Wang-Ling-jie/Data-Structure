#ifndef seqlist_h
#define seqlist_h

#include <iostream>
using namespace std;

template <class elemtype>
class seqList
{
private:
    elemtype *data;
    int currentLength;
    int maxSize;
    void doublespace();

public:
    seqList(int initSize = 10);
    ~seqList();
    void clear();
    int length() const;
    void insert(int i, const elemtype &x);
    void remove(int i);
    int search(const elemtype &x) const;
    elemtype visit(int i) const;
    void traverse() const;
};

template <class elemtype>
seqList<elemtype>::seqList(int initSize)
{
    maxSize = initSize;
    currentLength = 0;
    data = new elemtype[maxSize];
}

template <class elemtype>
seqList<elemtype>::~seqList()
{
    delete[] data;
}

template <class elemtype>
void seqList<elemtype>::clear()
{
    currentLength = 0;
}

template <class elemtype>
int seqList<elemtype>::length() const
{
    return currentLength;
}

template <class elemtype>
void seqList<elemtype>::insert(int i, const elemtype &x)
{
    if (i > currentLength)
        return;
    for (int j = currentLength; j > i; --j)
        data[j] = data[j - 1];
    data[i] = x;
    currentLength++;
}

template <class elemtype>
void seqList<elemtype>::remove(int i)
{
    if (i >= currentLength)
        return;
    for (int j = i; j < currentLength - 1; ++j)
        data[j] = data[j + 1];
    currentLength--;
}

template <class elemtype>
int seqList<elemtype>::search(const elemtype &x) const
{
    for (int i = 0; i < currentLength; ++i)
    {
        if (data[i] == x)
            return i;
    }
    return -1;
}

template <class elemtype>
elemtype seqList<elemtype>::visit(int i) const
{
    if (i >= currentLength)
        exit(-1);
    return data[i];
}

template <class elemtype>
void seqList<elemtype>::traverse() const
{
    for (int i = 0; i < currentLength; ++i)
        cout << data[i] << ' ';
    cout << endl;
}

#endif // seqlist_h
