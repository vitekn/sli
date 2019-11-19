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

std::tuple<bool, Segment> TriangleUtil::intersectZ(const Triangle& t, uint64_t z)
{
    bool res;
    Segment s;
    int sc = 0;
    for (int i = 0; i < 3; ++i) {
        const Point& p1 = t.points[i];
        const Point& p2 = t.points[(i+1)%3];
        const Point* ppa;
        const Point* ppb;
        if (p1.z > p2.z) {
            ppa = &p1;
            ppb = &p2;
        } else {
            ppb = &p1;
            ppa = &p2;
        }
        
        if (ppa->z >= z && ppb->z <= z) {
            Point d = *ppa - *ppb;
            //std::cout << "diff " << d <<std::endl;
            int64_t dz = z - ppb->z; 
            if (dz) {
                int64_t x = ppb->x + (d.x*dz)/d.z;
                int64_t y = ppb->y + (d.y*dz)/d.z;
                if (sc < 2) {
                    s.points[sc].x = x;
                    s.points[sc].y = y;
                }
                ++sc;
            }
        }
    }
    
    res = (sc == 2);
    if (res) {
        s.k = ((double)t.normal.y) / (double)t.normal.x;
        
        s.sign = t.normal.x != 0 ?  t.normal.x/std::abs(t.normal.x) : 0;
    }
    
    return std::tie(res, s);
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

