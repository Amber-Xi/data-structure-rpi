#ifndef __URGENTQ_H_
#define __URGENTQ_H_
//You can change/add to these #includes
#include <ctime>
#include <vector>
#include <iostream>
#include <fstream>
typedef int uq_hook; //Used to point to a location in the heap, fill in the "???"
#include "job.h"



//Forward declaration of Job class, do not remove this line, do not change.
class Job;

//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap);

class UrgentQueue{
    
    //////////FILL THIS IN///////////
    std::vector<Job*> urgent_heap;
    
    //private implementation
private:
    void percolate_up(uq_hook index);
    void percolate_down(uq_hook index);
    
    //public implementaion
public:
    
    void printHeap(std::ofstream &outfile);
    Job* top();
    void push(Job* job);
    Job* pop();
    int size();
    bool empty();
    void remove_from_index(uq_hook index);
    
    
    
};

#endif
