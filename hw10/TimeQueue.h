#ifndef __TIMEQ_H_
#define __TIMEQ_H_
//You can change/add to these #includes
#include <ctime>
#include <vector>

typedef int tq_hook; //Used to point to a location in the heap, fill in the "???"

//Forward declaration of Job class, do not remove this line, do not change.
class Job;

//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap);

class TimeQueue
{
private:
  std::vector<Job*> m_heap;
public:
	Job* top() const;//return the top value
	void percolate_up(int index);// resort the position
	void percolate_down(int index);// resort the position
	void push(Job* entry);//push every value into the heap
	Job* pop();//pop the value
	void remove_from_index(tq_hook pos);//remove one positi
	void printHeap(std::ostream& out);//print the format
	void swap(tq_hook i, tq_hook j);//swap the position
};

#endif
