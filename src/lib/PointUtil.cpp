#include "PointUtil.h"
#include <cmath>

int PointUtil::getPointFormatIdx() {
    static int xall = std::ios_base::xalloc();
    return xall;
}

std::istream& operator>>(std::istream& is, Point& p)
{
    
    float x;
    float y;
    float z;
    if (is.iword(PointUtil::getPointFormatIdx()) == 0) {
        is >> x >> y >> z;
    } else {
        ReadUtil::readLE32Num(is, x);
        ReadUtil::readLE32Num(is, y);
        ReadUtil::readLE32Num(is, z);
    }
    p = {(int64_t)std::round(x*1000), (int64_t)std::round(y*1000), (int64_t)std::round(z*1000)};
    return is;
}


std::ostream& operator<<(std::ostream& os, const Point& p)
{
    os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
    return os;
}
