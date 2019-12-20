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
    
    static std::tuple<bool, Point2> haveIntersection(const Segment& s1, const Segment& s2); // t+
    
    struct PointPosition {
        enum {
            INSIDE,
            OUTSIDE,
            ONLINE,
        };
    };
    
    static int getPointPosition(const Point2& subj, const Segment& section); // t+
    static int64_t getYOnLine(int64_t x, const Segment& seg); // t+
    
//    static Segment moveSegmentOnNorm(const Segment& seg, int64_t offset);
    static void midOffset(Segment& seg1, Segment& seg2, int64_t offset); // t+
    
    // s1.p1 == s2.p0
    static bool    validCorner(const Segment& s1, const Segment& s2, int64_t angle);
    static int64_t getAngle(const Segment& s1, const Segment& s2);
    static int64_t getAngle(const Point2& p1, const Point2& p2);
    static double  areaV(const Point2& p1, const Point2& p2);
    static double  cosA (const Point2& p1, const Point2& p2, double areaV);
    static double  sinA (const Point2& p1, const Point2& p2, double areaV);
    static constexpr Segment reverse(const Segment& s)
    {
        return {{s.points[1], s.points[0]}, s.normale, s.k, s.sign};
    }

    
  //  double getK(const Segment& s);
//    bool hasPoint(const Segment& s, const Point2& p);
};


#endif


