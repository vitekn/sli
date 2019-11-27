#ifndef TYPES_H
#define TYPES_H
//#include "thirdPart/clipper.hpp"
#include "Triangle.h"
#include "Segment.h"
#include <vector>

typedef std::vector<Segment> Polygon;
//typedef ClipperLib::Path Path;
//typedef ClipperLib::Paths Paths;
//typedef ClipperLib::IntPoint Point2d;
typedef std::vector<Triangle> Mesh;

typedef std::vector<Polygon> Polygons;
typedef std::vector<Polygons> Slices;

#endif
