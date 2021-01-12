#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include "job.h"
#include "TimeQueue.h"
#include <assert.h>


// Restores the heap property by swapping elements up the heap to parents
void TimeQueue::percolate_up(tq_hook index)
{
    //special case, return diretly
    if (index < 0 ||
        index >= time_heap.size() ||
        time_heap.size() == 1)
        return;
    
    int parent = (index - 1) / 2; //the parent index
    while (parent >= 0) {
        if (time_heap[parent]->getTime() > time_heap[index]->getTime()) {   !!!<
            Job* temp = time_heap[parent];
            //let the value of index parent equal to the value of index
            time_heap[parent] = time_heap[index]; //swap the value
            time_heap[index] = temp;
            index = parent;
            parent = (index - 1) / 2;
        }
        else break;
    }
}

// Restores the heap property by swapping elements down the heap to children
void TimeQueue::percolate_down(tq_hook index)
{
    if (index < 0 ||
        index >= time_heap.size() ||
        time_heap.size() == 1)
        return;
    
    int left = (2*index)+1,
    right = (2*index)+2,
    size = time_heap.size(),
    child;
    
    while (left < size) {
        if (right < size && time_heap[right]->getTime() < time_heap[left]->getTime())
            //find the smallest one
            child = right;
        else
            child = left;
        
        if (time_heap[index]->getTime() >= time_heap[child]->getTime()) {。 ！！！<
            Job* temp = time_heap[index]; //swap the position
            time_heap[index] = time_heap[child];
            time_heap[child] = temp;
            
            index = child;
            left = (2*index)+1;
            right = left+1;
        }
        else break;
    }
}

//public implementation


void TimeQueue::printHeap(std::ofstream &outfile){
    outfile<<time_heap;     !!! add << tq here
}

Job* TimeQueue::top(){
    assert( !time_heap.empty()); //check if the heap is emtpy
    return this->time_heap[0];
}

void TimeQueue::push(Job* job){
    time_heap.push_back(job);    
    !!!  update the time hook of the job here
    percolate_up(time_heap.size()-1);//the last index will always be the value minus one
}

Job* TimeQueue::pop(){
    assert(!time_heap.empty());//check if the heap is empty
    time_heap[0] = time_heap.back();
    !!! update the time hook of heap[0] here
    time_heap.pop_back();
    percolate_down(0);
    return time_heap[0];
}
void TimeQueue::remove_from_index(tq_hook index){
    assert(!time_heap.empty());
    time_heap[index] = time_heap.back();
    !!! update the time hook of heap[index] here
    time_heap.pop_back();
    percolate_down(index);
}

int TimeQueue::size() { return time_heap.size(); }
bool TimeQueue::empty() { return time_heap.empty(); }

