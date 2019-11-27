#include "PolygonUtil.h"
#include "SegmentUtil.h"
#include <algorithm>
#include <unordered_map>
#include <assert.h>

Polygon PolygonUtil::offset(const Polygon& p, int64_t offset)
{
    if (p.size() < 3) {
        return p;
    }
    
    Polygon tmp = p;
    auto it = tmp.begin();
    auto nit = ++it;
    for (;nit != tmp.end(); ++it, ++nit) {
        SegmentUtil::midOffset(*it, *nit, offset);
    }
    SegmentUtil::midOffset(tmp.back(), tmp.front(), offset);
    
    Polygon res;
    res.reserve(p.size());

    
    while (!tmp.empty()) {
        Polygon tmp2;
        Intersector ior(&tmp);
        for (it = tmp.begin(); it != tmp.end(); ++it) {
            auto segs = ior.getSortedIntersections(*it);
            if (segs.empty()) {
                res.emplace_back(*it);
                it->normale = {0, 0};
            } else {
                
                int pp = SegmentUtil::getPointPosition(it->points[0], segs.front().s);
                Point2 *sp = &(it->points[0]);
                bool cut = false;
                switch(pp) {
                    case SegmentUtil::PointPosition::INSIDE:
                        //keep
                        cut = false;
                    break;
                    case SegmentUtil::PointPosition::OUTSIDE:
                        //cut
                        cut = true;
                    break;
                    case SegmentUtil::PointPosition::ONLINE:
                        cut = SegmentUtil::getPointPosition(it->points[1], segs.front().s) == SegmentUtil::PointPosition::OUTSIDE;
                    break;
                }

                for (int i = 0; i < segs.size(); i+=2){
                    tmp2.emplace_back(*it);
                    tmp2.back().points[0] = *sp;
                    tmp2.back().points[1] = segs[i].ip;
                }
            }
        }
        std::swap(tmp, tmp2);
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
