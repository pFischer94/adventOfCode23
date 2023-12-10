#ifndef RANGE_WITH_ADDEND_H
#define RANGE_WITH_ADDEND_H

#include "Range.h"

class RangeWithAddend : Range {

    long addend;

public:
    RangeWithAddend(long start, long end, long addend) : Range(start, end), addend(addend) {}
    long getAddend() { return addend; }

};

#endif