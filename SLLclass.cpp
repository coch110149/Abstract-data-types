/*
Name: Clinton Cochrane
	Date : 11/01/2015
	Assignment: ASN4
	Platfrom / IDE : Windowns 10 / VS15

	Description :
Templete class for singely linked list. Also sorts list based.
*/

#include <iostream>				//Used for outputting to the console window
#include <time.h>				//Used for random number generator seeding

using std::ostream;
template <typename E> class SLinkedList;
template <typename E>
ostream& operator << (ostream& out, const SLinkedList<E>& v);

template <typename E>
class Node							// node class to be used by Singly Linked List
{
public:
	Node();							//default constructor
	Node(const Node<E>& obj);		//copy constructor
private:
	E elem;							// linked list element value
	Node<E>* next;					// next item in the list

template <typename E>
friend class SLinkedList;			// provide SLinkedList access
friend ostream& operator << <E> (ostream& out, const SLinkedList <E>& v);
};

template <typename E>
Node<E>::Node()						// default constructor
{	
	elem = NULL;					
	next = nullptr;
}

template <typename E>
Node<E>::Node(const Node<E>& obj)	//Copy constructor
{
	elem = obj->elem;
	next = obj->next;
}


template <typename E>
class SLinkedList							//A singly linked list class
{
public:
	SLinkedList();							//Empty list contructor
	SLinkedList(SLinkedList<E> &obj);		//Copy constructor
	~SLinkedList();							//Desctrutor

	/*====setters====*/	
	void removeFront();						//Remove front item from the list
	void insertionSort();					//Sorts the list based on the insertion sort algorithm
	void addFront(const E& e);				//Add e (a refference to the E) to front of list
	void swap(Node<E>* n1, Node<E>* n2);	//Swaps the place of n1 and n2. Both adjacent nodes in the list

	/*====getters=====*/
	int size() const;						//returns sllSize
	bool empty() const;						//Is the list empty?
	Node<E>& front() const;					//Return front element
	void printDetails() const;				//Prints extra details about the list. Used for debugging
	Node <E>* retrieve(const int index) const;	//returns the address of the node at element index
	

	/*====overloads====*/
	friend ostream& operator << <E> (ostream& out, const SLinkedList <E>& v);	//overload output
	E& operator [] (const int index);
private:
	Node <E>* head;							//pointer to the head of the list
	int sllSize;							//size of the list
};

template <typename E>						
SLinkedList<E>::SLinkedList()				//default constructor
{
	head = nullptr;
	sllSize = 0;
}

template<typename E>
SLinkedList<E>::SLinkedList(SLinkedList<E>& obj)		//copy constructor
{
	Node<E>* curr = obj.head;
	Node<E>* v = new Node <E>;			//creates a new node
	v->elem = obj.head->elem;			//assign v's element to the old SLL's head element
	Node<E>* nu = new Node<E>;			//create a new node
	v->next = nu;						//set v's next to the new node
	head = v;							//set head to v [value of old head]-->[nu]
	v = head;							//set v head. Saves head from being overwritten
	curr = curr->next;					//advance curr so the head element is not written to the new list twice
	while (curr != nullptr)				//if true we have reached passed the tail
	{
		nu->elem = curr->elem;			//set nu's element to the curr element
		nu->next = new Node<E>;			//set nu's next a new empty node
		nu = nu->next;					//advance nu
		curr = curr->next;				//advance curr
		v = v->next;					//advance v
		sllSize++;						//increment 

	}

	v->next = nullptr;					//set v's next element to nullptr after the loop exits
}

template <typename E>
SLinkedList <E>::~SLinkedList()			//destructor
{
	while (!empty())
		removeFront();		//if the list is not empty then destory it.
}

/*=======setters========*/
template <typename E>
void SLinkedList <E>::removeFront()
{
	Node <E>* old = head;				//save current head
	head = old->next;					//skip over the old head
	delete old;							//delete old head
	sllSize--;
}

