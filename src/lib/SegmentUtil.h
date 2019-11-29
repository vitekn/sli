#ifndef SEGMENTUTIL_H
#define SEGMENTUTIL_H
#include "Segment.h"
#include <tuple>
#include <vector>
#include "Types.h"

struct SegmentUtil
{
    static Polygons sort(const std::vector<Segment>& segs);
    static void join(Polygon& segs);
    static bool join2(Segment& s1, const Segment& s2);
    
    template <class F>
    static void asPath(const std::vector<Segment>& segs, F f) {
        for (const auto& s : segs) {
            f(s.points[0]);
        }
    }
    
    static std::tuple<bool, Point2> haveIntersection(const Segment& s1, const Segment& s2);
    
    struct PointPosition {
        enum {
            INSIDE,
            OUTSIDE,
            ONLINE,
        };
    };
    
    static int getPointPosition(const Point2& subj, const Segment& section);
    static int64_t getYOnLine(int64_t x, const Segment& seg);
    
//    static Segment moveSegmentOnNorm(const Segment& seg, int64_t offset);
    static void midOffset(Segment& seg1, Segment& seg2, int64_t offset);
    
    
  //  double getK(const Segment& s);
//    bool hasPoint(const Segment& s, const Point2& p);
};


#endif


