#ifndef SEGMENTUTIL_H
#define SEGMENTUTIL_H
#include "Segment.h"
#include <vector>


struct SegmentUtil
{
    static std::vector< std::vector<Segment> > sort(const std::vector<Segment>& segs);
    static void join(std::vector<Segment>& segs);
    static bool join2(Segment& s1, const Segment& s2);
};


#endif


