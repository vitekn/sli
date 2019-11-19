#include "SegmentUtil.h"

#include "Point2.h"

#include <algorithm>
#include <assert.h>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

std::vector<std::vector<Segment> > SegmentUtil::sort(const std::vector<Segment>& segs)
{
    typedef std::unordered_multimap<Point2, const Segment*> SMap;
    typedef std::unordered_set<const Segment*> SSet;

    SMap map;
    for (const auto& s : segs) {
        map.insert({s.points[0], &s});
        map.insert({s.points[1], &s});
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
        const Segment* sp;
        auto it1 = itp.first;
        auto it2 = itp.first;
        ++it2;
        if (it1->second == fp) {
            sp = it2->second;
        } else {
            sp = it1->second;
        }
        
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
            res.push_back(std::vector<Segment>());
            cs = &res.back();
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


void SegmentUtil::join(std::vector<Segment>& segs)
{
    auto it = segs.begin();
    auto nit = it;
    ++nit;

    while (nit != segs.end()) {
        while (join2(*it,*nit)) {
            ++nit;
        }
        if (nit == segs.end()) {
            break;
        }
        ++it;
        *it = *nit;
        ++nit;
    }
    size_t d = it - segs.begin() + 1;
    segs.resize(d);
}

