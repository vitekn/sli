#ifndef SEGMENT_H
#define SEGMENT_H
#include "Point2.h"
#include <stdint.h>
#include <ostream>

struct Segment
{
    Point2 points[2];
    double k;
    int    sign;

};

inline 
std::ostream& operator<<(std::ostream& os, const Segment s)
{
    os << "[(" << s.points[0].x << ", " << s.points[0].y
       << ") -> (" << s.points[1].x << ", " << s.points[1].y
       << ") k = " << s.k << " s = " << s.sign << "]";
    return os;
}

#endif
