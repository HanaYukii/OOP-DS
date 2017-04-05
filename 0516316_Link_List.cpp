#include "0516316_Link_List.h"
#include<iostream>
ostream &operator<<(ostream &it, const Link_List &v)
{
    it<<"NULL"<<"<->";
    Int_Node *n = v.head;
    while(n!= NULL)
    {

        it<< n->value<<"<->";
        n=n->next;
    }
    it<<"NULL";
    return it;
}
istream &operator>>(istream &it, Link_List &v)
{
    int a;
    it >> a;
    v.insert_node(a);
    return it;
}
Link_List::Link_List(const Link_List &v)
{
    size=v.getSize();
    head=new Int_Node;
    Int_Node *p=v.head;
    int *a=new int[size];
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
        Int_Node *q=new Int_Node;
        q->value=a[i];
        p->next=q;
        q->prev=p;
        p=p->next;
    }
    tail=p;
    tail->next=NULL;
    delete a;
}

void Link_List::operator=(const Link_List &v)
{
    Int_Node *p=head,*pp;
    while(p!=NULL)
    {
        pp=p;
        p=p->next;
        delete pp;
    }
    size=v.getSize();
    head=new Int_Node;
    p=v.head;
    int *a=new int[size];
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
        Int_Node *q=new Int_Node;
        q->value=a[i];
        p->next=q;
        q->prev=p;
        p=p->next;
    }
    tail=p;
    tail->next=NULL;
    delete a;

}
int Link_List::getSize() const
{
    return this->size;
}
bool Link_List::operator==(const Link_List &v) const
{
    Int_Node *n=head;
    Int_Node *m=v.head;
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

int Link_List::operator[](int num) const
{
    Int_Node *n=head;
    while(num--)
        n=n->next;
    return n->value;
}
int &Link_List::operator[](int num)
{
    Int_Node *n=head;
    while(num--)
        n=n->next;

    return n->value;
}
bool Link_List::insert_node(int num)
{
    size++;
    Int_Node *n=new Int_Node;
    tail->next = n;
    n->value=num;
    n->next=NULL;
    n->prev=tail;
    tail=n;
    return true;
}
bool Link_List::delete_node()
{
    size--;
    Int_Node *n=tail;
    Int_Node *m=n;
    n=n->prev;
    tail=n;
    tail->next=NULL;
    delete m;
    return true;
}
bool Link_List::insert_node(int nth, int num)
{
    Int_Node *n=head;
    for(int i=1;i<nth;i++)
    {
        n=n->next;
    }
    Int_Node *m=n;
    m=m->next;
    Int_Node *add=new Int_Node;
    add->value=num;
    add->next=m;
    m->prev=n;
    n->next=add;
    add->prev=n;
    size++;
    return true;
}
bool Link_List::delete_node(int nth)
{
    Int_Node *n=head;
    for(int i=1;i<nth;i++)
    {
        n=n->next;
    }
    Int_Node *m,*o=n;
    n=n->next;
    m=o->prev;
    delete o;
    n->prev=m;
    m->next=n;
    size--;
    return true;
}
