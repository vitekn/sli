#include <iostream>
#include <istream>
#include <fstream>
#include <vector>

#include "lib/MachineCommands.h"
#include "lib/MeshUtil.h"
#include "lib/TriangleUtil.h"
#include "lib/SegmentUtil.h"
#include "lib/StlReader.h"
#include "lib/Slicer.h"
#include "thirdPart/clipper.hpp"

int main(int argc, char **argv) {
    
    std::ifstream ifs("build/in2.stl");
    std::istream& is = ifs;
//    auto trs = StlReader::readStlBin(is);
    auto trs = StlReader::readStlText(is);
    MeshUtil::calcNormales(trs);
//    for (auto& t : trs) {
//        std::cout << t << std::endl;
//    }
    
    auto slcs  = Slicer::slice(trs, 1001);
    
    
//    ClipperLib::ClipperOffset co;
    /*
    Polygons pols;
    
    auto slice = slcs.front();
    if (slcs.size() > 1 ) {
        ClipperLib::Clipper xorer;
        auto it = slice.begin();
        xorer.AddPath(*it, ClipperLib::ptSubject, true);
        for (; it < slice.end(); ++it) {
            xorer.AddPath(*it, ClipperLib::ptClip, true);
        }
        
        auto ptree = xorer.ExecuteAsTree(ClipperLib::ctXor);
        std::vector<ClipperLib::PolyNodes*> pntr;
        pntr.push_back(&ptree.Childs);
        
        size_t indx = 0;
        
        for (; indx < pntr.size(); ++indx) {
            
            ClipperLib::PolyNodes *chlds = pntr[indx];
            if (!chlds->empty()) {
                for (auto& pn: *chlds) {
                    //p
                    pols.emplace_back();
                    pols.back().push_back(pn->Contour);
                    for (auto& hl: pn->Childs) {
                        pols.back().push_back(hl->Contour);
                        pntr.push_back(&(hl->Childs));
                    }
                }
            }
        }
    }*/
    //auto np = co.ExecuteAsPaths(-10);
    
  //  std::cout << "NP = " << np << std::endl;
    
    return 0;
}
