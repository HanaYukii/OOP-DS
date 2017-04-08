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
    Link_List(T n=10)
    {
        size=1;
        tail=head=new Int_Node<T>;
        head->value=n;
        head->next=NULL;
        head->prev=NULL;
    }			//default constructor
    Link_List(const Link_List<T> &);	// copy constructor
    ~Link_List();
    int getSize() const;

    const Link_List<T> &operator=(const Link_List<T> &);
    // assignment operator
    bool operator==(const Link_List<T> &) const;			// equality operator
    bool operator!=(const Link_List<T> &right) const		// inequality operator
    {
        return !(*this == right);
    }		// inequality operator

    T &operator[](int);								// subscript operator for non-const objects
    T operator[](int) const;							// subscript operator for const objects

    bool insert_node(T);								// insert an integer at the back of link list
    bool delete_node();									// delete the last node
    bool insert_node(int, T);						// insert an integer after the i_th position
    bool delete_node(int);								// delete the i_th node

private:
    int size;
    Int_Node<T> *head, *tail;								// pointer to the first and the last element of Link_List
};


#endif // LINK_LIST
