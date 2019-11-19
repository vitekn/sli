#include <iostream>
#include <istream>
#include <fstream>
#include <vector>
#include "TriangleUtil.h"
#include "SegmentUtil.h"
#include "StlReader.h"


int main(int argc, char **argv) {
    
    std::ifstream ifs("build/in.stl");
    std::istream& is = ifs;
    auto trs = StlReader::readStlBin(is);
    std::vector<Segment> vs;
    for(auto& t: trs) {
        t.normal = TriangleUtil::calcNormale(t);
        std::cout << "#N [ " << t.normal.x << ", " << t.normal.y << ", " << t.normal.z << " ]" << std::endl;
        for (int i = 0; i < 3; ++i) {
            std::cout << "#" << i << " [ " << t.points[i].x << ", " << t.points[i].y << ", " << t.points[i].z << " ]" << std::endl;
        }
        bool r;
        Segment s;
        std::tie(r,s) = TriangleUtil::intersectZ(t,10);
        if (r) {
            std::cout << "IR = " << s << std::endl;
            vs.emplace_back(s);
        }
        std::cout << std::endl;
    }
    
    auto ss = SegmentUtil::sort(vs);
    
    for (auto& v : ss) {
        SegmentUtil::join(v);
        for (auto& s : v) {
            std::cout << s << std::endl;
        }
    }
    
    return 0;
}
