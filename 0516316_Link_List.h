#ifndef LINK_LIST
#define LINK_LIST


#include <iostream>
using namespace std;

struct Int_Node
{
	int value;
	Int_Node *prev, *next;
};

class Link_List
{
	friend ostream &operator<<(ostream &, const Link_List &);
	friend istream &operator>>(istream &, Link_List &);

public:
	Link_List(int =10)
	{
	    size=1;
	    tail=head=new Int_Node;
	    head->value=10;
	    head->next=NULL;
	    head->prev=NULL;
	}			//default constructor
	Link_List(const Link_List &);	// copy constructor
	~Link_List()
	{
        Int_Node *p,*q=new Int_Node;
        p=head;
        while(p->next!=NULL)
        {
            q=p;
            p=p->next;
            delete q;
        }
        delete p;
	}
	int getSize() const;

	void operator=(const Link_List &v);
	// assignment operator
	bool operator==(const Link_List &) const;			// equality operator
	bool operator!=(const Link_List &right) const		// inequality operator
	{
		return !(*this == right);
	}		// inequality operator

	int &operator[](int);								// subscript operator for non-const objects
	int operator[](int) const;							// subscript operator for const objects

	bool insert_node(int);								// insert an integer at the back of link list
	bool delete_node();									// delete the last node
	bool insert_node(int , int);						// insert an integer after the i_th position
	bool delete_node(int);								// delete the i_th node

private:
	int size;
	Int_Node *head, *tail;								// pointer to the first and the last element of Link_List
};


#endif // LINK_LIST
