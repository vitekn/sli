#include "PolygonUtil.h"
#include "SegmentUtil.h"
#include <algorithm>
#include <unordered_map>
#include <assert.h>
// construct insert segs by dividing by intersections, map pt->segs, some segs -> poly, some -> discard
Polygons PolygonUtil::offset(const Polygon& p, int64_t offset)
{
    if (p.size() < 3) {
        return Polygons (1, p);
    }
    
    Polygon tmp = p;
    auto it = tmp.begin();
    auto nit = ++it;
    for (;nit != tmp.end(); ++it, ++nit) {
        SegmentUtil::midOffset(*it, *nit, offset);
    }
    SegmentUtil::midOffset(tmp.back(), tmp.front(), offset);

    Polygons res;

    std::unordered_multimap<Point2, Segment> segments;
    
    Intersector ior(&tmp);
    for (Segment& s : tmp) {
        
        auto segs = ior.getSortedIntersections(s);
        assert (segs.size() > 1);
        
        Point2 fp = segs.front().ip;
        
        auto it = segs.begin();
        ++it;
        for (; it != segs.end(); ++it) { //add check for dups, if any delete both
            segments.insert({fp,     {{it->ip, fp}, {s.normale}, s.k, s.sign}});
            segments.insert({it->ip, {{fp, it->ip}, {s.normale}, s.k, s.sign}});
            fp = it->ip;
        }
    }
    
    while (!segments.empty()) {
        auto mit = segments.begin();
        Point2 curr = mit->first;
        Point2 nextKey = mit->second.points[0];
        auto range = segments.equal_range(nextKey);
        res.emplace_back();
        bool discard = false;
        
        while (range.first != range.second) {
            
            auto ssegit = range.first;
            
            for (; ssegit != range.second; ++ssegit) {
                if (ssegit->second.points[0] == curr) {
                    break;
                }
            }
            res.back().emplace_back(ssegit->second);
            curr = nextKey;
            
            
            if (std::distance(range.first, range.second) > 2) {
                
                std::unordered_multimap<Point2, Segment>::iterator minAit;
                std::unordered_multimap<Point2, Segment>::iterator maxAit;
                int64_t maxA = std::numeric_limits<int64_t>::min();
                int64_t minA = std::numeric_limits<int64_t>::max();
                
                for (auto oit = range.first; oit != range.second; ++oit) {
                    if (oit == ssegit) {
                        continue;
                    }
                    Segment tmps = oit->second;
                    std::swap(tmps.points[0], tmps.points[1]);
                    int64_t angle = SegmentUtil::getAngle(ssegit->second, tmps);
                    if ( angle >= maxA ) {
                        maxA = angle;
                        maxAit = oit;
                    }
                    if ( angle <= minA ) {
                        minA = angle;
                        minAit = oit;
                    }
                }
                
                //try maxA -> if internal region - take it
                
                if (SegmentUtil::validCorner(ssegit->second, maxAit->second, maxA)) {
                    //match
                        nextKey = maxAit->second.points[0];
                        segments.erase(maxAit);
                } else {
                    if (SegmentUtil::validCorner(ssegit->second, minAit->second, minA)) {
                        // match - discard
                        discard = true;
                        nextKey = minAit->second.points[0];
                        segments.erase(minAit);
                    }
                    else {
                        assert(false && "smth worng");
                    }
                        
                }
                
            }
            else {

                auto oit = ssegit == range.first ? range.second : range.first;
                nextKey = oit->second.points[0];
                segments.erase(oit);
            }
            
            segments.erase(ssegit);
            
            range = segments.equal_range(nextKey);
        }

        // no more segments in poly, take arbitrary if exists
        if (discard) {
            res.pop_back();
        }
    }
    
    return res;
}


PolygonUtil::Intersector::Intersector(Polygon* p)
: _p(p)
{
    Polygon& lp = *_p;
    _max.reserve(lp.size());
    _min.reserve(lp.size());
    for (size_t i = 0; i < lp.size(); ++i) {
        _max.emplace_back(Point2{std::max(lp[i].points[0].x, lp[i].points[1].x), std::max(lp[i].points[0].y, lp[i].points[1].y)});
        _min.emplace_back(Point2{std::max(lp[i].points[0].x, lp[i].points[1].x), std::max(lp[i].points[0].y, lp[i].points[1].y)});
    }
}

std::vector<PolygonUtil::Intersection> PolygonUtil::Intersector::getSortedIntersections(const Segment& s)
{
    
        std::unordered_map<size_t, int> pnm;
        Polygon& lp = *_p;
        
        int64_t mix = std::min(s.points[0].x, s.points[1].x);
        int64_t max = std::max(s.points[0].x, s.points[1].x);
        int64_t miy = std::min(s.points[0].y, s.points[1].y);
        int64_t may = std::max(s.points[0].y, s.points[1].y);

        std::vector<Intersection> ips;
        
        for (size_t i = 0; i < lp.size(); ++i) {
            if (&s == &lp[i]) {
                continue;
            }
            
            if (_min[i].x > max || _max[i].x < mix || _min[i].y > may || _max[i].y < miy) {
                continue;
            }

            bool r;
            Point2 ip;
            std::tie(r, ip) =  SegmentUtil::haveIntersection(s, lp[i]);
            if (r) {
                ips.emplace_back(Intersection{lp[i], ip});
            }
        }
    
        //sort ips reging to s.p[0]
        const Point2& sp = s.points[0];
        std::sort(ips.begin(), ips.end(), [&sp](const Intersection& i1, const Intersection& i2)->bool{
            Point2 d1 = sp - i1.ip;
            Point2 d2 = sp - i2.ip;
            return ((d1.x * d1.x) + (d1.y * d1.y)) < ((d2.x * d2.x) + (d2.y * d2.y));
        });
        
        return ips;
}
