#ifndef LINK_LIST
#define LINK_LIST


#include <iostream>
using namespace std;
template <typename T>
struct Int_Node
{
    T value;
    Int_Node<T> *prev, *next;
};
template <typename T>
class Link_List
{
    friend ostream &operator<<(ostream &it,const Link_List<T> &v)
    {
        it<<"NULL"<<"<->";
        Int_Node<T> *n = v.head;
        while(n!= NULL)
        {

            it<< n->value<<"<->";
            n=n->next;
        }
        it<<"NULL";
        return it;
    }
    friend istream &operator>>(istream &it,Link_List<T> &v)
    {
        T a;
        it >> a;
        v.insert_node(a);
        return it;
    }

public:
    Link_List<T>(T n=10)
    {
        size=1;
        tail=head=new Int_Node<T>;
        head->value=n;
        head->next=NULL;
        head->prev=NULL;
    }			//default constructor
    Link_List<T>(const Link_List<T> &v)
    {
        size=v.getSize();
        head=new Int_Node<T>;
        Int_Node<T> *p=v.head;
        T *a=new T[size];
        for(int i=0; i<size; i++)
        {
            a[i]=p->value;
            p=p->next;
        }
        p=head;
        p->value=a[0];
        p->prev=NULL;
        for(int i=1; i<size; i++)
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
    // copy constructor
    ~Link_List()
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
    int getSize() const
    {
        return this->size;
    }

    const Link_List<T> &operator=(const Link_List<T> &v)
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
        for(int i=0; i<size; i++)
        {
            a[i]=p->value;
            p=p->next;
        }
        p=head;
        p->value=a[0];
        p->prev=NULL;
        for(int i=1; i<size; i++)
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
    // assignment operator
    bool operator==(const Link_List<T> &v) const
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
    // equality operator
    bool operator!=(const Link_List<T> &right) const		// inequality operator
    {
        return !(*this == right);
    }		// inequality operator

    T &operator[](int num)
    {
        Int_Node<T> *n=head;
        while(num--)
            n=n->next;

        return n->value;
    }
    // subscript operator for non-const objects
    T operator[](int num) const
    {
        Int_Node<T> *n=head;
        while(num--)
            n=n->next;

        return n->value;
    }							// subscript operator for const objects

    bool insert_node(T num)
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
    // insert an integer at the back of link list
    bool delete_node()
    {
        size--;
        Int_Node<T> *n=tail;
        Int_Node<T> *m=n;
        n=n->prev;
        tail=n;
        tail->next=NULL;
        delete m;
        return true;
    }									// delete the last node
    bool insert_node(int nth, T num)
    {
        Int_Node<T> *n=head;
        for(int i=1; i<nth; i++)
        {
            n=n->next;
        }
        Int_Node<T> *m=n;
        m=m->next;
        Int_Node<T> *add=new Int_Node<T>;
        add->value=num;
        add->next=m;
        m->prev=add;
        n->next=add;
        add->prev=n;
        size++;
        return true;
    }
    // insert an integer after the i_th position
    bool delete_node(int nth)
    {
        Int_Node<T> *n=head;
        for(int i=1; i<nth; i++)
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
    // delete the i_th node

private:
    int size;
    Int_Node<T> *head, *tail;								// pointer to the first and the last element of Link_List
};


#endif // LINK_LIST
