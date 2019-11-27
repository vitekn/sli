#include "MeshUtil.h"
#include <limits>
#include "TriangleUtil.h"

void MeshUtil::calcNormales(Mesh& m)
{
    for (auto& t : m) {
        t.normal = TriangleUtil::calcNormale(t);
    }
    
}


std::tuple<int64_t, int64_t> MeshUtil::getZRange(const Mesh& m)
{
    int64_t mi = std::numeric_limits<int64_t>::max();
    int64_t ma = std::numeric_limits<int64_t>::min();
    
    for (const auto& t : m) {
        for (int i = 0; i < 3; ++i) {
            if (mi > t.points[i].z) {
                mi = t.points[i].z;
            }
            if (ma < t.points[i].z) {
                ma = t.points[i].z;
            }
        }
    }
    
    return std::tie(mi, ma);
}

