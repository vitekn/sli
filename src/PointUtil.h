#ifndef POINTUTIL_H
#define POINTUTIL_H

#include "Point.h"
#include "ReadUtil.h"

#include <istream>
#include <ostream>
#include <tuple>

struct PointUtil
{
    
    static int getPointFormatIdx();

    static std::istream& setPointFormat(std::istream& is, int format);

    static std::istream& setPointTextFormat(std::istream& is);

    static std::istream& setPointBinFormat(std::istream& is);
    
    static std::tuple<const Point*, const Point*> orderByZ(const Point& p1, const Point& p2);

};

inline
std::istream& PointUtil::setPointFormat(std::istream& is, int format)
{
    is.iword(getPointFormatIdx()) = format;
    return is;
};

inline
std::istream& PointUtil::setPointTextFormat(std::istream& is)
{
    return setPointFormat(is, 0);
};

inline
std::istream& PointUtil::setPointBinFormat(std::istream& is)
{
    return setPointFormat(is, 1);
};
inline
std::tuple<const Point*, const Point*> PointUtil::orderByZ(const Point& p1, const Point& p2)
{
        if (p1.z > p2.z) {
            return std::tuple<const Point*, const Point*>(&p2, &p1);
        } else {
            return std::tuple<const Point*, const Point*>(&p1, &p2);
        }

}


std::istream& operator>>(std::istream& is, Point& p);

std::ostream& operator<<(std::ostream& os, const Point& p);



#endif


