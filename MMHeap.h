///////////////////////////////////////////////////////////////
//  File:   MMHeap
//  Course: CSCE-221 Data Structures & Algorithms
//  Author: Sean Miller
//  Date:   10/24/2019
//  Usage:  Class for the MinMax heap
///////////////////////////////////////////////////////////////

#ifndef PROJECTTHREE_MMHEAP_H
#define PROJECTTHREE_MMHEAP_H


#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

template<typename T>
class MMHeap {
private:
    T **pData;
    size_t length;
    size_t capacity;

    void grow() {

//      Doubles capacity
        capacity *= 2;

//      Creates temporary array of new size
        T **temp = new T *[capacity];

//      Copies values over
        for (unsigned int i = 1; i <= length; i++) {
            temp[i] = pData[i];
        }

//      Finish
        pData = temp;
        temp = nullptr;
        delete[] temp;
    };

public:

//  Default Constructor
    MMHeap() : pData(nullptr), length(0), capacity(1) {};

//  Initialized Constructor
    explicit MMHeap(const int &initialSize) : length(0), capacity(initialSize / 2) { grow(); };

//  Destructor
    ~MMHeap() {
        for (unsigned int i = 0; i < capacity; i++) {
            pData[i] = nullptr;
            delete pData[i];
        }
        pData = nullptr;
        delete[] pData;
    };

//  Does the same thing percolateDownMin does just when deleting max values
    void percolateDownMax(int index) {

        //      Base case
        if ((index * 4) > length) {
            return;
        }

//      Checks if there is only one grandchild
        if ((index * 4) <= length && (index * 4 + 1) > length) {
            if (*pData[index * 4] > *pData[index]) {
                swap(index, 4 * index);
                percolateDownMax(4 * index);
            }
//      if there are only two grandchildren
        } else if ((index * 4) <= length && (index * 4 + 1) <= length && (index * 4 + 2) > length) {

//          pData[4 * index]
            if (*pData[4 * index] > *pData[4 * index + 1]) {
                swap(index, 4 * index);
                percolateDownMax(4 * index);

//          pData[4 * index + 1]
            } else if (*pData[4 * index + 1] > *pData[4 * index]) {
                swap(index, 4 * index + 1);
                percolateDownMax(index * 4 + 1);
            }

//      if there are only three grandchildren
        } else if ((index * 4) <= length && (index * 4 + 1) <= length && (index * 4 + 2) <= length &&
                   (index * 4 + 3) > length) {

//          pData[4 * index]
            if (*pData[4 * index] > *pData[4 * index + 1] && *pData[4 * index] > *pData[4 * index + 2]) {
                swap(index, 4 * index);
                percolateDownMax(4 * index);

//          pData[4 * index + 1]
            } else if (*pData[4 * index + 1] > *pData[4 * index] && *pData[4 * index + 1] > *pData[4 * index + 2]) {
                swap(index, 4 * index + 1);
                percolateDownMax(index * 4 + 1);

//          pData[4 * index + 2]
            } else if (*pData[4 * index + 2] > *pData[4 * index + 1] && *pData[4 * index + 2] > *pData[4 * index]) {
                swap(index, 4 * index + 2);
                percolateDownMax(index * 4 + 2);
            }

//      If all four grandchildren are present
        } else if (4 * index + 3 <= length) {

//          pData[4 * index]
            if (*pData[4 * index] > *pData[4 * index + 1] && *pData[4 * index] > *pData[4 * index + 2] &&
                *pData[4 * index] > *pData[4 * index + 3]) {
                swap(index, 4 * index);
                percolateDownMax(4 * index);

//          pData[4 * index + 1]
            } else if (*pData[4 * index + 1] > *pData[4 * index] && *pData[4 * index + 1] > *pData[4 * index + 2] &&
                       *pData[4 * index + 1] > *pData[4 * index + 3]) {
                swap(index, 4 * index + 1);
                percolateDownMax(index * 4 + 1);

//          pData[4 * index + 2]
            } else if (*pData[4 * index + 2] > *pData[4 * index + 1] && *pData[4 * index + 2] > *pData[4 * index] &&
                       *pData[4 * index + 2] > *pData[4 * index + 3]) {
                swap(index, 4 * index + 2);
                percolateDownMax(index * 4 + 2);

//          pData[4 * index + 3]
            } else if (*pData[4 * index + 3] > *pData[4 * index + 1] && *pData[4 * index + 3] > *pData[4 * index] &&
                       *pData[4 * index + 3] > *pData[4 * index + 2]) {
                swap(index, 4 * index + 3);
                percolateDownMax(index * 4 + 3);
            }
        }
    }

//  Sole purpose of this method is to do the swaps after a deleteMin
    void percolateDownMin(int index) {

//      Base case
        if ((4 * index) > length) {
            return;
        }

//      Checks if there is only one grandchild
        if ((index * 4) <= length && (index * 4 + 1) > length) {
            swap(index, 4 * index);
            percolateDownMin(4 * index);

//      if there are only two grandchildren
        } else if ((index * 4) <= length && (index * 4 + 1) <= length && (index * 4 + 2) > length) {

//          pData[4 * index]
            if (*pData[4 * index] < *pData[4 * index + 1]) {
                swap(index, 4 * index);
                percolateDownMin(4 * index);

//          pData[4 * index + 1]
            } else if (*pData[4 * index + 1] < *pData[4 * index]) {
                swap(index, 4 * index + 1);
                percolateDownMin(index * 4 + 1);
            }

//      if there are only three grandchildren
        } else if ((index * 4) <= length && (index * 4 + 1) <= length && (index * 4 + 2) <= length &&
                   (index * 4 + 3) > length) {

//          pData[4 * index]
            if (*pData[4 * index] < *pData[4 * index + 1] && *pData[4 * index] < *pData[4 * index + 2]) {
                swap(index, 4 * index);
                percolateDownMin(4 * index);

//          pData[4 * index + 1]
            } else if (*pData[4 * index + 1] < *pData[4 * index] && *pData[4 * index + 1] < *pData[4 * index + 2]) {
                swap(index, 4 * index + 1);
                percolateDownMin(index * 4 + 1);

//          pData[4 * index + 2]
            } else if (*pData[4 * index + 2] < *pData[4 * index + 1] && *pData[4 * index + 2] < *pData[4 * index]) {
                swap(index, 4 * index + 2);
                percolateDownMin(index * 4 + 2);
            }

//      If all four grandchildren are present
        } else {

//          pData[4 * index]
            if (*pData[4 * index] < *pData[4 * index + 1] && *pData[4 * index] < *pData[4 * index + 2] &&
                *pData[4 * index] < *pData[4 * index + 3]) {
                swap(index, 4 * index);
                percolateDownMin(4 * index);

//          pData[4 * index + 1]
            } else if (*pData[4 * index + 1] < *pData[4 * index] && *pData[4 * index + 1] < *pData[4 * index + 2] &&
                       *pData[4 * index + 1] < *pData[4 * index + 3]) {
                swap(index, 4 * index + 1);
                percolateDownMin(index * 4 + 1);

//          pData[4 * index + 2]
            } else if (*pData[4 * index + 2] < *pData[4 * index + 1] && *pData[4 * index + 2] < *pData[4 * index] &&
                       *pData[4 * index + 2] < *pData[4 * index + 3]) {
                swap(index, 4 * index + 2);
                percolateDownMin(index * 4 + 2);

//          pData[4 * index + 3]
            } else if (*pData[4 * index + 3] < *pData[4 * index + 1] && *pData[4 * index + 3] < *pData[4 * index] &&
                       *pData[4 * index + 3] < *pData[4 * index + 2]) {
                swap(index, 4 * index + 3);
                percolateDownMin(index * 4 + 3);
            }
        }
    }

//  If the last level is even (min level), return true otherwise (max level) return false O(log(n))
    bool lastLevel(size_t size) {
        unsigned int cnt = 0;
        for (unsigned int i = size; i >= 2; i /= 2) {
            cnt++;
        }
        return cnt % 2 == 0;
    };

//  Returns how many values are in the heap
    size_t size() const { return length; };

