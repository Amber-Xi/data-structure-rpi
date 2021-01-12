#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>


template <class T>
class priority_queue {
private:
  std::vector<T> m_heap;

public:
  priority_queue() {}

  priority_queue( std::vector<T> const& values )
  {
  	for(unsigned int i = 0; i < values.size(); ++i){
  		push(values[i]);
  	}
  }

  const T& top() const 
  {
    assert( !m_heap.empty() );
    return m_heap[0]; 
  }

  void push( const T& entry )
  {
  	m_heap.push_back(entry);
  	unsigned int i = m_heap.size()-1;
  	while(i != 0){
  		if(m_heap[i] < m_heap[(i-1)/2]){
  			T temp = m_heap[(i-1)/2];
  			m_heap[(i-1)/2] = m_heap[i];
  			m_heap[i] = temp;
  			i = (i-1)/2;
  		} else{
  			break;
  		}
  	}
  }

  void pop() 
  {
    assert( !m_heap.empty() );
    unsigned int i = 0;
    unsigned int curr;
    m_heap[i] = m_heap[m_heap.size()-1];
    m_heap.pop_back();
    while(2*i+1 < m_heap.size()){
    	if(2*i+2 < m_heap.size() && m_heap[2*i+2] < m_heap[2*i+1]){
    		curr = 2*i+2;
    	} else{
    		curr = 2*i+1;
    	}
    	if(m_heap[curr] < m_heap[i]){
    		T temp = m_heap[curr];
    		m_heap[curr] = m_heap[i];
    		m_heap[i] = temp;
    		i = curr;
    	} else{
    		break;
    	}
    }
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
  	if(heap.size() == 0){
  		return true;
  	}
  	for(unsigned int i = 0; i <= (heap.size()-1)/2; ++i){
  		if(2*i+1 < heap.size()){
  			if(heap[2*i+1] < heap[i]){
  				return false;
  			}
  		}
  		if(2*i+2 < heap.size()){
  			if(heap[2*i+2] < heap[i]){
  				return false;
  			}
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
void heapify(std::vector<T> & v, int n, unsigned int i){
  int largest = i;
  int l = 2*i+1;
  int r = 2*i+2;
  if(l < n && v[largest] < v[l]){
    largest = l;
  }
  if(r < n && v[largest] < v[r]){
    largest = r;
  }
  if(largest != i){
    T temp = v[i];
    v[i] = v[largest];
    v[largest] = temp;
    heapify(v, n, largest);
  }
}


template <class T>
void heap_sort( std::vector<T> & v )
{
	if(v.size() == 0){
		return;
	}
  for(int i = (v.size()-1)/2; i >= 0; --i){
    heapify(v, v.size(), i);
  }
  for(int i = v.size()-1; i >= 0; --i){ 
    T temp = v[i];
    v[i] = v[0];
    v[0] = temp;
    heapify(v, i, 0);
  }
}

#endif
