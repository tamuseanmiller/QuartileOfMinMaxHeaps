///////////////////////////////////////////////////////////////
//  File:   MMHeap
//  Course: CSCE-221 Data Structures & Algorithms
//  Author: Sean Miller
//  Date:   10/24/2019
//  Usage:  Class for the MinMax heap
///////////////////////////////////////////////////////////////

//
// Created by Sean on 10/24/2019.
//

#include <cmath>
#include "MMHeap.h"

//template<typename T>
//void MMHeap<T>::grow() {
//    pData
//}

// If the last level is even (min level), return true otherwise (max level) return false O(log(n))
template<typename T>
bool MMHeap<T>::lastLevel() {
    unsigned int cnt = 1;
    for (unsigned int i = length - 1; i >= 1; floor(i /= 2)) {
        cnt++;
    }
    return cnt % 2 == 0;
}

// Helper method for insert that calls itself recursively
template<typename T>
void MMHeap<T>::insertHelp(T *px, size_t length) {

//  Checks to see whether the last level is a min or a max level
    if (lastLevel()) {

//      Base Case
        if (length == 0) {
            return;

//        Compares to the next min row
        } else if (px < pData[floor((length - 1) / 4)]) {
            pData[length] == pData(floor((length - 1) / 4));
            pData[(length - 1) / 4] = px;
            insertHelp(px, floor(length / 2));

//        Compares to the next max row
        } else if (px > pData[floor(length - 1)] / 2) {
            pData[length] == pData(floor((length - 1) / 2));
            pData[floor((length - 1) / 2)] = px;
            insertHelp(px, floor(length / 2));

//        If it's in the right spot
        } else {
            return;
        }
    } else {

//      Base Case
        if (length == 0) {
            return;

//        Compares to the next min row
        } else if (px > pData[floor((length - 1) / 4)]) {
            pData[length] == pData(floor((length - 1) / 4));
            pData[(length - 1) / 4] = px;
            insertHelp(px, floor(length / 2));

//        Compares to the next max row
        } else if (px < pData[floor(length - 1)] / 2) {
            pData[length] == pData(floor((length - 1) / 2));
            pData[floor((length - 1) / 2)] = px;
            insertHelp(px, floor(length / 2));

//        If it's in the right spot
        } else {
            return;
        }
    }
}

// Inserts a node into the minmax heap
template<typename T>
void MMHeap<T>::insert(T *px) {
//    if (++length == capacity) {
//        grow();
//    }
    insertHelp(px, length);
    length++;
}

template<typename T>
void MMHeap<T>::dump() {

}

template<typename T>
T *MMHeap<T>::getMin() {
    return pData;
}

template<typename T>
T *MMHeap<T>::getMax() {
    return nullptr;
}

template<typename T>
T MMHeap<T>::deleteMin() {
    length--;
}

template<typename T>
T MMHeap<T>::deleteMax() {
    length--;
    return nullptr;
}
