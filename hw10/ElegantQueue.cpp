#include <iostream> 
#include "ElegantQueue.h"
#include "Job_extra.h"
#include <string>
#include <vector>

Job* ElegantQueue::time_top() const
{
  if (time.empty())
  {
    return nullptr;
  }
  return time[0];
}

void ElegantQueue::time_percolate_up(int index)
{
	while(index > 0)
    {
      int parent = (index-1)/2;
      //if right child exists and left is greater right
      if (time[parent]->timestamp > time[index]->timestamp)
      { 
        //swap the time position
        time_swap(index, parent);
        index = parent;
      }
      else
      {
        break;
      }

    }
}

void ElegantQueue::time_percolate_down(int index)
{ 
     //while a left exists
    while ((unsigned int)2*index+1 < time.size())
    {
      int child;
      //if right child exists and left is greater right
      if ((unsigned int)2*index+2 < time.size() && time[2*index+2]->timestamp < time[2*index+1]->timestamp )
      { //copied logic from lecture note
        child = 2*index+2;//right child
      }
      else
      {
        child = 2*index+1;//left child
      }

      //if child value less than current index value
      if ( time[child]->timestamp < time[index]->timestamp )
      {
        time_swap(child, index); // swap value and other non-pointer member vars
        index = child; //reset index
      }
      else
      {
        break;
      }

    }
}

void ElegantQueue::push(Job* entry )
{
  //double push the position
  entry->ptr = this;
  time.push_back(entry);
  time[time.size()-1]->time_hook = time.size()-1;
  time_percolate_up(time.size()-1);

  urgent.push_back(entry);
  urgent[time.size()-1]->urgent_hook = urgent.size()-1;
  urgent_percolate_up(urgent.size()-1);


 }

Job* ElegantQueue::time_pop() 
{ 
    //pop the time position
    Job* j = time[0];
    time_swap(0, time.size()-1);
    time.pop_back();
    time_percolate_down(0);
    return j;
}
void ElegantQueue::time_remove_from_index(int pos)
{
  //remove by time
	time_swap(pos, time.size()-1);
	time.pop_back();
	time_percolate_down(pos);
}

void ElegantQueue::time_printHeap(std::ostream& out)
{
	out << "TQ ";
	out << time;
}


void ElegantQueue::time_swap(int i, int j)
{
  //swap the position
  Job* tmp = time[i];
  time[i] = time[j];
  time[i]->time_hook = i;
  time[j] = tmp;
  time[j]->time_hook = j;

}

Job* ElegantQueue::urgent_top() const
{
  //return the top one by the urgent
  if (urgent.empty())
  {
    return nullptr;
  }
  return urgent[0];
}

void ElegantQueue::urgent_percolate_up(int index)
{
   while(index > 0)
    {
      int parent = (index-1)/2;
      //if right child exists and left is greater right
      if (urgent[parent]->priority < urgent[index]->priority)
      { 
        urgent_swap(index, parent);
        index = parent;
      }
      else
      {
        break;
      }

    }
}

void ElegantQueue::urgent_percolate_down(int index)
{
     //while a left exists
    while ((unsigned int)2*index+1 < urgent.size())
    {
      int child;
      //if right child exists and left is greater right
      if ((unsigned int)2*index+2 < urgent.size() && urgent[2*index+2]->priority > urgent[2*index+1]->priority )
      { //copied logic from lecture note
        child = 2*index+2;//right child
      }
      else
      {
        child = 2*index+1;//left child
      }

      //if child value less than current index value
      if ( urgent[child]->priority > urgent[index]->priority )
      {
        urgent_swap(child, index); // swap value and other non-pointer member vars
        index = child; //reset index
      }
      else
      {
        break;
      }

    }
}



Job* ElegantQueue::urgent_pop() 
{ 
    //pop by the urgent
    Job* j = urgent[0];
    urgent_swap(0, urgent.size()-1);
    urgent.pop_back();
    urgent_percolate_down(0);
    return j;
}
void ElegantQueue::urgent_remove_from_index(int pos)
{
  // remove by the urgent
  urgent_swap(pos, urgent.size()-1);
  urgent.pop_back();
  urgent_percolate_down(pos);
}

void ElegantQueue::urgent_printHeap(std::ostream& out)
{
  out << "UQ ";
  out << urgent;
}

void ElegantQueue::urgent_swap(int i, int j)
{
  Job* tmp = urgent[i];
  urgent[i] = urgent[j];
  urgent[i]->urgent_hook = i;
  urgent[j] = tmp;
  urgent[j]->urgent_hook = j;

}
