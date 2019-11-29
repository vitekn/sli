#ifndef TYPES_H
#define TYPES_H
//#include "thirdPart/clipper.hpp"
#include "Triangle.h"
#include "Segment.h"
#include <limits>
#include <vector>

typedef std::vector<Segment> Polygon;
//typedef ClipperLib::Path Path;
//typedef ClipperLib::Paths Paths;
//typedef ClipperLib::IntPoint Point2d;
typedef std::vector<Triangle> Mesh;

typedef std::vector<Polygon> Polygons;
typedef std::vector<Polygons> Slices;

struct Lim {
    constexpr static const int COORD_MIN = std::numeric_limits<int32_t>::min() / 2;
    constexpr static const int COORD_MAX = std::numeric_limits<int32_t>::max() / 2;
};

#endif