    void swap(int index1, int index2) {
        if (index1 <= 0 || index2 <= 0) {
            return;
        }
        T *temp = pData[index1];
        pData[index1] = pData[index2];
        pData[index2] = temp;
    }

//  Checks to make sure that it is still a minmax heap
    void heapify(int index) {
        int level = static_cast<int> (log2(index));
        if (index <= 0) {
            return;
        }
        if (index > length) {
            return;

//      If it's on a min level
        } else if (level % 2 == 0) {

//          Checks if the value is less than the min level children
//          Checks if there are all four grandchildren
            if ((index * 4 + 3) < length) {

//              index * 4
                if (*pData[index * 4] < *pData[index] && *pData[4 * index] < *pData[4 * index + 1] &&
                    *pData[4 * index] < *pData[4 * index + 2] &&
                    *pData[4 * index] < *pData[4 * index + 3]) {
                    swap(index, index * 4);
                }

//              index * 4 + 1
                if (*pData[index * 4 + 1] < *pData[index] && *pData[4 * index + 1] < *pData[4 * index] &&
                    *pData[4 * index + 1] < *pData[4 * index + 2] &&
                    *pData[4 * index + 1] < *pData[4 * index + 3]) {
                    swap(index, index * 4 + 1);

//              index * 4 + 2
                } else if (*pData[index * 4 + 2] < *pData[index] && *pData[4 * index + 2] < *pData[4 * index] &&
                           *pData[4 * index + 2] < *pData[4 * index + 1] &&
                           *pData[4 * index + 2] < *pData[4 * index + 3]) {
                    swap(index, index * 4 + 2);

//              index * 4 + 3
                } else if (*pData[index * 4 + 3] < *pData[index] && *pData[4 * index + 3] < *pData[4 * index] &&
                           *pData[4 * index + 3] < *pData[4 * index + 1] &&
                           *pData[4 * index + 3] < *pData[4 * index + 2]) {
                    swap(index, index * 4 + 3);
                }

//          if only 3 grandchildren are present
            } else if ((index * 4 + 2) < length) {

//              index * 4
                if (*pData[index * 4] < *pData[index] && *pData[4 * index] < *pData[4 * index + 1] &&
                    *pData[4 * index] < *pData[4 * index + 2]) {
                    swap(index, index * 4);
                }

//              index * 4 + 1
                if (*pData[index * 4 + 1] < *pData[index] && *pData[4 * index + 1] < *pData[4 * index] &&
                    *pData[4 * index + 1] < *pData[4 * index + 2]) {
                    swap(index, index * 4 + 1);

//              index * 4 + 2
                } else if (*pData[index * 4 + 2] < *pData[index] && *pData[4 * index + 2] < *pData[4 * index] &&
                           *pData[4 * index + 2] < *pData[4 * index + 1]) {
                    swap(index, index * 4 + 2);
                }

//          Checks if there are only 2 grandchildren present
            } else if ((index * 4 + 1) < length) {

//              index * 4
                if (*pData[index * 4] < *pData[index] && *pData[4 * index] < *pData[4 * index + 1]) {
                    swap(index, index * 4);
                }

//              index * 4 + 1
                if (*pData[index * 4 + 1] < *pData[index] && *pData[4 * index + 1] < *pData[4 * index]) {
                    swap(index, index * 4 + 1);
                }

//          Checks if there is only one grandchild present
            } else if ((index * 4) < length) {
                swap(index, index * 4);
            }

//          Compares to max rows
            if ((index * 2 + 1) < length) {
                if (*pData[index * 2 + 1] < *pData[index] && *pData[index * 2 + 1] < *pData[index * 2]) {
                    swap(index, index * 2 + 1);
                    heapify(index * 2 + 1);
                } else if (*pData[index * 2] < *pData[index]) {
                    swap(index, index * 2);
                }
            } else if (index * 2 < length) {
                if (*pData[index * 2] < *pData[index]) {
                    swap(index, index * 2);
                }
            }

//      If it's on a max level
        } else if (level % 2 == 1) {

//          Checks if the value is greater than the max level children
//          Checks if there are all four grandchildren
            if ((index * 4 + 3) < length) {

//              index * 4
                if (*pData[index * 4] > *pData[index] && *pData[4 * index] > *pData[4 * index + 1] &&
                    *pData[4 * index] > *pData[4 * index + 2] &&
                    *pData[4 * index] > *pData[4 * index + 3]) {
                    swap(index, index * 4);
                }

//              index * 4 + 1
                if (*pData[index * 4 + 1] > *pData[index] && *pData[4 * index + 1] > *pData[4 * index] &&
                    *pData[4 * index + 1] > *pData[4 * index + 2] &&
                    *pData[4 * index + 1] > *pData[4 * index + 3]) {
                    swap(index, index * 4 + 1);

//              index * 4 + 2
                } else if (*pData[index * 4 + 2] > *pData[index] && *pData[4 * index + 2] > *pData[4 * index] &&
                           *pData[4 * index + 2] > *pData[4 * index + 1] &&
                           *pData[4 * index + 2] > *pData[4 * index + 3]) {
                    swap(index, index * 4 + 2);

//              index * 4 + 3
                } else if (*pData[index * 4 + 3] > *pData[index] && *pData[4 * index + 3] > *pData[4 * index] &&
                           *pData[4 * index + 3] > *pData[4 * index + 1] &&
                           *pData[4 * index + 3] > *pData[4 * index + 2]) {
                    swap(index, index * 4 + 3);
                }

//          if only 3 grandchildren are present
            } else if ((index * 4 + 2) < length) {

//              index * 4
                if (*pData[index * 4] > *pData[index] && *pData[4 * index] > *pData[4 * index + 1] &&
                    *pData[4 * index] > *pData[4 * index + 2]) {
                    swap(index, index * 4);
                }

//              index * 4 + 1
                if (*pData[index * 4 + 1] > *pData[index] && *pData[4 * index + 1] > *pData[4 * index] &&
                    *pData[4 * index + 1] > *pData[4 * index + 2]) {
                    swap(index, index * 4 + 1);

//          index * 4 + 2
                } else if (*pData[index * 4 + 2] > *pData[index] && *pData[4 * index + 2] > *pData[4 * index] &&
                           *pData[4 * index + 2] > *pData[4 * index + 1]) {
                    swap(index, index * 4 + 2);
                }

//          Checks if there are only 2 grandchildren present
            } else if ((index * 4 + 1) <= length) {

//          index * 4
                if (*pData[index * 4] > *pData[index] && *pData[4 * index] > *pData[4 * index + 1]) {
                    swap(index, index * 4);
                }

//              index * 4 + 1
                if (*pData[index * 4 + 1] > *pData[index] && *pData[4 * index + 1] > *pData[4 * index]) {
                    swap(index, index * 4 + 1);
                }

//          Checks if there is only one grandchild present
            } else if ((index * 4) < length) {
                if (*pData[4 * index] > *pData[index]) {
                    swap(index, index * 4);
                }
            }

//          Compares to min rows
            if ((index * 2 + 1) < length) {
                if (*pData[index * 2 + 1] > *pData[index] && *pData[index * 2 + 1] > *pData[index * 2]) {
                    swap(index, index * 2 + 1);
                    heapify(index * 2 + 1);
                } else if (*pData[index * 2] > *pData[index]) {
                    swap(index, index * 2);
                }
            } else if ((index * 2) < length) {
                if (*pData[index * 2] > *pData[index]) {
                    swap(index, index * 2);
                }
            }
        }
        heapify(index * 2);
        heapify(index * 2 + 1);
    }

//  Main insert method that sort of acts like a bootstrap
    void insert(T *px) {

//      Checks for if the length is going to be greater than the capacity, then grows the array
        if (length++ == capacity) {
            grow();
        }

//      Checks for first insertion
        if (length == 1) {
            pData[0] = nullptr;
            pData[1] = px;
            return;

//      Checks for second insertion
        } else if (length == 2) {
            if (*pData[1] > *px) {
                pData[2] = pData[1];
                pData[1] = px;
                return;
            }
            pData[2] = px;
            return;
        }

//      Initial insert
        pData[length] = px;

//      Function Call
        insertHelp(length);
    };

//  Helper method for Insert that recursively places nodes
    void insertHelp(size_t size) {

//  Checks to see whether the last level is a min or a max level
        if (!lastLevel(size)) {

//          Base Case
            if (size < 2) {
                return;

//          Compares to the next min row
            } else if (size / 4 >= length) {
                if (*pData[size] > *pData[size / 4]) {
                    swap(size, size / 4);
                    insertHelp(size / 4);
                }
            }

//          Compares to the next max row
            if (*pData[size] < *pData[(size) / 2]) {
                swap(size, size / 2);
                insertHelp(size / 2);

//          If it's in the right place
            } else {
                return;
            }
        } else {

//          Base Case
            if (size < 2) {
                return;

//        Compares to the next max row
            } else if ((size / 4) != 0) {
                if (*pData[size] < *pData[size / 4]) {
                    swap(size, size / 4);
                    insertHelp(size / 4);
                }
            }

//          Compares to the next min row
            if (*pData[size] > *pData[(size) / 2]) {
                swap(size, size / 2);
                insertHelp(size / 2);

//        If it's in the right spot
            } else {
                return;
            }
        }
    }

//  Essentially "Dumps" all of the necessary debugging information for the heap
    void dump() {
        cout << "---------------------------------------" << endl;
        cout << "--- min-max heap dump --- " << endl;
        cout << "Size: " << length << endl;
        cout << "Minimum: " << *getMin() << endl;
        cout << "Maximum: " << *getMax() << endl;
        if (lastLevel(length))
            cout << "Last Level is even" << endl;
        else
            cout << "Last Level is odd" << endl;
        cout << "Total Height of Tree: " << static_cast<int> (log2(length)) + 1 << endl;
        cout << "--- heap data items --- " << endl;
        for (unsigned int i = 1; i < length + 1; i++) {
            cout << "H[" << i << "] = " << *pData[i] << endl;
        }
    };

//  Return the min value in the heap
    T *getMin() {
        return pData[1];
    };

//  Return the max value in the heap
    T *getMax() {
        if (length == 1) {
            return pData[1];
        } else if (length == 2) {
            return pData[2];
        } else if (*pData[2] > *pData[3]) {
            return pData[2];
        } else {
            return pData[3];
        }
    };

//  Deletes the min value in the heap
    T deleteMin() {

//      Check for edge case where there's nothing to delete
        if (length == 0) {
            cout << "Cannot deleteMin() when there is no valid length" << endl;
            return T();
        }

//      Replace root with last value in tree
        pData[1] = pData[length--];
        percolateDownMin(1);
        heapify(1);
        return *pData[length + 1];
    };

//  Deletes the max value in the heap
    T deleteMax() {

//      Checks for edge case
        if (length == 0) {
            cout << "Cannot deleteMin() when there is no valid length" << endl;
            return T();

//      Edge case for if length is 1
        } else if (length == 1) {
            pData[--length] = new T();
            return *pData[length + 1];

//      Edge case for if length is 2
        } else if (length == 2) {
            pData[--length] = new T();
            return *pData[length + 1];

//      Checks for whether the second node or first node is bigger
        } else if (*pData[2] >= *pData[3]) {
            pData[2] = pData[length--];
            percolateDownMax(2);
            heapify(2);
            return *pData[length + 1];
        } else {
            pData[3] = pData[length--];
            percolateDownMax(3);
            heapify(3);
            return *pData[length + 1];
        }
    };

};


#endif //PROJECTTHREE_MMHEAP_H
