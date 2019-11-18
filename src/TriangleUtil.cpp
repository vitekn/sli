#include "TriangleUtil.h"

std::istream& operator>>(std::istream& is, Triangle& p){
    if (is.iword(PointUtil::getPointFormatIdx()) == 0) {
        std::string tmp;
        tmp.reserve(10);
        is >> tmp;
        if (tmp != "normal") {
            is.fail();
            return is;
        }
        is >> p.normal;
        is >> tmp;
        if (tmp != "outer") {
            is.fail();
            return is;
        }
        is >> tmp;
        if (tmp != "loop") {
            is.fail();
            return is;
        }
        for (int i = 0; i < 3; ++i) {
            is >> tmp;
            if (tmp != "vertex") {
                is.fail();
                return is;
            }
            is >> p.points[i];
        }
        is >> tmp;
        if (tmp != "endloop") {
            is.fail();
            return is;
        }
        is >> tmp;
        if (tmp != "endfacet") {
            is.fail();
            return is;
        }
    }
    else {
        is >> p.normal >> p.points[0] >> p.points[1] >> p.points[2];
        is.ignore(2);
    }
    
    return is;
}

