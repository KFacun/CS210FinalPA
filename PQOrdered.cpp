/*
For this assignment, you will write three implementations of a Priority Queue. For this
ADT, removal operations always return the object in the queue of highest priority, and if
multiple objects have the same priority, the one in the queue the longest shall be returned.
That is, no object of a given priority is ever removed as long as the queue contains one or
more object of a higher priority. Within a given priority FIFO order must be preserved. This
property is called stable sorting in a sorting algorithm, where two objects with equal keys
will need to appear in the same sorted order as they appear in the unsorted order.
Your implementations will be:
    1. Ordered Array
    2. Linked List
    3. Binary Heap
All implementations must have identical behavior, and must implement the PriorityQueue
interface (provided). The implementations must have two constructors, a default constructor
with no arguments that uses the DEFAULT_MAX_CAPACITY constant from
PriorityQueue.h, and a constructor that takes a single integer parameter that represents the
maximum capacity of the priority queue.

@author Kaelin Facun 
Louie Lu CS210
11/3/2023

*/


//Similar to PA1, I approached it the same but included more conditional statements to match priority and fifo order
//specifically in insert(), del(), and contains()

#include "PriorityQueue.h"
#include "TestDriver.h"
#include <memory>
#include <string>
using namespace std;

static int current_size = 0;

//Contructor for PriorityQueue that holds no parameters/arguments
PriorityQueue::PriorityQueue() {
    max_capacity = DEFAULT_MAX_CAPACITY;
    pq = make_unique<Element[]>(DEFAULT_MAX_CAPACITY);

}

//Constructor for Priority that holds int size as a parameter/argument
PriorityQueue::PriorityQueue(int size) {
    max_capacity = size;
    pq = make_unique<Element[]>(size);
}

//Boolean insert function that checks if the queue is full. If not full, then the insert function
//continues to insert element in the specific element address.
bool PriorityQueue::insert(Element& element) {
    //Boolean to check if queue is full and or can take more elements in the queue.
    if (isFull()) {
        return false;
    }
    
     //priorityQueue's size is incremented with element inserted.
    pq[current_size] = element;
    current_size++;

    //for loop checks for priority and orders the priorityQueue correctly based on priority. 
    //"swap" function found in library swaps function in their right position.
    for (int i = current_size - 1; i > 0 && pq[i].priority < pq[i - 1].priority; i--) {
        swap(pq[i], pq[i - 1]);
    }
    return true;
}

//Element remove function removes the most prioritized element from the queue. Can also be used under bool, similar to insert but
//the PA specifically requested remove() be under Element in PriorityQueue.h
Element PriorityQueue::remove() {
    //Boolean to check if there's anything in the queue to remove.
    if (isEmpty()) {
        return {};
    }
    //ELement of highestPriority is in the beginning position of the queue or (0)
    Element highestPriority = pq[0];
    //For loop that shifts elements to the left to fill the empty spot
    for (int i = 1; i < current_size; i++) {
        pq[i - 1] = pq[i];
    }
    //decrements size to count current size
    current_size--;

    return highestPriority;
}

//bool delete function deletes a specific element under a priority or fifo order. If found, element is deleted and del() returns true
//it was successful. If return false, element was not found and del() was unsuccessful
bool PriorityQueue::del(Element& element) {
    int index = -1;
    //For loop that searches for specific element, priority, and fifo order. Index/Element will be assigned to 'i' and 
    //elements in the next for loop will be shifted to the right of 'i' and deleted.
    for (int i = 0; i < current_size; i++) {
        if (pq[i].name == element.name && pq[i].priority == element.priority && pq[i].fifo == element.fifo) {
            index = i;
            break;
        }
    }
    //if index is -1, or not found, del() is not successful and returned false
    if (index == -1) return false;
    //shifting to the right
    for (int i = index; i < current_size - 1; i++) {
        pq[i] = pq[i + 1];
    }
    //currentsize is decremented to account for current size of the queue
    current_size--;

    return true;
}

//Element peek() returns first element of the queue. ifEmpty() boolean is used again to check if there is any elements in the
//queue. If true, isEmpty() returns empty queue.
Element PriorityQueue::peek() {
    if (isEmpty()) {
        return {};
    }
    //If false, element returns first element in the queue or at position 0.
    return {};
}

//bool contains() finds if a specific element is in the queue, based on priority and or fifo order.
bool PriorityQueue::contains(Element& element) {
    //For loop transverses the queue to find if the queue contains the specified element
    for (int i = 0; i < current_size; i++) {
        //If loop searches the queue to match the specified element and returns true if found
        if (pq[i].name == element.name && pq[i].priority == element.priority && pq[i].fifo == element.fifo) {
            return true;
        }
    }
    //Returns false if not found
    return false;
}

//size() returns the size of the queue
int PriorityQueue::size() {
    return current_size;
}

//clear() clears out the queue and makes the queue empty with no elements
void PriorityQueue::clear() {
    current_size = 0;
}

//isEmpty() is when the queue is empty, or 0 elements are not in the queue
bool PriorityQueue::isEmpty() {
    return current_size == 0;
}

//isFull() is when the queue is full and elements cannot add more elements in the queue
bool PriorityQueue::isFull() {
    return current_size == max_capacity;
}

int main() {
    test_PQOrdered();
    return 0;
}