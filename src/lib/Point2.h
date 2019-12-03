#ifndef POINT2_H
#define POINT2_H

#include <stdint.h>
#include <ostream>
#include <tuple>
#include <cmath>

struct Point2
{
    int64_t x;
    int64_t y;

    bool operator==(const Point2& o) const;
    bool operator!=(const Point2& o) const;

    Point2& operator*=(int64_t o);
    Point2& operator/=(int64_t o);
    Point2& operator+=(const Point2& o);
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

inline
Point2& Point2::operator*=(int64_t o)
{
    x *= o;
    y *= o;
    return *this;
}

inline
Point2& Point2::operator/=(int64_t o)
{
    x /= o;
    y /= o;
    return *this;
}

inline
Point2& Point2::operator+=(const Point2& o)
{
    x += o.x;
    y += o.y;
    return *this;
}

constexpr inline 
Point2 operator-(const Point2 p1, const Point2 p2)
{
     return {p1.x - p2.x, p1.y - p2.y};
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



struct Point2Util 
{
    static std::tuple<const Point2*, const Point2*> orderByX(const Point2& p1, const Point2& p2);
    static Point2 normalize(const Point2& p);
};

inline
std::tuple<const Point2*, const Point2*> Point2Util::orderByX(const Point2& p1, const Point2& p2)
{
        if (p1.x > p2.x) {
            return std::tuple<const Point2*, const Point2*>(&p2, &p1);
        } else {
            return std::tuple<const Point2*, const Point2*>(&p1, &p2);
        }

}

inline
Point2 Point2Util::normalize(const Point2& p)
{
    int64_t m = std::sqrt(p.x * p.x + p.y * p.y);
    return {(p.x * 1000) / m, (p.y * 1000) / m};
}

inline
std::ostream& operator<<(std::ostream& os, const Point2& p)
{
    os << '(' << p.x << ", " << p.y << ')';
    return os;
}

constexpr inline 
Point2 operator+(const Point2& p1, const Point2& p2)
{
    return {p1.x + p2.x, p1.y + p2.y};
}

constexpr inline
Point2 operator/(const Point2& p, int64_t o)
{
    return {p.x / o, p.y / o};
}

constexpr inline
Point2 operator*(const Point2& p, int64_t o)
{
    return {p.x * o, p.y * o};
}


#endif


