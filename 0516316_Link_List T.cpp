#include "0516316_Link_List.h"
#include<iostream>

template <typename T>
Link_List<T>::Link_List(const Link_List<T> &v)
{
    size=v.getSize();
    head=new Int_Node<T>;
    Int_Node<T> *p=v.head;
    T *a=new T[size];
    for(int i=0;i<size;i++)
    {
        a[i]=p->value;
        p=p->next;
    }
    p=head;
    p->value=a[0];
    p->prev=NULL;
    for(int i=1;i<size;i++)
    {
        Int_Node<T> *q=new Int_Node<T>;
        q->value=a[i];
        p->next=q;
        q->prev=p;
        p=p->next;
    }
    tail=p;
    tail->next=NULL;
    delete a;
}

template <typename T>
Link_List<T>::~Link_List()
{
    Int_Node<T> *n=head;
    if(size==1)
        delete n;
    else
    {
        while(n->next!=NULL)
        {
            n=n->next;
            delete n->prev;
        }
        delete n;
    }
    size=0;
}
template <typename T>
const Link_List<T> &Link_List<T>::operator=(const Link_List<T> &v)
{
    Int_Node<T> *p=head,*pp;
    while(p!=NULL)
    {
        pp=p;
        p=p->next;
        delete pp;
    }
    size=v.getSize();
    head=new Int_Node<T>;
    p=v.head;
    T *a=new T[size];
    for(int i=0;i<size;i++)
    {
        a[i]=p->value;
        p=p->next;
    }
    p=head;
    p->value=a[0];
    p->prev=NULL;
    for(int i=1;i<size;i++)
    {
        Int_Node<T> *q=new Int_Node<T>;
        q->value=a[i];
        p->next=q;
        q->prev=p;
        p=p->next;
    }
    tail=p;
    tail->next=NULL;
    delete a;

}
template <class T>
int Link_List<T>::getSize() const
{
    return this->size;
}
template <typename T>
bool Link_List<T>::operator==(const Link_List<T> &v) const
{
    Int_Node<T> *n=head;
    Int_Node<T> *m=v.head;
    while(n->next!=NULL)
    {
        if(n->value!=m->value)
            return 0;
        n=n->next;
        m=m->next;
    }
    if(m->next==NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

template <typename T>
T Link_List<T>::operator[](int num) const
{
    Int_Node<T> *n=head;
    while(num--)
        n=n->next;
    return n->value;
}

template <typename T>
T &Link_List<T>::operator[](int num)
{
    Int_Node<T> *n=head;
    while(num--)
        n=n->next;

    return n->value;
}

template <typename T>
bool Link_List<T>::insert_node(T num)
{
    size++;
    Int_Node<T> *n=new Int_Node<T>;
    tail->next = n;
    n->value=num;
    n->next=NULL;
    n->prev=tail;
    tail=n;
    return true;
}

template <typename T>
bool Link_List<T>::delete_node()
{
    size--;
    Int_Node<T> *n=tail;
    Int_Node<T> *m=n;
    n=n->prev;
    tail=n;
    tail->next=NULL;
    delete m;
    return true;
}

template <typename T>
bool Link_List<T>::insert_node(int nth, T num)
{
    Int_Node<T> *n=head;
    for(int i=1;i<nth;i++)
    {
        n=n->next;
    }
    Int_Node<T> *m=n;
    m=m->next;
    Int_Node<T> *add=new Int_Node<T>;
    add->value=num;
    add->next=m;
    m->prev=n;
    n->next=add;
    add->prev=n;
    size++;
    return true;
}

template <typename T>
bool Link_List<T>::delete_node(int nth)
{
    Int_Node<T> *n=head;
    for(int i=1;i<nth;i++)
    {
        n=n->next;
    }
    Int_Node<T> *m,*o=n;
    n=n->next;
    m=o->prev;
    delete o;
    n->prev=m;
    m->next=n;
    size--;
    return true;
}
