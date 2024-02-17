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

/* My implementation of the heap was difficult to me so I used multiple youtube videos as a source to help me through the logic of 
heaps and the best approach. My approach is similar to linkedList where each node is attached through nodes based on fifo and
priority and the indexes involved in them. I created heapUp functions that will sort and insert according to heap property as well as 
heap down for delete and remove functions.

Sources:
Priority Queue implementation through heaps: https://www.youtube.com/watch?v=Xnpo1atN-Iw&t=2343s
"Trickle Up": https://www.youtube.com/watch?v=6i15PI_VP-E
swap() function: https://www.geeksforgeeks.org/swap-in-cpp/

Each child is sorted by the order of FIFO and priority where the root node is the one with the greatest fifo and priority, or
the one that was inserted first and the highest priority.
                                                        [ROOT NODE]
                                                        /         \
                                                [CHILD 1]          [CHILD 2]
                                                /        \         /        \
                                        [CHILD 3]   [CHILD 4]  [CHILD 6]    [CHILD 7]

*/

#include "PriorityQueue.h"
#include "TestDriver.h"
#include <iostream>
#include <vector>
using namespace std;

//PriorityQueue constructor that doesn't take any parameters
static int current_size = 0;
PriorityQueue::PriorityQueue() {
    max_capacity = DEFAULT_MAX_CAPACITY;
    pq = make_unique<Element[]>(DEFAULT_MAX_CAPACITY);
}

//PriorityQueue constructor that takes int size as a parameter
PriorityQueue::PriorityQueue(int size) {
    max_capacity = size;
    pq = make_unique<Element[]>(size);
}

//insert() that inserts element into the heap. Uses isFull() to test if the heap is full and cannot take any more
//elements into it. If false, then the function continues.
bool PriorityQueue::insert(Element& element) {
    if (isFull()) {
        return false;
    }

//Adds element according to heap property and fifo and priority order
    int index = current_size++;
    pq[index] = element;

    while (index > 0) {
        int parent = (index - 1) / 2;
        //PRIORITY ORDER = If child index has a greater priority than the parent priority, then swap() and then the index of said
        //node becomes the parent node instead.
        if (pq[index].priority > pq[parent].priority) {
            swap(pq[index], pq[parent]);
            index = parent;
        } 
        //FIFO ORDER: If child has equal priority and the fifo order is greater than the parent, then swap() places
        //with the parent.
        else if (pq[index].priority == pq[parent].priority && pq[index].fifo < pq[parent].fifo) {
            swap(pq[index], pq[parent]);
            index = parent;
        }
        else {
            break; 
        }
    }
//Returns true as in insertion was a success.
    return true;
}

//Remove() removes the rootNode or the highest priority node in the heap. Following heap property, the rootNode
//gets removed and heaps down to follow the heap property.
Element PriorityQueue::remove() {
    if (isEmpty()) {
        return Element();
    }
//RootNode gets deleted
    Element rootNode = pq[0];
    pq[0] = pq[--current_size];

    int index = 0;
    //While loop secures heapDown property and swaps according to FIFO and priority to adjust.
    while (2 * index + 1 < current_size) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        //Checks left child. If left child is lesser than the currentSize of the node and rightChild is less than leftChild
        //then leftChild becomes higherPriority than the right child.
        int lessPriority = left;
        if (right < current_size && (pq[right].priority < pq[left].priority)) {
            lessPriority = right;
        }
        //If rightChild's priority is equal to left priority but lesser in FIFO order of the leftChild, right child beomes lesser
        //priority and the leftChild becomes higherPriority or higher on the heap.
        else if (pq[right].priority == pq[left].priority && pq[right].fifo < pq[left].fifo) {
            lessPriority = right;
        }

        //If the index of the node is lessPriority then break.
        if (pq[index].priority < pq[lessPriority].priority) {
            break;
        }
        //If the index of the node's priority is than lessPriority (right) and has been inserted after lessPriority (right),
        //then break.
        else if (pq[index].priority == pq[lessPriority].priority && pq[index].fifo < pq[lessPriority].fifo) {
            break;
        }

        //swap() with lesserPriority to follow heap property.
        swap(pq[index], pq[lessPriority]);
        index = lessPriority;
    }
    return rootNode;
}

//Del() removes a specific element under the same name, FIFO, and priority order deemed by the user. Uses is Empty() to check
//if there's anything to remove
bool PriorityQueue::del(Element& element) {
    if (isEmpty()) {
        return false; 
    }

//checks if the specified element according to name and priority exists.
    int index = -1;
    for (int i = 0; i < current_size; i++) {
        if (pq[i].name == element.name && pq[i].priority == element.priority) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        return false; 
    }
    //decrements the current size to keep track.
    pq[index] = pq[--current_size];

    int parent = (index - 1) / 2;
    int left, right, lessPriority;

    //heap indexes according to ZyBooks
    while (index > 0) {
        left = 2 * index + 1;
        right = 2 * index + 2;
        lessPriority = left;

        //Heaps down following the heap property
        //If rightChild is less than the current_size of the node and rightChild's priority is lesser then left,
        //then make right the lesserPriority
        if (right < current_size && (pq[right].priority < pq[left].priority)) {
            lessPriority = right;
        }
        //If the rightChild is equivalent to left priority's but the has a lesser fifo insertion order
        //then make right the lesserPriority and left the highestPriority
        else if (pq[right].priority == pq[left].priority && pq[right].fifo < pq[left].fifo) {
            lessPriority = right;
        }

        //If the parent's priority is higher than the current index's priority or parent's priority equivalent
        //and fifo order higher than index's, then swap places so the nodes follow in heap property.
        if ((pq[parent].priority > pq[index].priority) || (pq[parent].priority == pq[index].priority && pq[parent].fifo > pq[index].fifo)) {
            swap(pq[index], pq[parent]);
            index = parent;
            //parent's index (ZyBooks)
            parent = (index - 1) / 2;
        }
        else {
            break;
        }
    }
    return true; 
}

//peek() looks at the heap's first highest priority element
Element PriorityQueue::peek() {
    return pq[0];
}

//contains() checks if there is a specific element under the same name and priority.
bool PriorityQueue::contains(Element& element) {
    for (int i = 0; i < current_size; i++) {
        if (pq[i].name == element.name && pq[i].priority == element.priority) {
            return true;
        }
    }
    return false; 
}

//returns size
int PriorityQueue::size() {
    return current_size;
}

//clears out the heap and makes it empty.
void PriorityQueue::clear() {
    current_size = 0;
}

//checks if the heap is empty.
bool PriorityQueue::isEmpty() {
    return current_size == 0;
}

//checks if the heap is full and cannot insert any more elements
bool PriorityQueue::isFull() {
    return current_size == max_capacity;
};

int main() {
    test_PQHeap();
    return 0;
}

