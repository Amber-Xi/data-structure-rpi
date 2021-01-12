#include <iostream>
#ifndef UnrolledLL_h_
#define UnrolledLL_h_

#include <cassert>

// -----------------------------------------------------------------
// NODE CLASS
const int NUM_ELEMENTS_PER_NODE = 6;
template <class T>
class Node
{
public:

	//Node Constructor
    Node()
    {
        next_ = NULL;
        prev_ = NULL;
        num_elements=0;
    }
    
    //Copy Constructor
    Node(const Node<T> &old)
    {
        next_ = NULL;
        prev_ = NULL;
        num_elements=old.num_elements;
        for(unsigned int i = 0; i < num_elements; i++)
        {
            elements_[i] = old.elements_[i];
        }
    }

    // REPRESENTATION
    unsigned int num_elements;
    T elements_[NUM_ELEMENTS_PER_NODE];
    Node<T> * next_;
    Node<T> * prev_;
};

template<class T> class UnrolledLL;

// -----------------------------------------------------------------
// LIST ITERATOR
template <class T>
class list_iterator
{
public:

	//default constructor
    list_iterator(Node<T>* p=NULL, unsigned int n=0)
    {
        ptr_ = p;
        offset = n;
    }

    // dereferencing operator gives access to the value at the pointer
    T& operator*()
    {
        return ptr_-> elements_[offset];
    }
    
    // increment & decrement operators
    list_iterator<T>& operator++()
    {
        ++offset;
        if(offset >= ptr_->num_elements)
        {
            ptr_ = ptr_->next_;
            offset = 0;
        }
        return *this;
    }
    
    list_iterator<T> operator++(int)
    {
        list_iterator<T> temp(*this);
        ++(*this);
        return temp;
    }
    
    list_iterator<T>& operator--()
    {
        --offset;
        if(offset < 0)
        {
            ptr_ = ptr_->prev_;
            offset = ptr_->num_elements-1; //error checking
        }
        return *this;
    }
    
    list_iterator<T> operator--(int)
    {
        list_iterator<T> temp(*this);
        --(*this);
        return temp;
    }
    
    friend class UnrolledLL<T>;
    
    // Comparions operators are straightforward
    bool operator==(const list_iterator<T>& r) const
    {
        return (this -> ptr_ == r.ptr_ && this->offset == offset);
    }
    
    bool operator!=(const list_iterator<T>& r) const
    {
        return (this -> ptr_ != r.ptr_ || this->offset != offset);
    }
    
private:
	// REPRESENTATION
    Node<T>* ptr_;
    unsigned int offset;
};

// -----------------------------------------------------------------
// LIST CLASS DECLARATION
template <class T>
class UnrolledLL
{
public:
    typedef list_iterator<T> iterator;
    
    // default constructor, copy constructor, assignment operator, & destructor
    UnrolledLL()
    {
        head_ = NULL;
        tail_ = NULL;
        size_ = 0;
    }
    
    UnrolledLL(const UnrolledLL<T>& old)
    {
        this->copy_list(old);//Copy constuctor
    }
    
    UnrolledLL& operator=(const UnrolledLL<T>& old);
    ~UnrolledLL() {this -> destory_list();}
    
    
    unsigned int size() const
    {
        return size_;
    }

    // modify the linked list structure
    void push_front(const T& v);
    void pop_front();
    void push_back(const T& v);
    void pop_back();
    
    iterator erase(iterator itr);
    iterator insert(iterator itr, const T& v);
    iterator begin() {return iterator(head_);}
    iterator end() {return iterator(NULL);}
    
    const T& front() const
    {
    	return head_-> elements_[0];
    }
    const T& back() const
    {
        return tail_->elements_[tail_->num_elements-1]; // error checking
    }
    
    void print(std::ostream &ostr);
    
private:

	// private helper functions
    void copy_list(const UnrolledLL<T>& old)
    {
        size_ = old.size_;
        if (size_== 0) 
        {
            head_ = tail_ = 0;
            return;
        }
  
        head_ = new Node<T>(*old.head_);
        tail_ = head_;
  
        Node<T>* old_p = old.head_->next_;
  
        while (old_p) 
        {
            tail_->next_ = new Node<T>(*old_p);
            tail_->next_->prev_ = tail_;
            tail_ = tail_->next_;
            old_p = old_p->next_;
        }
    }

