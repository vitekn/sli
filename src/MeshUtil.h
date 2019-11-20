#ifndef MESHUTIL_H
#define MESHUTIL_H

#include "Types.h"

#include <stdint.h>
#include <tuple>

struct MeshUtil
{
    static void calcNormales(Mesh& m);
    static std::tuple<int64_t, int64_t> getZRange(const Mesh& m);
};

#endif


