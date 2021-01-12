#include <iostream>
#ifndef UnrolledLL_h_
#define UnrolledLL_h_

#include <cassert>

const int NUM_ELEMENTS_PER_NODE = 6;
template <class T>
class Node
{
public:
    Node()
    {
        next_ = NULL;
        prev_ = NULL;
        num_elements=0;
    }
    
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

    void print_() const
    {
        std::cout << "num_elements: " << num_elements << std::endl;
        std::cout << elements_[0] << std::endl;
    }

    unsigned int num_elements;
    T elements_[NUM_ELEMENTS_PER_NODE];
    Node<T> * next_;
    Node<T> * prev_;
};

template<class T> class UnrolledLL;

template <class T>
class list_iterator
{
public:

    /*
    list_iterator()
    {
        ptr_ = NULL;
        offset = 0;
    }
    */
    list_iterator(Node<T>* p=NULL, unsigned int n=0)
    {
        ptr_ = p;
        offset = n;
    }

    T& operator*()
    {
        return ptr_-> elements_[offset];
    }
    
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
    
    bool operator==(const list_iterator<T>& r) const
    {
        return (this -> ptr_ == r.ptr_ && this->offset == offset);
    }
    
    bool operator!=(const list_iterator<T>& r) const
    {
        return (this -> ptr_ != r.ptr_ || this->offset != offset);
    }
    
private:
    Node<T>* ptr_;
    unsigned int offset;
};


template <class T>
class UnrolledLL
{
public:
    typedef list_iterator<T> iterator;
    
    UnrolledLL()
    {
        head_ = NULL;
        tail_ = NULL;
        size_ = 0;
    }
    
    UnrolledLL(const UnrolledLL<T>& old)
    {
        this->copy_list(old);
    }
    
    UnrolledLL& operator=(const UnrolledLL<T>& old);
    ~UnrolledLL() {this -> destory_list();}
    
    
    unsigned int size() const
    {
        return size_;
    }

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
        return head_-> elements_[0]; //error checking
    }
    const T& back() const
    {
        return tail_->elements_[tail_->num_elements-1]; // error checking
    }
    
    void print(std::ostream &ostr);
    
private:

    void copy_list(const UnrolledLL<T>& old)
    {
        size_ = old.size_;
        if (size_== 0) 
        {
            head_ = tail_ = 0;
            return;
        }
  
        head_ = new Node<T>(old.head_);
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
    Node<T>* head_;
    Node<T>* tail_;
    unsigned int size_;
};

template <class T>
void UnrolledLL<T>::push_back(const T& v)
{
    if(head_== NULL)
    {
        Node <T>* temp = new Node<T>;
        temp->elements_[0] = v;
        head_ = temp;
        tail_ = temp;
        temp->num_elements = 1;
        size_ = 1;
        
    }
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
    if(head_== NULL)
    {
        Node <T>* temp = new Node<T>;
        temp->elements_[0] = v;
        head_ = temp;
        tail_ = temp;
        temp->num_elements = 1;
        size_ = 1;
    }
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
    if(head_ == tail_ && size_ ==1)
    {
        head_ = NULL;
        tail_ = NULL;
        size_ -= 1;
    }
    else if(head_->num_elements == 1)
    {
        Node <T>* temp;
        temp = head_->next_;
        delete head_;
        head_ = temp;
        size_ -= 1;
    }
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
    if(head_ == tail_ && size_ ==1)
    {
        head_ = NULL;
        tail_ = NULL;
        size_ -= 1;
    }
    else if(tail_->num_elements == 1)
    {
        Node <T>* temp;
        temp = tail_->prev_;
        delete tail_;
        tail_ = temp;
        temp->next_ = NULL;
        size_ -= 1;
    }
    else if(tail_->num_elements != 1)
    {
        tail_->num_elements -= 1;
        size_ -= 1;
    }
}


template <class T>
void UnrolledLL<T>::print(std::ostream &ostr)
{
    
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
{//error NULL pointer
    //list empty
    size_+=1;
    if(itr.ptr_->num_elements < 6)
    {

        for(int i = itr.ptr_->num_elements; i>itr.offset; i--)
        {

            itr.ptr_->elements_[i] = itr.ptr_->elements_[i-1];
        }
        itr.ptr_->elements_[itr.offset] = v;
        itr.ptr_->num_elements+=1;
    } 
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
        /*
        if(itr.offset != 0)
        {
            for(unsigned int i = itr.offset; i<6;i++)
            {
            itr.ptr_->elements_[i] = itr.ptr_->elements_[i-itr.offset]; 
            }
        }
	
        if(itr.ptr_ == head_)
        {
            n->next_ = head_;
            head_->prev_ = n;
            head_ = n;

        }
        */
    
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
	size_-=1;
    if(size_ == 0){
        delete itr.ptr_;
        head_ = tail_ = NULL;
        return NULL;
    }
    else if(itr.ptr_ == head_ && itr.ptr_->num_elements == 1)
    {
    	iterator result(itr);
    	result++;
        head_ = itr.ptr_->next_;
        head_->prev_ = NULL;
        delete itr.ptr_;
        return result;
    }
    else if(itr.ptr_ == tail_ && itr.ptr_->num_elements == 1)
    {
        tail_ = itr.ptr_->prev_;
        tail_->next_ = NULL;
        delete itr.ptr_;
        return NULL;
    }
    else if(itr.ptr_->num_elements == 1)
    {
    	iterator result(itr);
    	result++;
        //Node<T>* temp = itr.ptr_->next_;
        itr.ptr_->prev_->next_ = itr.ptr_->next_;
        itr.ptr_->next_->prev_ = itr.ptr_->prev_;
        delete itr.ptr_;
        //itr.ptr_ = temp;
        return result;

    }
    else
    {
    	if(itr.offset == itr.ptr_->num_elements-1)
    	{
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
        
        //return iterator(itr.ptr_, itr.offset);

    }

}
 
#endif
