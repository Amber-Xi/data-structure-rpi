#ifndef __URGENTQ_H_
#define __URGENTQ_H_
//You can change/add to these #includes
#include <vector>

typedef int uq_hook; //Used to point to a location in the heap, fill in the "???"

//Forward declaration of Job class, do not remove this line, do not change.
class Job;

//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap);

class UrgentQueue
{
private:
  std::vector<Job*> m_heap_u;
public:
	Job* top() const;//return the top value
	void percolate_up(int index);// resort the position
	void percolate_down(int index);// resort the position
	void push(Job* entry);//push every value into the heap
	Job* pop();//pop the value
	void remove_from_index(uq_hook pos);//remove one positin
	void printHeap(std::ostream& out);//print the format
	void swap(uq_hook i, uq_hook j);//swap the position
};

#endif