template <typename E>
void SLinkedList<E>::insertionSort()	//Sorts the list based on the insertion sort algorithm
{
	for (int i = 1; i < sllSize; i++)	//insertion loop
	{
		E curr = (*this)[i];			//current character to insert
		int	j = (i - 1);				//j = previous element
		while ((j >= 0) && ((*this)[j] > curr)) //while [j] is out of order
		{
			swap(retrieve(j), retrieve(j + 1));	//move [j] to right
			j = j - 1;					//decrement j
		}
	}
}

template <typename E>
void SLinkedList <E>::addFront(const E& e)	//Add e (a refference to the E) to front of list
{
	Node<E>* v = new Node <E>;				//creates a new node
	v->elem = e;							//set new node's element to e
	v->next = head;							//set new node's next to the current head
	head = v;								//set the head to the new node
	sllSize++;								//increment
}

template <typename E>
void SLinkedList<E>::swap(Node<E>* n1, Node<E>* n2)
//swaps two adjacent nodes. N1 is before n2
{
	if (n1 != head)						//factors in if n1 is head
	{
		Node<E>* prev = head;
		Node<E>* curr = head->next;
		while (curr != n1 && curr->next != nullptr)
		{
			prev = prev->next;
			curr = curr->next;
		}
		n1->next = n2->next; //n1-> points to the node after n2
		n2->next = n1;		//n2-> points to n1 that points to n2->next
		prev->next = n2;	//prev-> points to n2
	}
	else
	{
		n1->next = n2->next;
		n2->next = n1;
		head = n2;
	}

}

/*=====getters======*/
template <typename E>
int SLinkedList<E>::size()const
{
	return sllSize;
}

template <typename E>
bool SLinkedList <E>::empty() const		//is the list empty?
{
	return head == nullptr;
}

template <typename E>
Node<E>& SLinkedList<E>::front() const		//returns front node
{
	return head->elem;
}

template <  typename E>
void   SLinkedList<E>::printDetails()   const {
	// Note: I have a class field   sllSize that is an up-to-date size of the list.
	// If you didn't implement that, then comment out the next line.
	/* Print details as much as possible even if list structure is   borked. */
	std::cout << "size=" << sllSize << "\n"; // <<   typeid(  sllSize).name()

	Node<E>*   itr = head;
	int i = 0;
	while (itr != nullptr) {
		std::cout << "index: " << i << "   data: " << itr->elem << "   node: " << itr << std::endl;
		itr = itr->next;
		i++;
		if (i > size() + 1)   //if structure of list gets messed up
			break;               //avoid infinite loop
	}
}

template <typename E>
Node <E>* SLinkedList<E>::retrieve(const int index) const
{
	/*loops through list until the element at the given index is found. Returns address
	of index*/
	Node<E>* v = head;
	int	count = 0;
	while ((v != nullptr) && (count != index))
	{
		count++;
		v = v->next;
	}
	return    v;

}

/*==========overloads==============*/
template<typename E>
E& SLinkedList <E>:: operator[](const int index)
{
	Node<E>* v = head;
	int	count = 0;
	while ((v != nullptr) && (count != index))
	{
		count++;
		v = v->next;
	}
	return v->elem;
}
template <typename E>
ostream& operator << (ostream& out, const SLinkedList<E>& v)
{
	Node<E>* temp = v.head;				//assign temp to the head of the lsit
	std::cout << "{";					//print starting bracket
	while (temp != nullptr)				//if it is nullptr then the tail has been passed
	{
		if (temp->next == nullptr)		//if tail
		{
			std::cout << temp->elem;	//print the tail element and the closing bracket
		}
		else								//have not reached the tail
		{
			std::cout << temp->elem << ",";	//print the element followed by a coma
		}
		temp = temp->next;				//advance to the next node
	}
	std::cout << "}";
	return out;
}

int main()
{
	SLinkedList <float> list;
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		float num = rand() % 999 + 1;		//number between 1 and 999
		num /= 100;							//number between .01 and 9.99
		list.addFront(num);
	}
//	std::cout << "list size is: " << list.size() << std::endl;
	std::cout << "list is: " << list << std::endl;

	///cb4: test subscript overload
	for (int i = 0; i < list.size(); i++)
		std::cout << list[i] << ", ";
	std::cout << std::endl;
	list.insertionSort();
	std::cout << list<<std::endl;
	//std::cout << std::endl;
	system("pause");
	return EXIT_SUCCESS;
}
