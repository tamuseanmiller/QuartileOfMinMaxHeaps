///////////////////////////////////////////////////////////////
//  File:   QHeap
//  Course: CSCE-221 Data Structures & Algorithms
//  Author: Sean Miller
//  Date:   10/24/2019
//  Usage:  This makes a Quartile Heap
///////////////////////////////////////////////////////////////

#ifndef PROJECTTHREE_QHEAP_H
#define PROJECTTHREE_QHEAP_H


#include "MMHeap.h"

template<typename T>
class QHeap {
    MMHeap<T> **heaps;

public:

//  Default Constructor
    QHeap() : heaps(nullptr) {};

//  Initialized Constructor - Creates 4 MMHeaps and puts them in heaps with size 5
    explicit QHeap(const int &initialSize) {
        auto *temp5 = new MMHeap<T> *[5];
        heaps = temp5;
        auto *temp = new MMHeap<T>(initialSize);
        auto *temp1 = new MMHeap<T>(initialSize);
        auto *temp2 = new MMHeap<T>(initialSize);
        auto *temp3 = new MMHeap<T>(initialSize);
        heaps[0] = nullptr;
        heaps[1] = temp;
        heaps[2] = temp1;
        heaps[3] = temp2;
        heaps[4] = temp3;
        temp = nullptr;
        temp1 = nullptr;
        temp2 = nullptr;
        temp3 = nullptr;
        temp5 = nullptr;
        delete temp;
        delete temp1;
        delete temp2;
        delete temp3;
        delete[] temp5;
    };

//  Destructor
    ~QHeap() {
        for (unsigned int i = 0; i < 5; i++) {
            heaps[i] = nullptr;
            delete heaps[i];
        }
        heaps = nullptr;
        delete[] heaps;
    };


//  Consolidates by size to make sure that the first set of heaps have the max sizes
    void consolidate() {

//    Traversing from 4 to 1 and evening the size
        if (heaps[4]->size() > heaps[3]->size()) {
            heaps[3]->insert(heaps[4]->getMin());
            heaps[4]->deleteMin();
        }
        if (heaps[3]->size() > heaps[2]->size()) {
            heaps[2]->insert(heaps[3]->getMin());
            heaps[3]->deleteMin();
        }
        if (heaps[2]->size() > heaps[1]->size()) {
            heaps[1]->insert(heaps[2]->getMin());
            heaps[2]->deleteMin();
        }

//    Going in the opposite Direction
        if (heaps[1]->size() > (heaps[2]->size() + 1)) {
            heaps[2]->insert(heaps[1]->getMax());
            heaps[1]->deleteMax();
        }
        if (heaps[2]->size() > (heaps[3]->size() + 1)) {
            heaps[3]->insert(heaps[2]->getMax());
            heaps[2]->deleteMax();
        }
        if (heaps[3]->size() > (heaps[4]->size() + 1)) {
            heaps[4]->insert(heaps[3]->getMax());
            heaps[3]->deleteMax();
        }
    }

//  Inserts information into your QHeap
    void insert(T *px) {
        if (heaps == nullptr) {
            auto *temp5 = new MMHeap<T> *[5];
            heaps = temp5;
            heaps[0] = nullptr;
            temp5 = nullptr;
            delete[] temp5;
        } else if (heaps[1]->size() == 0) {
            heaps[1]->insert(px);

//      Checks for if only a single value has been inserted
        } else if (heaps[2]->size() == 0) {
            if (*px < *heaps[1]->getMax()) {
                heaps[2]->insert(heaps[1]->getMin());
                heaps[1]->deleteMin();
                heaps[1]->insert(px);
            } else {
                heaps[2]->insert(px);
            }

//      Checks for if only two values have been inserted
        } else if (heaps[3]->size() == 0) {
            if (*px < *heaps[1]->getMax()) {
                heaps[3]->insert(heaps[2]->getMax());
                heaps[2]->deleteMax();
                heaps[2]->insert(heaps[1]->getMax());
                heaps[1]->deleteMax();
                heaps[1]->insert(px);
            } else if (*px > *heaps[1]->getMax() && *px < *heaps[2]->getMin()) {
                heaps[3]->insert(heaps[2]->getMin());
                heaps[2]->deleteMin();
                heaps[2]->insert(heaps[1]->getMin());
                heaps[1]->deleteMin();
                heaps[1]->insert(px);
            } else if (*px < *heaps[2]->getMax()) {
                heaps[3]->insert(heaps[2]->getMax());
                heaps[2]->deleteMax();
                heaps[2]->insert(px);
            } else {
                heaps[3]->insert(px);
            }

//      Checks for if only three values have been inserted
        } else if (heaps[4]->size() == 0) {
            if (*px < *heaps[1]->getMax()) {
                heaps[4]->insert(heaps[3]->getMax());
                heaps[3]->deleteMax();
                heaps[3]->insert(heaps[2]->getMax());
                heaps[2]->deleteMax();
                heaps[2]->insert(heaps[1]->getMax());
                heaps[1]->deleteMax();
                heaps[1]->insert(px);
            } else if (*px > *heaps[1]->getMax() && *px < *heaps[2]->getMin()) {
                heaps[4]->insert(heaps[3]->getMin());
                heaps[3]->deleteMin();
                heaps[3]->insert(heaps[2]->getMin());
                heaps[2]->deleteMin();
                heaps[2]->insert(heaps[1]->getMin());
                heaps[1]->deleteMin();
                heaps[1]->insert(px);
            } else if (*px < *heaps[2]->getMax()) {
                heaps[4]->insert(heaps[3]->getMax());
                heaps[3]->deleteMax();
                heaps[3]->insert(heaps[2]->getMax());
                heaps[2]->deleteMax();
                heaps[2]->insert(px);
            } else if (*px > *heaps[2]->getMax() && *px < *heaps[3]->getMin()) {
                heaps[4]->insert(heaps[3]->getMin());
                heaps[3]->insert(heaps[2]->getMin());
                heaps[2]->deleteMin();
                heaps[2]->insert(px);
            } else if (*px < *heaps[3]->getMax()) {
                heaps[4]->insert(heaps[3]->getMax());
                heaps[3]->deleteMax();
                heaps[3]->insert(px);
            } else {
                heaps[4]->insert(px);
            }

//      If the value is less than the min
        } else if (*px > *heaps[4]->getMin()) {
            heaps[4]->insert(px);
            consolidate();

//      If the value is greater than the min of the third heap
        } else if (*px > *heaps[3]->getMin()) {
            heaps[3]->insert(px);
            consolidate();

//      If the value is greater than the min of the second heap
        } else if (*px > *heaps[2]->getMin()) {
            heaps[2]->insert(px);
            consolidate();

//      Literally anything else
        } else {
            heaps[1]->insert(px);
            consolidate();
        }

    };

//  Dumps debug information into the console
    void dump() {
        cout << "***********************************" << endl;
        cout << "***** Quartile heap statistics ..." << endl;
        cout << "Minimum = " << *getMin() << endl;
        cout << "25th Percentile = " << *get25() << endl;
        cout << "Median = " << *get50() << endl;
        cout << "75th Percentile = " << *get75() << endl;
        cout << "Maximum = " << *getMax() << endl;
        cout << "---------------------------------------" << endl;
        cout << "***** First Quartile heap dump ..." << endl;
        cout << "---------------------------------------" << endl;
        heaps[1]->dump();
        cout << "---------------------------------------" << endl;
        cout << "***** Second Quartile heap dump ..." << endl;
        cout << "---------------------------------------" << endl;
        heaps[2]->dump();
        cout << "---------------------------------------" << endl;
        cout << "***** Third Quartile heap dump ..." << endl;
        cout << "---------------------------------------" << endl;
        heaps[3]->dump();
        cout << "---------------------------------------" << endl;
        cout << "***** Fourth Quartile heap dump ..." << endl;
        cout << "---------------------------------------" << endl;
        heaps[4]->dump();
        cout << "---------------------------------------" << endl;
        cout << "***** End of Quartile heap dump" << endl;
        cout << "***********************************" << endl;

    };

//  Returns the minimum value in the first MMHeap
    T *getMin() {
        return heaps[1]->getMin();
    };

//  Returns the max value in the fourth minmax heap
    T *getMax() {
        return heaps[4]->getMax();
    };

//  Returns th max value in the first heap
    T *get25() {
        return heaps[1]->getMax();
    };

//  Returns the max value in the second heap
    T *get50() {
        return heaps[2]->getMax();
    };

//  Returns the max value in the third heap
    T *get75() {
        return heaps[3]->getMax();
    };

};


#endif //PROJECTTHREE_QHEAP_H