    void destory_list()
    {
        Node<T>* temp = head_;
        while(temp != tail_)
        {
            head_ = head_->next_;
            delete temp;
            temp = head_;
        }
        delete temp;
    }
    
private:
	//REPRESENTATION
    Node<T>* head_;
    Node<T>* tail_;
    unsigned int size_;
};

template <class T>
void UnrolledLL<T>::push_back(const T& v)
{
	/*
	Adding one element in back of the node's element list
	*/

	//If there is no elements in the linked list
    if(head_== NULL)
    {
        Node <T>* temp = new Node<T>;
        temp->elements_[0] = v;
        head_ = temp;
        tail_ = temp;
        temp->num_elements = 1;
        size_ = 1;
        
    }
    //If the elements in the linked list's node is full, create a new node on the back
    else if(tail_->num_elements == 6)
    {
        Node <T>* temp = new Node<T>;
        temp->num_elements = 1;
        temp->elements_[0] = v;
        tail_->next_ = temp;
        temp->prev_ = tail_;
        tail_ = temp;
        size_ += 1;
    }
    //If the elements in the linked list's node is not full, just add one element in the back
    else
    {
        tail_->elements_[tail_->num_elements] = v;
        tail_->num_elements += 1;
        size_ += 1;
    }
}

template <class T>
void UnrolledLL<T>::push_front(const T& v)
{
	/*
	Adding one element in front of the node's element list
	*/
	//If there is no elements in the linked list, just create a new one
    if(head_== NULL)
    {
        Node <T>* temp = new Node<T>;
        temp->elements_[0] = v;
        head_ = temp;
        tail_ = temp;
        temp->num_elements = 1;
        size_ = 1;
    }
    //If the elements in the linked list's node is full, create a new node in the front
    else if(head_->num_elements == 6)
    {
        Node <T>* temp = new Node<T>;
        temp->elements_[0] = v;
        head_->prev_= temp;
        temp->next_= head_;
        head_= temp;
        temp->num_elements = 1;
        size_ += 1;
    }
     //If the elements in the linked list's node is not full, just add one element in the front
    else if(head_->num_elements != 6)
    {
        for(int i = head_->num_elements-1;i>=0; i--)
        {
            head_->elements_[i+1] = head_->elements_[i];
        }
        head_->num_elements += 1;
        head_->elements_[0] = v;
        size_ += 1;
    }
}

template <class T>
void UnrolledLL<T>::pop_front()
{
	/*
	poping one element in front of element list
	*/
	//If the element list just has one node, deleting that node
    if(tail_ == NULL)
    {
        std::cerr << "No elements" << std::endl;
        return;
    }
    if(head_ == tail_ && size_ ==1)
    {
        head_ = NULL;
        tail_ = NULL;
        size_ -= 1;
    }
    //If the head just has one element, deleting that node
    else if(head_->num_elements == 1)
    {
        Node <T>* temp;
        temp = head_->next_;
        delete head_;
        head_ = temp;
        size_ -= 1;
    }
    // the normal situation
    else if(head_->num_elements != 1)
    {
        for(int i = 0;i<head_->num_elements; i++)
        {
            head_->elements_[i] = head_->elements_[i+1];
        }
        head_->num_elements -= 1;
        size_ -= 1;
    }
}

template <class T>
void UnrolledLL<T>::pop_back()
{
	/*
	Poping one element in back of the element list
	*/
	//If the element list just has one node, deleting that node
	if(head_ == NULL)
	{
		std::cerr << "No elements" << std::endl;
        return;
	}
    if(head_ == tail_ && size_ ==1)
    {
        head_ = NULL;
        tail_ = NULL;
        size_ -= 1;
    }
    //If the tail just has one element, deleting that node
    else if(tail_->num_elements == 1)
    {
        Node <T>* temp;
        temp = tail_->prev_;
        delete tail_;
        tail_ = temp;
        temp->next_ = NULL;
        size_ -= 1;
    }
    // the normal situation
    else if(tail_->num_elements != 1)
    {
        tail_->num_elements -= 1;
        size_ -= 1;
    }

}


