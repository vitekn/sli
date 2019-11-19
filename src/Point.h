#ifndef POINT_H
#define POINT_H
#include <stdint.h>

struct Point{
     
    int64_t x;
    int64_t y;
    int64_t z;
    
    Point operator-(const Point& o) const;
    Point operator+(const Point& o) const;

    bool operator==(const Point& o) const;
    bool operator!=(const Point& o) const;
    
};

inline
bool Point::operator!=(const Point& o) const
{
    return !(*this == o);
}

inline
bool Point::operator==(const Point& o) const
{
    return x == o.x && y == o.y && z == o.z;
}


#endif

