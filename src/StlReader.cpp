#include "StlReader.h"
#include "Point.h"
#include "TriangleUtil.h"

std::vector<Triangle> StlReader::readStlText(std::istream& is)
{
    std::vector<Triangle> data;
    {
        std::string solid = "_____";
        for (int i = 0; i < solid.size() && is; ++i) {
            is >> solid[i];
        }
        
        if (solid != "solid" || !is) {
            return data;
        }
    }
    
    std::string name;
    is >> name;
    if (!is) {
        return data;
    }
    
    is >> PointUtil::setPointTextFormat;
    
    bool res=true;
    while (is) {
        std::string cmd;
        is >> cmd;
        if (cmd == "facet") {
            Triangle t;
            is >> t;
            if (is) {
                data.emplace_back(t);
            } else {
                res = false;
                break;
            }
        } else if (cmd == "endsolid") {
            is >> cmd;
            res = is && (cmd == name);
            break;
        }
    }

    if (!res) {
        data.clear();
    }
    
    return data;
}

std::vector<Triangle> StlReader::readStlBin(std::istream& is)
{

    std::vector<Triangle> data;
    is >> PointUtil::setPointBinFormat;
    is.ignore(80);
    if (!is) {
        return data;
    }
    uint32_t ct;
    ReadUtil::readLE32Num(is, ct);
    data.reserve(ct);
    int i = 0;
    for (; i < ct && is; ++i) {
        Triangle t;
        is >> t;
        if (!is) {
            break;
        }
        data.emplace_back(t);
    }
    
    if (data.size() != ct) {
        data.clear();
    } 
    
    return data;
}
