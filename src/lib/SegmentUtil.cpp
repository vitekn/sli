#include "SegmentUtil.h"

#include "Point2.h"
#include "Types.h"
#include <algorithm>
#include <assert.h>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <cmath>

Polygons SegmentUtil::sort(const std::vector<Segment>& segs)
{
    typedef std::unordered_multimap<Point2, const Segment*> SMap;
    typedef std::unordered_set<const Segment*> SSet;

    if (segs.size() < 3){
        return std::vector<std::vector<Segment> >(1, segs);
    }
    
    SMap map;
    for (const auto& s : segs) {
        if(s.points[0] != s.points[1]) {
            map.insert({s.points[0], &s});
            map.insert({s.points[1], &s});
        }
    }
    
    std::vector<std::vector<Segment> > res;
    res.push_back(std::vector<Segment>());
    std::vector<Segment>* cs = &res.back();

    SSet set;
    const Segment* fp = &segs.front();
    Point2 fpp = fp->points[1];
    set.insert(fp);
    cs->push_back(*fp);
    
    while (!map.empty()) {
        auto itp = map.equal_range(fpp);
        size_t n = std::distance(itp.first, itp.second);

        assert (n == 2);

        auto it1 = itp.first;
        auto it2 = itp.first;
        ++it2;

        const Segment* sp = (it1->second == fp) ? sp = it2->second : sp = it1->second;
        
        map.erase(fpp);
        fp = sp;

        if (set.find(sp) == set.end()) {
            set.insert(sp);
            Segment sa = *sp;
            if (fpp != sa.points[0]) {
                std::swap(sa.points[0], sa.points[1]);
            }
            fpp = sa.points[1];
            cs->push_back(sa);
            
        } else {
            if (!map.empty()) {
                
                res.push_back(std::vector<Segment>());
                cs = &res.back();
                fp = map.begin()->second;
                fpp = fp->points[1];
                set.insert(fp);
                cs->push_back(*fp);
            }
        }
    }
    return res;
}

bool SegmentUtil::join2(Segment& s1, const Segment& s2)
{
    if (s1.k == s2.k && s1.sign == s2.sign) {
        if (s1.points[1] == s2.points[0]) {
            s1.points[1] = s2.points[1];
            return true;
        }
        else if (s1.points[0] == s2.points[1]) {
            s1.points[0] = s2.points[0];
            return true;
        }
    }
    return false;
}


void SegmentUtil::join(Polygon& segs)
{
    if (segs.size() < 2) {
        return;
    }
    auto it = segs.begin();
    auto nit = it;
    ++nit;

    while (nit != segs.end()) {
        while (nit != segs.end() && join2(*it,*nit)) {
            ++nit;
        }
        if (nit == segs.end()) {
            break;
        }
        ++it;
        *it = *nit;
        ++nit;
    }

    if (join2(* segs.begin(),*it)) {
        --it;
    }
    size_t d = it - segs.begin() + 1;
    segs.resize(d);
}
/*
double SegmentUtil::getK(const Segment& s)
{
    const Point2 *p1 = &s.points[0];
    const Point2 *p2 = &s.points[1];
    
    if (p1->x > p2->x) {
        std::swap(p1, p2);
    }
    
    return ((double)(p1->y - p2->y))/((double)(p2->x - p1->x));
}
// */

/*bool SegmentUtil::hasPoint(const Segment& s, const Point2& p)
{
    return false;
}*/


std::tuple<bool, Point2> SegmentUtil::haveIntersection(const Segment& s1, const Segment& s2)
{
    
    int64_t s1_x = s1.points[1].x - s1.points[0].x;
    int64_t s1_y = s1.points[1].y - s1.points[0].y;
    int64_t s2_x = s2.points[1].x - s2.points[0].x;
    int64_t s2_y = s2.points[1].y - s2.points[0].y;

    int64_t d = -s2_x * s1_y + s1_x * s2_y;
    
    if (!d) {
        return std::tuple<bool, Point2>(false,{});
    }
    
    double s = (double)(-s1_y * (s1.points[0].x - s2.points[0].x) + s1_x * (s1.points[0].y - s2.points[0].y)) / (double)(d);
    if ( s < 0 || s > 1) {
        return std::tuple<bool, Point2>(false,{});
    }
    
    double t = (double)( s2_x * (s1.points[0].y - s2.points[0].y) - s2_y * (s1.points[0].x - s2.points[0].x)) / (double)(d);

    
    if (t >= 0 && t <= 1) {
        return std::tuple<bool, Point2>(true,{(int64_t)(s1.points[0].x + (t * s1_x)), (int64_t)(s1.points[0].y + (t * s1_y))});
    }

    return std::tuple<bool, Point2>(false,{});
    
}

