#ifndef POLYGONUTIL_H
#define POLYGONUTIL_H

#include "Types.h"
#include <map>

struct PolygonUtil {
    
    static Polygons offset(const Polygon& p, int64_t offset);

    struct Intersection {
        Segment s;
        Point2  ip;
    };
//    static std::vector<Intersection> getSortedIntersections(const Polygon& p, const Segment& s);
    
    class Intersector {
    public:
        Intersector (Polygon* p);
        
        std::vector<Intersection> getSortedIntersections(const Segment& s);
        
    private:
        Polygon* _p;
        std::vector<Point2> _max;
        std::vector<Point2> _min;
    };
    
};




#endif

