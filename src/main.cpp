#include <iostream>
#include <istream>
#include <fstream>
#include <vector>

#include "StlReader.h"


int main(int argc, char **argv) {
    
    std::ifstream ifs("build/in.stl");
    std::istream& is = ifs;
    auto trs = StlReader::readStlBin(is);
    for(auto& t: trs) {
        std::cout << "#N [ " << t.normal.x << ", " << t.normal.y << ", " << t.normal.z << " ]" << std::endl;
        for (int i = 0; i < 3; ++i) {
            std::cout << "#" << i << " [ " << t.points[i].x << ", " << t.points[i].y << ", " << t.points[i].z << " ]" << std::endl;
        }
        std::cout << std::endl;
    }
    
    return 0;
}
