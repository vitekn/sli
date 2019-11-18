#ifndef STLREADER_H
#define STLREADER_H
#include "Triangle.h"
#include <istream>
#include <vector>

struct StlReader
{
    
static std::vector<Triangle> readStlText(std::istream& is);
static std::vector<Triangle> readStlBin(std::istream& is);

};

#endif

