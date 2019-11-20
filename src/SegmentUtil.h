#ifndef SEGMENTUTIL_H
#define SEGMENTUTIL_H
#include "Segment.h"
#include <vector>


struct SegmentUtil
{
    static std::vector< std::vector<Segment> > sort(const std::vector<Segment>& segs);
    static void join(std::vector<Segment>& segs);
    static bool join2(Segment& s1, const Segment& s2);
    
    template <class F>
    static void asPath(const std::vector<Segment>& segs, F f) {
        for (const auto& s : segs) {
            f(s.points[0]);
        }
    }
};


#endif


