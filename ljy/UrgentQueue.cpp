#include <ctime>
#include <vector>
#include <iostream>
#include <fstream>
#include "job.h"
#include "UrgentQueue.h"
#include <assert.h>

// Restores the heap property by swapping elements up the heap to parents
void UrgentQueue::percolate_up(uq_hook index)
{
   // std::cout<<index;
    //special case, return diretly
    if (index < 0 ||
        index >= urgent_heap.size() ||
        urgent_heap.size() == 1)
        return;
    
    int parent = (index - 1) / 2; //the parent index
   // std::cout<<" "<< parent <<std::endl;
    while (parent >= 0) {
        if (urgent_heap[parent]-> getPriority() < urgent_heap[index]-> getPriority()) {
            Job* temp = urgent_heap[parent];
            //let the value of index parent equal to the value of index
            urgent_heap[parent] = urgent_heap[index]; //swap the value
            urgent_heap[index] = temp;
            index = parent;
            parent = (index - 1) / 2;
        }
        else break;
    }
}

// Restores the heap property by swapping elements down the heap to children
void UrgentQueue::percolate_down(uq_hook index)
{
    if (index < 0 ||
        index >= urgent_heap.size() ||
        urgent_heap.size() == 1)
        return;
    
    int left = (2*index)+1,
    right = (2*index)+2,
    size = urgent_heap.size(),
    child;
    
    while (left < size) {
        if (right < size && urgent_heap[right]->getPriority() > urgent_heap[left]->getPriority())
            //find the biggest one
            child = right;
        else
            child = left;
        
        if (urgent_heap[index]->getPriority() <= urgent_heap[child]->getPriority()) {
            Job* temp = urgent_heap[index]; //swap the position
            urgent_heap[index] = urgent_heap[child];
            urgent_heap[child] = temp;
            
            index = child;
            left = (2*index)+1;
            right = left+1;
        }
        else break;
    }
}



void UrgentQueue::printHeap(std::ofstream &outfile){
    outfile<<urgent_heap;
    
}

Job* UrgentQueue::top(){
    assert( !urgent_heap.empty()); //check if the heap is emtpy
    return this->urgent_heap[0];
}

void UrgentQueue::push(Job* job){
    std::cout<<job<<std::endl;
    urgent_heap.push_back(job);
    percolate_up(urgent_heap.size()-1);//the last index will always be the value minus one
}

Job* UrgentQueue::pop(){
    std::cout<<"DEBUGGG"<<std::endl;
    assert(!urgent_heap.empty());//check if the heap is empty
    urgent_heap[0] = urgent_heap.back();
    urgent_heap.pop_back();
    std::cout<<"DEBUGGG222"<<std::endl;
    percolate_down(0);
    std::cout<<"DEBUGGG333"<<std::endl;
    return urgent_heap[0];
    
}
void UrgentQueue::remove_from_index(tq_hook index){
    assert(!urgent_heap.empty());
    urgent_heap[index] = urgent_heap.back();
    urgent_heap.pop_back();
    percolate_down(index);
}


int UrgentQueue::size() { return urgent_heap.size(); }
bool UrgentQueue::empty() { return urgent_heap.empty(); }



