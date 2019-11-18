#include "PointUtil.h"

int PointUtil::getPointFormatIdx() {
    static int xall = std::ios_base::xalloc();
    return xall;
}

std::istream& operator>>(std::istream& is, Point& p) {
    
    if (is.iword(PointUtil::getPointFormatIdx()) == 0) {
        is >> p.x >> p.y >> p.z;
    } else {
        ReadUtil::readLE32Num(is, p.x);
        ReadUtil::readLE32Num(is, p.y);
        ReadUtil::readLE32Num(is, p.z);
    }
    return is;
}


