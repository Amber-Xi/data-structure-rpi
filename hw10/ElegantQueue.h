#ifndef __TIMEQ_H_
#define __TIMEQ_H_
//You can change/add to these #includes
#include <ctime>
#include <vector>

typedef int eq_hook; //Used to point to a location in the heap, fill in the "???"

//Forward declaration of Job class, do not remove this line, do not change.
class Job;

//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap);

class ElegantQueue
{
private:
  std::vector<Job*> time;
  std::vector<Job*> urgent;
public:
	Job* time_top() const;
	void time_percolate_up(int index);
	void time_percolate_down(int index);
	void push(Job* entry);
	Job* time_pop();
	void time_remove_from_index(eq_hook pos);
	void time_printHeap(std::ostream& out);
	void time_swap(eq_hook i, eq_hook j);



	Job* urgent_top() const;
	void urgent_percolate_up(int index);
	void urgent_percolate_down(int index);
	Job* urgent_pop();
	void urgent_remove_from_index(eq_hook pos);
	void urgent_printHeap(std::ostream& out);
	void urgent_swap(eq_hook i, eq_hook j);
};

#endif