#include "Point.h"


Point Point::operator+(const Point& o) const
{
    return {x + o.x, y + o.y, z + o.z};
}

Point Point::operator-(const Point& o) const
{
    return {x - o.x, y - o.y, z - o.z};
}

