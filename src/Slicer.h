#ifndef SLICER_H
#define SLICER_H
#include "Types.h"
#include <vector>

struct Slicer 
{
    static Slices slice(const Mesh& m, int zStep);
    static Paths  sliceAt(const Mesh& m, int z);
};

#endif

