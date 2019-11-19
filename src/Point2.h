#ifndef POINT2_H
#define POINT2_H

#include <stdint.h>
#include <ostream>

struct Point2
{
    int64_t x;
    int64_t y;

    bool operator==(const Point2& o) const;
    bool operator!=(const Point2& o) const;

    
};

inline
bool Point2::operator!=(const Point2& o) const
{
    return !(*this == o);
}

inline
bool Point2::operator==(const Point2& o) const
{
    return x == o.x && y == o.y;
}

namespace std {
    template<> struct hash<Point2>
    {
        std::size_t operator()(const Point2& p) const noexcept
        {
            int64_t m =p.x*p.y;
            return ((int)m)^((int)(m >> 32));
        }
    };
}




#endif


