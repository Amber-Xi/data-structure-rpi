#include <iostream> 
#include "TimeQueue.h"
#include "Job.h"
#include <string>
#include <vector>

Job* TimeQueue::top() const
{
  //check whether the heap is empty
  if (m_heap.empty())
  {
    return nullptr;
  }
  //return the first position of heap
  return m_heap[0];
}

void TimeQueue::percolate_up(int index)
{
	while(index > 0)
    {
      int parent = (index-1)/2;
      //if the parent's timestamp greater than the child's one
      if (m_heap[parent]->timestamp > m_heap[index]->timestamp)
      { 
        //swap the position
        swap(index, parent);
        index = parent;
      }
      else
      {
        break;
      }

    }
}

void TimeQueue::percolate_down(int index)
{
     //while a left exists
    while ((unsigned int)2*index+1 < m_heap.size())
    {
      int child;
      //if right child exists and left is greater right
      if ((unsigned int)2*index+2 < m_heap.size() && m_heap[2*index+2]->timestamp < m_heap[2*index+1]->timestamp )
      { //copied logic from lecture note
        child = 2*index+2;//right child
      }
      else
      {
        child = 2*index+1;//left child
      }

      //if child value less than current index value
      if ( m_heap[child]->timestamp < m_heap[index]->timestamp )
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

void TimeQueue::push(Job* entry )
{
  //reset time_ptr
  entry->time_ptr = this;
  m_heap.push_back(entry);
  //set the time_hook
  m_heap[m_heap.size()-1]->time_hook = m_heap.size()-1;
  percolate_up(m_heap.size()-1);

 }

Job* TimeQueue::pop() 
{ 
    // pop the first position
    Job* j = m_heap[0];
    swap(0, m_heap.size()-1);
    m_heap.pop_back();
    percolate_down(0);
    //return pop value
    return j;
}
void TimeQueue::remove_from_index(tq_hook pos)
{
  //swap the position
	swap(pos, m_heap.size()-1);
	m_heap.pop_back();
	percolate_down(pos);
}

void TimeQueue::printHeap(std::ostream& out)
{
	out << "TQ ";
	out << m_heap;
}

void TimeQueue::swap(tq_hook i, tq_hook j)
{
  //swap the position
  Job* tmp = m_heap[i];
  m_heap[i] = m_heap[j];
  //reset the time_hook
  m_heap[i]->time_hook = i;
  m_heap[j] = tmp;
  m_heap[j]->time_hook = j;

}