int64_t SegmentUtil::getYOnLine(int64_t x, const Segment& seg)
{
    int64_t dx = seg.points[0].x - seg.points[1].x;
    int64_t dy = seg.points[0].y - seg.points[1].y;
    int64_t dsx = seg.points[0].x - x;
    volatile int64_t m = dsx*dy;

    return seg.points[0].y - m/dx;
    
}


int SegmentUtil::getPointPosition(const Point2& subj, const Segment& section)
{
    if (section.points[0].x == section.points[1].x) {
        int64_t nxd = section.points[0].x - subj.x;
        if (!nxd) {
            return PointPosition::ONLINE;
        }
        if (nxd * section.sign < 0) {
            return PointPosition::OUTSIDE;
        } 
        return PointPosition::INSIDE;
    }
    
    int64_t nyd = subj.y - getYOnLine(subj.x, section);
    
    if (!nyd) {
        return PointPosition::ONLINE;
    }
    
    if ((((int64_t)std::copysign(1,section.k)) ^ section.sign ^ nyd) & 0x8000000000000000) {
        return PointPosition::INSIDE;
    } 
    return PointPosition::OUTSIDE;

}

/*Segment SegmentUtil::moveSegmentOnNorm(const Segment& seg, int64_t offset)
{
    int64_t dx = offset * seg.normale.x;
    int64_t dy = offset * seg.normale.y;
    //dx = (offset*offset)/(1 + seg.k * seg.k);
    Segment res = seg;
    res.points[0].x = seg.points[0].x + dx;
    res.points[1].x = seg.points[1].x + dx;
    res.points[0].y = seg.points[0].y + dy;
    res.points[1].y = seg.points[1].y + dy;
    return res;
    
}*/

void SegmentUtil::midOffset(Segment& seg1, Segment& seg2, int64_t offset)
{
        
    Point2 md = { seg1.normale.x + seg2.normale.x, seg1.normale.y + seg2.normale.y };
    
    md = Point2Util::normalize(md);
    //Point2 md2{-seg1.normale.y, seg1.normale.x};
    const Point2& md2 = { -seg1.normale.x, -seg1.normale.y} ;
    int64_t cp = md.x * md2.x + md.y * md2.y; // /1 000 000
    
    md *= (offset * 1000);
    md /= cp;
    
    assert (seg1.points[1] == seg2.points[0]);
    seg1.points[1] += md;
    seg2.points[0] = seg1.points[1];
}

double SegmentUtil::areaV(const Point2& p1, const Point2& p2)
{
    return std::sqrt(p1.x*p1.x + p1.y*p1.y) * std::sqrt(p2.x*p2.x + p2.y*p2.y);
}


double SegmentUtil::sinA(const Point2& p1, const Point2& p2, double areaV)
{
    
    return (double(p1.x * p2.y - p1.y * p2.x)) / areaV; // 1..-1 = 2..0
}


double SegmentUtil::cosA(const Point2& p1, const Point2& p2, double areaV)
{
    
    int64_t p = (p1.x * p2.x + p1.y * p2.y);
    double res = ((double)(p)) / areaV;
    return res; // 1..-1 = 2..0
}

int64_t SegmentUtil::getAngle(const Point2& p1, const Point2& p2)
{
    double a = areaV(p1, p2);
    double c = cosA(p1 ,p2, a);
    double s = sinA(p1 ,p2, a);
    c += 1;
    if (s < 0) {
        c = -c;
    }
    return (int64_t(c * std::numeric_limits<int64_t>::max()/2));
}

int64_t SegmentUtil::getAngle(const Segment& s1, const Segment& s2)
{
    assert (s1.points[1] == s2.points[0]);

    Point2 p1 = s1.points[0] - s1.points[1];
    Point2 p2 = s2.points[1] - s2.points[0];

    double cA = cosA(p1, p2, areaV(p1, p2)) + 1;

    if(getPointPosition(s2.points[1], s1) == PointPosition::OUTSIDE) {
        cA = -cA;
    }
    return (int64_t(cA * std::numeric_limits<int64_t>::max()/2));
}

bool SegmentUtil::validCorner(const Segment& s1, const Segment& s2, int64_t angle)
{
    assert (s1.points[1] == s2.points[0]);
    int64_t ccwAngle = getAngle(s1.points[0] - s1.points[1],
                                s2.points[1] - s2.points[0]);
    
    int64_t normAngle = getAngle(s1.normale, s2.normale);
    
    int64_t rs = ~(ccwAngle ^ angle);
    
    return (((((normAngle ^ angle)) ^ rs) & 0x8000'0000'0000'0000) == 0);
}


