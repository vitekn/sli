#include "TriangleUtil.h"
#include <algorithm>
#include <iostream>

Point TriangleUtil::calcNormale(const Triangle& t)
{
    Point u = t.points[1] - t.points[0];
    Point v = t.points[2] - t.points[0];
 
    return { (u.y * v.z) - (u.z*v.y),
              (u.z * v.x) - (u.x * v.z),
              (u.x * v.y) - (u.y * v.x) };
}

std::tuple<bool, Point2> intersectSecionZ(const Point& pb, const Point& pa, int z)
{
    
    if (pa.z >= z && pb.z <= z) {
        Point d = pa - pb;
        //std::cout << "diff " << d <<std::endl;
        int64_t dz = z - pb.z; 
        if (dz) {
            int64_t x = pb.x + (d.x*dz)/d.z;
            int64_t y = pb.y + (d.y*dz)/d.z;
            return std::tuple<bool, Point2>(true, {x, y});
        }
    }
    
    return std::tuple<bool, Point2>(false, {0, 0});
    
}

std::tuple<bool, Segment> TriangleUtil::intersectZ(const Triangle& t, uint64_t z)
{
    bool res;
    Segment s;
    int sc = 0;
        
    if (t.points[0].z == z && t.points[1].z == z && t.points[2].z == z) {
        return std::tuple<bool, Segment>(false, s);
    }
    
    for (int i = 0; i < 3; ++i) {
        const Point& p1 = t.points[i];
        const Point& p2 = t.points[(i+1)%3];
        
        if (p1.z == p2.z && p2.z == z) {
            s.points[0] = {p1.x, p1.y};
            s.points[1] = {p2.x, p2.y};
            sc = 2;
            break;
        }
        const Point* ppa;
        const Point* ppb;
        std::tie(ppb, ppa) = PointUtil::orderByZ(p1, p2);
        auto r = intersectSecionZ(*ppb, *ppa, z);
        if (std::get<0>(r)) {
            if (sc == 0) {
                s.points[0] = std::get<1>(r);
                ++sc;
            } else {
                if (s.points[0] != std::get<1>(r)) {
                    s.points[1] = std::get<1>(r);
                    ++sc;
                    break;
                }
            }
        }
        
    }
    
    res = (sc == 2);
    if (res) {
        s.k = ((double)t.normal.y) / (double)t.normal.x;
        
        s.sign = t.normal.x != 0 ?  t.normal.x/std::abs(t.normal.x) : 0;
    }
    
    return std::tuple<bool, Segment>(res, s);
}


std::istream& operator>>(std::istream& is, Triangle& p){
    if (is.iword(PointUtil::getPointFormatIdx()) == 0) {
        std::string tmp;
        tmp.reserve(10);
        is >> tmp;
        if (tmp != "normal") {
            is.fail();
            return is;
        }
        is >> p.normal;
        is >> tmp;
        if (tmp != "outer") {
            is.fail();
            return is;
        }
        is >> tmp;
        if (tmp != "loop") {
            is.fail();
            return is;
        }
        for (int i = 0; i < 3; ++i) {
            is >> tmp;
            if (tmp != "vertex") {
                is.fail();
                return is;
            }
            is >> p.points[i];
        }
        is >> tmp;
        if (tmp != "endloop") {
            is.fail();
            return is;
        }
        is >> tmp;
        if (tmp != "endfacet") {
            is.fail();
            return is;
        }
    }
    else {
        is >> p.normal >> p.points[0] >> p.points[1] >> p.points[2];
        is.ignore(2);
    }
    
    return is;
}

