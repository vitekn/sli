#include <iostream>
#include <istream>
#include <fstream>
#include <vector>

#include "MachineCommands.h"
#include "MeshUtil.h"
#include "TriangleUtil.h"
#include "SegmentUtil.h"
#include "StlReader.h"
#include "Slicer.h"
#include "thirdPart/clipper.hpp"

int main(int argc, char **argv) {
    
    std::ifstream ifs("build/in.stl");
    std::istream& is = ifs;
    auto trs = StlReader::readStlBin(is);
    MeshUtil::calcNormales(trs);
    auto slcs  = Slicer::slice(trs, 1001);
    
    int z = 0;
    for (const auto& pss : slcs) {
        MoveCommand({Point::NO_VALUE, Point::NO_VALUE, z}).print(std::cout);
        std::cout << std::endl;
        for (const auto& ps: pss) {
            for (const auto& p: ps) {
                (MoveCommand({p.X, p.Y, Point::NO_VALUE}) + ExtrudeCommand(10, 1)).print(std::cout);
                std::cout << std::endl;
            }
        }
        z+=1001;
    }
    ClipperLib::ClipperOffset co;
    co.AddPath(slcs.front().front(), ClipperLib::jtMiter, ClipperLib::etClosedPolygon);
    auto np = co.ExecuteAsPaths(-10);
    
    std::cout << "NP = " << np << std::endl;
    
    return 0;
}
