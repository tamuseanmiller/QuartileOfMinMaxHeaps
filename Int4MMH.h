///////////////////////////////////////////////////////////////
//  File:   Int4MMH
//  Course: CSCE-221 Data Structures & Algorithms
//  Author: Sean Miller
//  Date:   10/24/2019
//  Usage:  TODO
///////////////////////////////////////////////////////////////

//
// Created by Sean on 10/24/2019.
//

#ifndef PROJECTTHREE_INT4MMH_H
#define PROJECTTHREE_INT4MMH_H

#include <ostream>

class Int4MMH {
public:
    Int4MMH() : num(new int(-1)) {};

    explicit Int4MMH(int n1) : num(new int(n1)) {};

    ~Int4MMH() {
        num = nullptr;
        delete num;
    };

    int *getNum() { return num; }

    Int4MMH &operator=(int* equal) {
        num = equal;
        return *this;
    };

    bool operator<(const Int4MMH &rhs) const {
        return *num < *rhs.num;
    }

    bool operator>(const Int4MMH &rhs) const {
        return *num > *rhs.num;
    }

    friend std::ostream &operator<<(std::ostream &os, const Int4MMH &mmh) {
        os << *mmh.num;
        return os;
    }

    bool operator<=(const Int4MMH &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Int4MMH &rhs) const {
        return !(*this < rhs);
    }

private:
    int *num;
};


#endif //PROJECTTHREE_INT4MMH_H
