#ifndef POINTUTIL_H
#define POINTUTIL_H

#include "Point.h"
#include "ReadUtil.h"

#include <istream>

struct PointUtil
{
    
    static int getPointFormatIdx();

    static std::istream& setPointFormat(std::istream& is, int format);

    static std::istream& setPointTextFormat(std::istream& is);

    static std::istream& setPointBinFormat(std::istream& is);


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

std::istream& operator>>(std::istream& is, Point& p);

#endif


