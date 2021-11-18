#ifndef linklist_h
#define linklist_h

#include <iostream>
using namespace std;

template <class elemtype>
class linkList
{
private:
    struct node
    {
        elemtype data;
        node *next;
        node(const elemtype &x, node *n = NULL)
        {
            data = x;
            next = n;
        }
        node() : next(NULL) {}
        ~node() {}
    };
    node *head;

public:
    linkList();
    ~linkList();
    void clear();
    void insert(int i, const elemtype &x);
    void remove(int i);
    int length() const;
    int search(const elemtype &x) const;
    elemtype visit(int i) const;
    void traverse() const;
    void quick_insert(elemtype a[], int n);
    void reverse();
};

template <class elemtype>
linkList<elemtype>::linkList()
{
    head = new node();
}

template <class elemtype>
void linkList<elemtype>::clear()
{
    node *p = head->next;
    node *q;
    head->next = NULL;
    while (p != NULL)
    {
        q = p->next;
        delete p;
        p = q;
    }
}

template <class elemtype>
linkList<elemtype>::~linkList()
{
    clear();
    delete head;
}

template <class elemtype>
void linkList<elemtype>::insert(int i, const elemtype &x)
{
    if (i < 0)
        return;
    node *p = head;
    for (int j = 0; j < i && p; ++j)
        p = p->next;
    if (!p)
        return;
    p->next = new node(x, p->next);
}

template <class elemtype>
void linkList<elemtype>::remove(int i)
{
    if (i < 0)
        return;
    node *p = head;
    for (int j = 0; j < i && p; ++j)
        p = p->next;
    if (!p || !p->next)
        return;
    node *q = p->next;
    p->next = p->next->next;
    delete q;
}

template <class elemtype>
int linkList<elemtype>::length() const
{
    node *p = head->next;
    int i = 0;
    while (p)
    {
        p = p->next;
        i++;
    }
    return i;
}

template <class elemtype>
int linkList<elemtype>::search(const elemtype &x) const
{
    node *p = head->next;
    int j = 0;
    while (p != NULL)
    {
        if (p->data == x)
            return j;
        j++;
        p = p->next;
    }
    if(p==NULL)
        return -1;
}

template <class elemtype>
elemtype linkList<elemtype>::visit(int i) const
{
    node *p = head->next;
    for (int j = 0; j < i && p; ++j)
        p = p->next;
    if (!p)
        exit(-1);
    return p->data;
}

template <class elemtype>
void linkList<elemtype>::traverse() const
{
    node *p = head->next;
    while (p)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

template <class elemtype>
void linkList<elemtype>::quick_insert(elemtype a[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        head->next = new node(a[i], head->next);
    }
}

template <class elemtype>
void linkList<elemtype>::reverse()
{
    node *p = head->next;
    node *q;
    head->next = NULL;
    while (p)
    {
        q = p->next;
        p->next = head->next;
        head->next = p;
        p = q;
    }
}

#endif // linklist_h
