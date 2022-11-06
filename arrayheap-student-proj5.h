/**
 * file: arrayheap-student-proj5.h
 * author: Luke Smith
 * course: CSI 3334
 * assignment: project 5
 * due date: November 6, 2022
 *
 * Array heap file containing all array heap operations.
 */
#ifndef ARRAY_HEAP_PROJ5_STUDENT_H
#define ARRAY_HEAP_PROJ5_STUDENT_H

#include "arrayheap-prof-proj5.h"
#include <algorithm>

using namespace std;

/*************************
 * INSERT YOUR CODE HERE *
 *************************/

/**
 * Default Constructor
 *
 * This function is the default constructor for arrayheap.
 *
 * Parameters: none
 *
 * Return value: none
 */
template<class Base>
ArrayHeap<Base>::ArrayHeap() {
    numItems = 0;
    capacity = 1;
    data = new Base[capacity];
    heapAndFreeStack = new int[capacity];
    heapAndFreeStack[0] = 0;
}

/**
 * Copy Constructor
 *
 * This function creates and copies and array heap object.
 *
 * Parameters:
 *      ArrayHeap<Base> ah: process to be copied
 *
 * Return value: none
 */
template<class Base>
ArrayHeap<Base>::ArrayHeap(const ArrayHeap<Base> &h) {
    data = new Base[h.capacity];
    heapAndFreeStack = new int[h.capacity];
    numItems = h.numItems;
    capacity = h.capacity;

    for (int i = 0; i < numItems; i++) {
        data[i] = h.data[i];
        heapAndFreeStack[i] = h.heapAndFreeStack[i];
    }
}

/**
 * Default Destructor
 *
 * This function is the default destructor for array heap.
 *
 * Parameters: none
 *
 * Return value: none
 */
template<class Base>
ArrayHeap<Base>::~ArrayHeap() {
    delete [] data;
    delete [] heapAndFreeStack;
    data = nullptr;
    heapAndFreeStack = nullptr;
    numItems = 0;
    capacity = 0;
}

/**
 * Overloaded operator=
 *
 * This function copies an array heap object to current object.
 *
 * Parameters:
 *      ArrayHeap<Base> ah: process to be copied
 *
 * Return value: Copied array heap object
 */
template<class Base>
const ArrayHeap<Base> &ArrayHeap<Base>::operator=(const ArrayHeap<Base> &ah) {
    numItems = ah.numItems;
    capacity = ah.capacity;

    delete [] data;
    delete [] heapAndFreeStack;
    data = new Base[capacity];
    heapAndFreeStack = new int[capacity];

    for (int i = 0; i < numItems; i++) {
        data[i] = ah.data[i];
        heapAndFreeStack[i] = ah.heapAndFreeStack[i];
    }

    return *this;
}

/**
 * insert
 *
 * This function inserts an item into an array heap and bubbles up the item.
 *
 * Parameters:
 *      Base &item: item to be inserted
 *
 * Return value: boolean representing if current proc < passed proc
 */
template<class Base>
void ArrayHeap<Base>::insert(const Base &item) {
    if (numItems == capacity) {
        doubleCapacity();
    }
    data[heapAndFreeStack[numItems++]] = item;
    bubbleUp(numItems - 1);
}


/**
 * removeMinItem
 *
 * This function removes the minimum item in array heap.
 *
 * Parameters: none
 *
 * Return value: none
 */
template<class Base>
void ArrayHeap<Base>::removeMinItem() {
    swap(heapAndFreeStack[0], heapAndFreeStack[numItems - 1]);
    numItems--;
    bubbleDown(0);
}

/**
 * getMinItem
 *
 * This function returns the minimum item in an array heap.
 *
 * Parameters: none
 *
 * Return value: minimum array heap object
 */
template<class Base>
const Base &ArrayHeap<Base>::getMinItem() const {
    return data[heapAndFreeStack[0]];
}

/**
 * getNumItems
 *
 * This function returns the number of items in an array heap
 *
 * Parameters: none
 *
 * Return value: integer representing number of items
 */
template<class Base>
int ArrayHeap<Base>::getNumItems() const {
    return numItems;
}

/**
 * doubleCapacity
 *
 * This function doubles the capacity of an array heap.
 *
 * Parameters: none
 *
 * Return value: none
 */
template<class Base>
void ArrayHeap<Base>::doubleCapacity() {
    int newCapacity = capacity * 2;
    Base *newData = new Base[newCapacity];
    int *newHFS = new int[newCapacity];
    for (int i = 0; i < newCapacity; i++) {
        newHFS[i] = i;
    }
    for (int i = 0; i < numItems; i++) {
        newData[i] = data[i];
        newHFS[i] = heapAndFreeStack[i];
    }

    delete [] data;
    data = newData;
    delete [] heapAndFreeStack;
    heapAndFreeStack = newHFS;
    capacity = newCapacity;
}

/**
 * bubbleUp
 *
 * This function bubbles up an item to its respective location in an array heap
 *
 * Parameters:
 *      int ndx: index to be bubbled up from
 *
 * Return value: none
 */
template<class Base>
void ArrayHeap<Base>::bubbleUp(int ndx) {
    if (ndx == 0) {
        return;
    }
    int parent = (ndx - 1) / 2;
    if (data[heapAndFreeStack[ndx]] < data[heapAndFreeStack[parent]]) {
        swap(heapAndFreeStack[ndx], heapAndFreeStack[parent]);
        bubbleUp(parent);
    }
}

/**
 * bubbleDown
 *
 * This function bubbles down an item to its respective location
 * from the minimum location in an array heap.
 *
 * Parameters:
 *      int ndx: index to be bubbled down from
 *
 * Return value: none
 */
template<class Base>
void ArrayHeap<Base>::bubbleDown(int ndx) {
    int child1 = 2 * ndx + 1;
    int child2 = 2 * ndx + 2;
    if (child1 < numItems) {
        int lesserChild = child1;
        if ((child2 < numItems) &&
        (data[heapAndFreeStack[child2]] < data[heapAndFreeStack[child1]])) {
            lesserChild = child2;
        }
        if (data[heapAndFreeStack[lesserChild]] < data[heapAndFreeStack[ndx]]){
            swap(heapAndFreeStack[lesserChild], heapAndFreeStack[ndx]);
            bubbleDown(lesserChild);
        }
    }
}

#endif

