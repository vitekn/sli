#ifndef PERIMETERPROC_H
#define PERIMETERPROC_H
#include "Types.h"
#include "MachineCommands.h"
#include <iostream>
//#include "thirdPart/clipper.hpp"

class PerimeterProc
{
public:
    PerimeterProc(size_t pCount, int64_t pWidth): _pCount(pCount), _pWidth(pWidth){}
    
    void process (Polygons& polygons)
    {
        Polygons peeled;
        for (int i = 0; i < _pCount; ++i) {
            peeled = peel(_pWidth/2+_pWidth*i);
            renderPerimeter(peeled);
        }

    }
    
    void renderPerimeter(Polygons& polygons)
    {
        for (const auto& polygon : polygons) {
            for (const auto& path: polygon) {
                for (const auto& point: path) {
                    (MoveCommand({point.X, point.Y, Point::NO_VALUE}) + ExtrudeCommand(10, 1)).print(std::cout);
                    std::cout << std::endl;
                }
                (MoveCommand({path.front().X, path.front().Y, Point::NO_VALUE}) + ExtrudeCommand(10, 1)).print(std::cout);
                std::cout << std::endl;
            }
        }
    }
    
    Polygons peel (const Polygons& polygons)
    {
        Polygons resp;
        resp.reserve(polygons.size());
        ClipperLib::ClipperOffset offs;
        for (const auto& polygon : polygons) {

            auto pit = polygon.begin();
            offs.AddPath(*pit, ClipperLib::JoinType::jtMiter, ClipperLib::etClosedPolygon);
            Paths peelRes = offs.ExecuteAsPaths(-_pWidth);
            
            if (peelRes.empty()) {
                continue;
            }
/*            if (peelRes.size() == 1) {
                resp.emplace_back();
                resp.back().emplace_back(std::move(peelRes.front()));
            } else {
                // split into N
            }*/

            ++pit;
            Paths holes;
            holes.resize(polygon.size());
            
            for (; pit != polygon.end(); ++pit) {
                offs.Clear();
                offs.AddPath(*pit, ClipperLib::jtMiter, ClipperLib::etClosedPolygon);
                offs.ExecuteAddTo(holes, _pWidth);
            }
            
            ClipperLib::Clipper clpr;
            for (auto& hole : holes) {
                clpr.AddPath()
            }
            
        }
    }
    
private:
    size_t  _pCount;
    int64_t _pWidth;
};

#endif

