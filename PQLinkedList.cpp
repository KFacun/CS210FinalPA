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


/* As it is a LinkedList, the program uses nodes with int data that are based on priority and fifo order.
    
    Node 1: FIFO pos 1              Node 2: FIFO pos 2             Node 3: FIFO pos 3
    [head->data.priority->next]->   [prev->data.priority->next]->  [prev->data.priority->tail] 

*/

//Constructor of PriorityQueue that does not take parameters/arguments

#include "PriorityQueue.h"
#include "TestDriver.h"
#include <memory>
#include <string>
using namespace std;

PriorityQueue::PriorityQueue()
{
    max_capacity = DEFAULT_MAX_CAPACITY;
    head = nullptr;
}

//Constructor of PriorityQueue that takes int size as a parameter/argument
PriorityQueue::PriorityQueue(int size)
{
    max_capacity = size;
    head = nullptr;
}

//Constructor for a newNode. Implemented the function of release() to unassign the newNode pointer so it can be unreferenced if a new
//node is made. Found it through a implementation for nodes through: https://cplusplus.com/reference/memory/unique_ptr/release/
std::unique_ptr<Node> newNode(const Element& element) {
    auto newNodePtr = std::make_unique<Node>();
    newNodePtr->data = element;
    newNodePtr->next = nullptr;
    return newNodePtr;
}

//Bool insert() that uses the boolean is Full() to check if the linkedList is full. If full, then return false for insert(), as in
//unsuccessful in insertion. If true, then proceed with insert() by insertion of a new node in the correct order of fifo and priority.
bool PriorityQueue::insert(Element& element) {
    if (isFull()) return false;

    auto newNodePtr = newNode(element);
    Node* newNode = newNodePtr.release();
    if (!head || head->data.priority > element.priority) {
        newNode->next = head;
        head = newNode;
        return true;
    }

//Conditional statement to check if node fits the correct order of priority and fifo insertion.
    Node* currentNode = head;
    while (currentNode->next && currentNode->next->data.priority <= element.priority) {
        currentNode = currentNode->next;
    }

    newNode->next = currentNode->next;
    currentNode->next = newNode;
    return true;
}

//Element remove() take takes bool isEmpty() to check if there is anything to remove in the linkedList. If isEmpty() true,
//then return element list. Else, then remove node and attach the leftover nodes.
Element PriorityQueue::remove() {
    if (isEmpty()) {
        return Element();
    }

    Node* temp = head;
    head = head->next;
    Element removedElement = temp->data;
    delete temp;
    return removedElement;
}

//Bool del removes a node that fits a specific name and priority in the list. Uses isEmpty() boolean to check if there is anything to remove
//If isEmpty() is true, then del() is unsuccessful in removal of the specific element.
bool PriorityQueue::del(Element& element) {
    if (isEmpty()) return false;

//Checks the head node separately and assigns the next node as the head node
    if (head->data.name == element.name && head->data.priority == element.priority) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

//Checks the rest of the list to see if the specific node exists to be deleted
    Node* currentNode = head;
    while (currentNode->next && (currentNode->next->data.name != element.name || currentNode->next->data.priority != element.priority)) {
        currentNode = currentNode->next;
    }

    if (!currentNode->next) return false;
//Reassigns the ordering and connects the next node back into the linkedList
    Node* temp = currentNode->next;
    currentNode->next = currentNode->next->next;
    delete temp;
    return true;
}

//Bool contains() searches for the element and returns true if the element has been found. False, if no such element exists.
bool PriorityQueue::contains(Element& element) {
    Node* currentNode = head;
    while (currentNode) {
        if (currentNode->data.name == element.name && currentNode->data.priority == element.priority) return true;
        currentNode = currentNode->next;
    }
    return false;
}

//Peek returns the head node
Element PriorityQueue::peek() {
    if (isEmpty()) return Element();

    return head->data;
}

//size() returns the size of the linkedList. 
int PriorityQueue::size() {
    int count = 0;
    Node* currentNode = head;
    while (currentNode) {
        count++;
        currentNode = currentNode->next;
    }
    return count;
}

//clear() cleans out the linkedList
void PriorityQueue::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

//isEmpty() is used in the list to see if the list is empty or not
bool PriorityQueue::isEmpty() {
    return !head;
}

//isFull is used in the list to see if the list is full. Used in insert() to see if the linkedList can be added to.
bool PriorityQueue::isFull() {
    return size() >= max_capacity;
}

int main() {
    test_PQLinkedList();
    return 0;
}
