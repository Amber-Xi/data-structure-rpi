#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>
#include <math.h> 


template <class T>
class priority_queue {
private:
  std::vector<T> m_heap;

public:
  priority_queue() {}

  priority_queue(std::vector<T> const& values)
  {
  	/*
      for (int i = 0; i < values.size(); i++)
      {
          push(values[i]);
      }
      */
  	if (values.size() == 0)
    {
        return;
    }
    for(int x = 0; x < values.size();x++)
    {
      m_heap.push_back(values[x]);
      percolate_up();
    }
  }


  const T& top() const 
  {
    assert( !m_heap.empty() );
    return m_heap[0]; 
  }

  void percolate_up()
  {
  	/*
    int parent = floor((node-1)/2);
    while (parent >= 0)
    {
      if (m_heap[node] < m_heap[parent])
      {
        T tmp = m_heap[parent];
        m_heap[parent] = m_heap[node];
        m_heap[node] = tmp;
        node = parent;
        parent = floor((parent-1)/2);
     } 
    else 
    {
        break;
        
    }
  }
  */
  	for(int i = m_heap.size()-1; i >= 0;){
    //if (p->value < p->parent->value) {
    if (m_heap[i] < m_heap[(i - 1)/2]){ //if prev value is greater than current
      //swap(p, parent);  // value and other non-pointer member vars
      std::swap(m_heap[i], m_heap[(i - 1)/2]); // swap value
      //p = p->parent;
      i = (i - 1)/2; //resent i aka parent
    }
    else
      break;
  }
}

void percolate_down(int index){
     //while a left exists
    while ((unsigned int)2*index+1 < m_heap.size() ){
      int child;
      //if right child exists and left is greater right
      if ((unsigned int)2*index+2 < m_heap.size() && m_heap[2*index+2] < m_heap[2*index+1] ){ //copied logic from lecture note
        child = 2*index+2;//right child
      }
      else{
        child = 2*index+1;//left child
      }

      //if child value less than current index value
      if ( m_heap[child] < m_heap[index] ){
        std::swap(m_heap[child], m_heap[index]); // swap value and other non-pointer member vars
        index = child; //reset index
      }
      else{
        break;
      }
    }
    }

  void push( const T& entry )
  {
  	/*
    int pos = m_heap.size(); //position of newly inserted item
    m_heap.push_back(entry);
    percolate_up(pos);
    */
    m_heap.push_back(entry);
    percolate_up();
  }

  void pop() 
  {
    assert( !m_heap.empty() );
    std::swap(m_heap[0], m_heap[m_heap.size()-1]);
    m_heap.pop_back();
    percolate_down(0);
  }

  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }


  //  The following three functions are used for debugging.

  //  Check to see that internally the heap property is realized.
  bool check_heap( )
  {
    return this->check_heap( this->m_heap );
  }

  //  Check an external vector to see that the heap property is realized.
  bool check_heap( const std::vector<T>& heap )
  {
    for (int i = 0; i < heap.size(); i++)
    {
        if (2*i + 1 < heap.size())
        {
            if (heap[i] > heap[2*i + 1]) return false;
        }

        if (2*i + 2 < heap.size())
        {
            if (heap[i] > heap[2*i + 2]) return false;
        }
    }

    return true;
  }

  //  A utility to print the contents of the heap.  Use it for debugging.
  void print_heap( std::ostream & ostr )
  {
    for ( unsigned int i=0; i<m_heap.size(); ++i )
      ostr << i << ": " << m_heap[i] << std::endl;
  }
  
};


template <class T>
void heap_sort( std::vector<T> & v )
{
	/*
  priority_queue<T> heap(v);
  v.clear();

    while (heap.size() != 0)
    {
        v.push_back(heap.top());
        heap.pop();
    }
    */

	if(v.size()==0)
	{
    	return;
     }

  for(int x = 0;x < v.size()-1;x++)
  {
    if(v[x]>v[x+1])
    {
      std::swap(v[x],v[x+1]);
      heap_sort(v);
    }
  }
}

void swap()

#endif
