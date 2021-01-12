#ifndef __TIMEQ_H_
#define __TIMEQ_H_
//You can change/add to these #includes
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
typedef int tq_hook; //Used to point to a location in the heap, fill in the "???"
#include "job.h"


//Forward declaration of Job class, do not remove this line, do not change.
class Job;

//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap);

class TimeQueue{
    
    //////////FILL THIS IN///////////
    std::vector<Job*> time_heap;
    
    //private implementation
private:
    
    void percolate_up(tq_hook index);
    void percolate_down(tq_hook index);
    
    
    //public implementation
public:
    
    
    void printHeap(std::ofstream &outfile);
    Job* top();
    void push(Job* job);
    Job* pop();
    int size();
    bool empty();
    void remove_from_index(tq_hook index);
};

#endif