template <class T>
void UnrolledLL<T>::print(std::ostream &ostr)
{
    /*
	Printing in the correct format
	*/

    ostr << "UnrolledLL, size: " << size_ << std::endl;
    
    list_iterator<T> itr;

    for(itr = begin(); itr!= end(); itr=list_iterator<T>(itr.ptr_->next_))
    {
        ostr << "node:["<< itr.ptr_->num_elements <<"]";
        for( int i=0; i< itr.ptr_->num_elements; i++)
        {
            ostr << itr.ptr_->elements_[i] << ' ';
        }
        ostr << std::endl;
    }
}

template <class T>
list_iterator<T> UnrolledLL<T>::insert(list_iterator<T> itr, const T& v)
{
	/*
	Inserting one element
	*/
	// If the number of elements is less than 6, just do the insert and pushing back the elements.
	size_ += 1;
    if(itr.ptr_->num_elements < 6)
    {
        for(int i = itr.ptr_->num_elements; i>itr.offset; i--)
        {

            itr.ptr_->elements_[i] = itr.ptr_->elements_[i-1];
        }
        itr.ptr_->elements_[itr.offset] = v;
        itr.ptr_->num_elements+=1;
    }
    // If the number of elements is greater than 6, creating a new node and then do the insert and pushing back the elements.
    else if(itr.ptr_->num_elements == 6)
    {
        Node <T>* n = new Node<T>;
        unsigned int number = 6-itr.offset;
        n->num_elements = number;
        itr.ptr_->num_elements = itr.offset+1;


        for(unsigned int i= 0; i<number; i++)
        {
            n->elements_[i] = itr.ptr_->elements_[i+itr.offset]; 
            
        }
        for(unsigned int i = itr.offset+1; i< itr.ptr_->num_elements; i++){
            itr.ptr_->elements_[i] = itr.ptr_->elements_[i+number];
        }
        itr.ptr_->elements_[itr.offset] = v;
    
        n->prev_ = itr.ptr_;
        n->next_ = itr.ptr_->next_;
        itr.ptr_->next_ = n;
        n->next_->prev_ = n;
        
        itr.ptr_ = n;
    }
    return itr;
    
}

template <class T>
list_iterator<T> UnrolledLL<T>::erase(list_iterator<T> itr)
{
	/*
	Ereasing one element
	*/
    if(itr == NULL)
    {
        std::cerr << "No elements to erase" << std::endl;
        exit(1);
    }
	size_-=1;
    if(size_ == 0)
    {
    	// If the size is zero, just delete that node
        delete itr.ptr_;
        head_ = tail_ = NULL;
        return NULL;
    }
    else if(itr.ptr_ == head_ && itr.ptr_->num_elements == 1)
    {
    	//if the head just has one element, delete that node
    	iterator result(itr);
    	result++;
        head_ = itr.ptr_->next_;
        head_->prev_ = NULL;
        delete itr.ptr_;
        return result;
    }
    else if(itr.ptr_ == tail_ && itr.ptr_->num_elements == 1)
    {
    	//if the tail just has one element, delete that node
        tail_ = itr.ptr_->prev_;
        tail_->next_ = NULL;
        delete itr.ptr_;
        return NULL;
    }
    else if(itr.ptr_->num_elements == 1)
    {
    	//if middle node just has one element, delete that node
    	iterator result(itr);
    	result++;
        itr.ptr_->prev_->next_ = itr.ptr_->next_;
        itr.ptr_->next_->prev_ = itr.ptr_->prev_;
        delete itr.ptr_;
        return result;

    }
    else
    {
    	//if middle node just has one more elements, erase the pointed one, and pushing front the elements
    	if(itr.offset == itr.ptr_->num_elements-1)
    	{
    		//when deleting the last element of the node, needs to return the offset of next node
            iterator result(itr);
            result++;
    		itr.ptr_->elements_[itr.offset] = itr.ptr_->elements_[itr.offset+1];
    		itr.ptr_->num_elements -=1;
            return result;
    	}
    	else
    	{
        	for(unsigned int i = itr.offset; i<itr.ptr_->num_elements; i++)
        	{
             	itr.ptr_->elements_[i] = itr.ptr_->elements_[i+1];
        	}
        	itr.ptr_->num_elements-=1;
            return itr;
        }
    }

}
 
#endif
