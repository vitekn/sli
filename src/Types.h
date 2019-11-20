#ifndef TYPES_H
#define TYPES_H
#include "thirdPart/clipper.hpp"
#include "Triangle.h"
#include <vector>

typedef ClipperLib::Path Path;
typedef ClipperLib::Paths Paths;
typedef std::vector<Paths> Slices;
typedef ClipperLib::IntPoint Point2d;
typedef std::vector<Triangle> Mesh;

#endif
