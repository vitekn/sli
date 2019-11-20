#include "Slicer.h"
#include "MeshUtil.h"
#include "Segment.h"
#include "SegmentUtil.h"
#include "TriangleUtil.h"

#include <iostream>

Slices Slicer::slice(const Mesh& m, int zStep)
{
    Slices res;
    int64_t miz;
    int64_t maz;
    std::tie(miz, maz) = MeshUtil::getZRange(m);
    int ct = (maz - miz) / zStep + 1;
    res.reserve(ct);
    for ( ; miz <= maz; miz += zStep) {
        res.emplace_back(sliceAt(m, miz));
    }
    return res;
}

Paths Slicer::sliceAt(const Mesh& m, int z)
{
    std::vector<Segment> vs;
    for (const auto& t : m) {

        auto r = TriangleUtil::intersectZ(t, z);
        if (std::get<0>(r)) {
            vs.emplace_back(std::get<1>(r));
        }
    }
    auto ss = SegmentUtil::sort(vs);

    Paths res;
    for (auto& v : ss) {
        SegmentUtil::join(v);
        res.push_back(ClipperLib::Path());
        SegmentUtil::asPath(v, [&](const Point2& p) {
            res.back().emplace_back(p.x, p.y);
        });
    }

    return res;
}

