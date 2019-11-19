#ifndef TRIANGLEUTIL_H
#define TRIANGLEUTIL_H

#include "PointUtil.h"
#include "Segment.h"
#include "Triangle.h"
#include <istream>
#include <string>
#include <tuple>


struct TriangleUtil
{
    static Point calcNormale(const Triangle& t);
    static std::tuple<bool, Segment> intersectZ(const Triangle& t, uint64_t z);
    
};

std::istream& operator>>(std::istream& is, Triangle& p);

#endif
