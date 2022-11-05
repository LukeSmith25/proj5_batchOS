#ifndef ARRAY_HEAP_PROJ5_STUDENT_H
#define ARRAY_HEAP_PROJ5_STUDENT_H

#include "arrayheap-prof-proj5.h"
#include <algorithm>

using namespace std;

/*************************
 * INSERT YOUR CODE HERE *
 *************************/

template<class Base>
ArrayHeap<Base>::ArrayHeap() {
    data = nullptr;
    heapAndFreeStack = nullptr;
    numItems = 0;
    capacity = 1;
}

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

template<class Base>
ArrayHeap<Base>::~ArrayHeap() {
    delete [] data;
    delete [] heapAndFreeStack;
    data = nullptr;
    heapAndFreeStack = nullptr;
    numItems = 0;
    capacity = 0;
}

template<class Base>
const ArrayHeap<Base> &ArrayHeap<Base>::operator=(const ArrayHeap<Base> &ah) {
    numItems = ah.numItems;
    capacity = ah.capacity;

    delete [] data;
    delete [] heapAndFreeStack;
    data = new int[capacity];
    heapAndFreeStack = new Base[capacity];

    for (int i = 0; i < numItems; i++) {
        data[i] = ah.data[i];
        heapAndFreeStack[i] = ah.heapAndFreeStack[i];
    }

    return this;
}

// DO THIS LAST
template<class Base>
void ArrayHeap<Base>::insert(const Base &item) {
    if (numItems == 0) {
        data = new Base[capacity];
        heapAndFreeStack = new int[capacity];
    }
    if (numItems == capacity) {
        doubleCapacity();
    }
    data[numItems] = item;
    numItems++;
    bubbleUp(numItems - 1);
}

// DO LAST
template<class Base>
void ArrayHeap<Base>::removeMinItem() {
    int minValue = heapAndFreeStack[0];
    int replacement = heapAndFreeStack[numItems - 1];
    numItems--;
    if (numItems > 0) {
        heapAndFreeStack[0] = replacement;
        bubbleDown(0);
    }
}

template<class Base>
const Base &ArrayHeap<Base>::getMinItem() const {
    return data[0];
}

template<class Base>
int ArrayHeap<Base>::getNumItems() const {
    return numItems;
}

// DO THIS LAST
template<class Base>
void ArrayHeap<Base>::doubleCapacity() {
    int newCapacity = capacity * 2;
    Base *newData = new Base[newCapacity];
    int *newHFS = new int[newCapacity];
    if (newData) {
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
}

template<class Base>
void ArrayHeap<Base>::bubbleUp(int ndx) {
    while (ndx > 0) {
        int parentIndex = (ndx - 1) / 2;
        // Return if no violation
        if (data[parentIndex] < data[ndx]) {
            return;
        }
        else {
            swap(heapAndFreeStack[ndx], heapAndFreeStack[parentIndex]);
            ndx = parentIndex;
        }
    }
}

template<class Base>
void ArrayHeap<Base>::bubbleDown(int ndx) {
    int childIndex = 2 * ndx + 1;
    Base value = data[ndx];
    while (childIndex < numItems) {
        Base minValue = value;
        int minIndex = -1;
        for (int i = 0; i < 2 && i + childIndex < numItems; i++) {
            if (data[i + childIndex] < minValue) {
                minValue = data[i + childIndex];
                minIndex = i + childIndex;
            }
        }
        if (!(minValue < value) && !(value < minValue)) {
            return;
        }
        else {
            swap(heapAndFreeStack[ndx], heapAndFreeStack[minIndex]);
            ndx = minIndex;
            childIndex = 2 * ndx + 1;
        }
    }
}


#endif

