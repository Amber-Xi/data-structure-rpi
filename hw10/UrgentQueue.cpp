#include <iostream> 
#include "UrgentQueue.h"
#include "Job.h"
#include <string>
#include <vector>

Job* UrgentQueue::top() const
{
  //check whether the heap is empty
  if (m_heap_u.empty())
  {
    return nullptr;
  }
   //return the first position of heap
  return m_heap_u[0];
}

void UrgentQueue::percolate_up(int index)
{
	 while(index > 0)
    {
      int parent = (index-1)/2;
      //if right child exists and left is greater right
      if (m_heap_u[parent]->priority < m_heap_u[index]->priority)
      { 
        swap(index, parent);
        index = parent;
      }
      else
      {
        break;
      }

    }
}

void UrgentQueue::percolate_down(int index)
{
     //while a left exists
    while ((unsigned int)2*index+1 < m_heap_u.size())
    {
      int child;
      //if right child exists and left is greater right
      if ((unsigned int)2*index+2 < m_heap_u.size() && m_heap_u[2*index+2]->priority > m_heap_u[2*index+1]->priority )
      { //copied logic from lecture note
        child = 2*index+2;//right child
      }
      else
      {
        child = 2*index+1;//left child
      }

      //if child value less than current index value
      if ( m_heap_u[child]->priority > m_heap_u[index]->priority )
      {
        swap(child, index); // swap value and other non-pointer member vars
        index = child; //reset index
      }
      else
      {
        break;
      }

    }
}

void UrgentQueue::push(Job* entry )
{
  //reset time_ptr
  entry->priority_ptr = this;
  m_heap_u.push_back(entry);
  //set the time_hook
  m_heap_u[m_heap_u.size()-1]->urgent_hook = m_heap_u.size()-1;
  percolate_up(m_heap_u.size()-1);

 }

Job* UrgentQueue::pop() 
{ 
    // pop the first position
    Job* j = m_heap_u[0];
    swap(0, m_heap_u.size()-1);
    m_heap_u.pop_back();
    percolate_down(0);
    //return pop value
    return j;
}
void UrgentQueue::remove_from_index(uq_hook pos)
{
  swap(pos, m_heap_u.size()-1);
	m_heap_u.pop_back();
	percolate_down(pos);
}

void UrgentQueue::printHeap(std::ostream& out)
{
	out << "UQ ";
	out << m_heap_u;
}

void UrgentQueue::swap(uq_hook i, uq_hook j)
{
  //swap the position
  Job* tmp = m_heap_u[i];
  m_heap_u[i] = m_heap_u[j];
  //reset the time_hook
  m_heap_u[i]->urgent_hook = i;
  m_heap_u[j] = tmp;
  m_heap_u[j]->urgent_hook = j;

}