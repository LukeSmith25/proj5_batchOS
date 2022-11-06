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
    numItems = 0;
    capacity = 1;
    data = new Base[capacity];
    heapAndFreeStack = new int[capacity];
    heapAndFreeStack[0] = 0;
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
    data = new Base[capacity];
    heapAndFreeStack = new int[capacity];

    for (int i = 0; i < numItems; i++) {
        data[i] = ah.data[i];
        heapAndFreeStack[i] = ah.heapAndFreeStack[i];
    }

    return *this;
}

// DO THIS LAST
template<class Base>
void ArrayHeap<Base>::insert(const Base &item) {
    if (numItems == capacity) {
        doubleCapacity();
    }
    data[heapAndFreeStack[numItems++]] = item;
    bubbleUp(numItems - 1);
}

// DO LAST
template<class Base>
void ArrayHeap<Base>::removeMinItem() {
    swap(heapAndFreeStack[0], heapAndFreeStack[numItems - 1]);
    numItems--;
    bubbleDown(0);
}

template<class Base>
const Base &ArrayHeap<Base>::getMinItem() const {
    return data[heapAndFreeStack[0]];
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

template<class Base>
void ArrayHeap<Base>::bubbleUp(int ndx) {
    if (ndx == 0) {
        return;
    }
    int parent = (ndx - 1) / 2;
    if (heapAndFreeStack[ndx] < heapAndFreeStack[parent]) {
        swap(heapAndFreeStack[ndx], heapAndFreeStack[parent]);
        bubbleUp(parent);
    }
}

template<class Base>
void ArrayHeap<Base>::bubbleDown(int ndx) {
    int child1 = 2 * ndx + 1;
    int child2 = 2 * ndx + 2;
    if (child1 < numItems) {
        int lesserChild = child1;
        if ((child2 < numItems) && (heapAndFreeStack[child2] < heapAndFreeStack[child1])) {
            lesserChild = child2;
        }
        if (heapAndFreeStack[lesserChild] < heapAndFreeStack[ndx]) {
            swap(heapAndFreeStack[lesserChild], heapAndFreeStack[ndx]);
            bubbleDown(lesserChild);
        }
    }
}

//template<class Base>
//void ArrayHeap<Base>::checkOrder() {
//    for (int i = 0; i < numItems; i++) {
//        data[heapAndFreeStack[i]].print();
//    }
//    cout << endl;
//}


#endif

