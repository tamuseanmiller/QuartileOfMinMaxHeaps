///////////////////////////////////////////////////////////////
//  File:   CensusCity
//  Course: CSCE-221 Data Structures & Algorithms
//  Author: Sean Miller
//  Date:   10/24/2019
//  Usage:  TODO
///////////////////////////////////////////////////////////////

#pragma once

#include <string>

class CensusCity {
    std::string city;
    std::string state;
    int census2010;
    int estimate2011;
    bool use2011;

public:
    CensusCity() : city(""), state(""), census2010(0), estimate2011(0), use2011(false) {};

    CensusCity(std::string &aCity, std::string &aState, int n1, int n2, bool tf) : city(aCity), state(aState),
                                                                                 census2010(n1), estimate2011(n2),
                                                                                 use2011(tf) {};

    ~CensusCity() = default;

    std::string toString() {
        return city + ", " + state + " (" + std::to_string(census2010) + ", " + std::to_string(estimate2011) + ")";
    }

    friend int compare(const CensusCity &c1, const CensusCity &c2);

    bool operator<(const CensusCity &rhs) const;

    bool operator>(const CensusCity &rhs) const;

    bool operator<=(const CensusCity &rhs) const;

    bool operator>=(const CensusCity &rhs) const;
};

int compare(const CensusCity &c1, const CensusCity &c2) {
    if (c1.use2011) {
        if (c1.estimate2011 < c2.estimate2011)
            return -1;
        if (c1.estimate2011 > c2.estimate2011)
            return 1;
        return 0;
    } else {
        if (c1.census2010 < c2.census2010)
            return -1;
        if (c1.census2010 > c2.census2010)
            return 1;
        return 0;
    }
}

bool CensusCity::operator<(const CensusCity &rhs) const {
    if (use2011) {
        if (estimate2011 < rhs.estimate2011)
            return true;
        if (rhs.estimate2011 < estimate2011)
            return false;
        return false;
    } else {
        if (census2010 < rhs.census2010)
            return true;
        if (rhs.census2010 < census2010)
            return false;
        return false;
    }
}

bool CensusCity::operator>(const CensusCity &rhs) const {
    return rhs < *this;
}

bool CensusCity::operator<=(const CensusCity &rhs) const {
    return !(rhs < *this);
}

bool CensusCity::operator>=(const CensusCity &rhs) const {
    return !(*this < rhs);
}
