#include "../lib/SegmentUtil.h"
#include "../lib/Point2.h"
#include "../lib/Types.h"
#include "gtest/gtest.h"
#include <limits>
#include <iostream>

namespace {

TEST (SegmentUtil, getYOnLine) {
    Segment s;
    s.k = 1;
    s.sign = 1;
    s.normale = {707, 707};
    s.points[0] = {1000, 2000};
    s.points[1] = {2000, 1000};

    int64_t y;
    y = SegmentUtil::getYOnLine(1500, s);
    EXPECT_EQ(1500, y);

    y = SegmentUtil::getYOnLine(10000, s);
    EXPECT_EQ(-7000, y);

    s.points[1] = {1000, 2000};
    s.points[0] = {2000, 1000};

    y = SegmentUtil::getYOnLine(1500, s);
    EXPECT_EQ(1500, y);

    y = SegmentUtil::getYOnLine(10000, s);
    EXPECT_EQ(-7000, y);

    s.points[0] = {1000, 1000};
    s.points[1] = {2000, 2000};

    y = SegmentUtil::getYOnLine(1500, s);
    EXPECT_EQ(1500, y);

    y = SegmentUtil::getYOnLine(10000, s);
    EXPECT_EQ(10000, y);

    s.points[1] = {1000, 1000};
    s.points[0] = {2000, 2000};

    y = SegmentUtil::getYOnLine(1500, s);

    EXPECT_EQ(1500, y);
    
    y = SegmentUtil::getYOnLine(10000, s);
    
    EXPECT_EQ(10000, y);    
}

struct GetPointPositionParam {
    Point2  p;
    Segment s;
    int     result;
};

std::ostream& operator<<(std::ostream& s, const GetPointPositionParam& p)
{
    s << "P = " << p.p << " S = " << p.s << " R = " << p.result;
    return s;
}

class GetPointPositionTest : public testing::TestWithParam<GetPointPositionParam>
{
    
};

TEST_P(GetPointPositionTest, getPointPositionTest)
{
    const GetPointPositionParam& p = GetParam();
    int rc = SegmentUtil::getPointPosition(p.p, p.s);
    EXPECT_EQ(p.result, rc);
}

struct TestSegs {
    constexpr static const double PI  = 3.141592653589793238463;
    constexpr static const double  infp =  std::numeric_limits<double>::infinity();
    constexpr static const double  infm = -std::numeric_limits<double>::infinity();
    
    constexpr static const int64_t miny30 = (int64_t)(0.57735026919 * (double)Lim::COORD_MIN);
    constexpr static const int64_t maxy30 = (int64_t)(0.57735026919 * (double)Lim::COORD_MAX);
    constexpr static const int64_t minx60 = miny30;
    constexpr static const int64_t maxx60 = maxy30;
//    constexpr static const int64_t miny30 = (int64_t)(0.57735026919 * (double)Lim::COORD_MIN);
    
    constexpr static const Segment p45u     {{{         -1000,          -1000}, {          1000,           1000}}, { 707, -707},   -1,  1};
    constexpr static const Segment n45u     {{{         -1000,          -1000}, {          1000,           1000}}, {-707,  707},   -1, -1};
    constexpr static const Segment p45max   {{{Lim::COORD_MIN, Lim::COORD_MIN}, {Lim::COORD_MAX, Lim::COORD_MAX}}, { 707, -707},   -1,  1};
    constexpr static const Segment n45max   {{{Lim::COORD_MIN, Lim::COORD_MIN}, {Lim::COORD_MAX, Lim::COORD_MAX}}, {-707,  707},   -1, -1};

    constexpr static const Segment y0u      {{{         -1000,              0}, {          1000,              0}}, {   0, 1000},  infp,  1};
    constexpr static const Segment x0u      {{{             0,          -1000}, {             0,           1000}}, {1000,    0},     0,  1};
    constexpr static const Segment y0max    {{{Lim::COORD_MIN,              0}, {Lim::COORD_MAX,              0}}, {   0, 1000},  infp,  1};
    constexpr static const Segment x0max    {{{             0, Lim::COORD_MIN}, {             0, Lim::COORD_MAX}}, {1000,    0},     0,  1};
    
    constexpr static const Segment p30u     {{{          -866,           -500}, {           866,            500}}, { 500, -866}, -1.73205080757,  1};
    constexpr static const Segment n30u     {{{          -866,           -500}, {           866,            500}}, {-500,  866}, -1.73205080757, -1};
    
    constexpr static const Segment p30max   {{{Lim::COORD_MIN,         miny30}, {Lim::COORD_MAX,         maxy30}}, { 500, -866}, -1.73205080757,  1};
    constexpr static const Segment n30max   {{{Lim::COORD_MIN,         miny30}, {Lim::COORD_MAX,         maxy30}}, {-500,  866}, -1.73205080757, -1};
    constexpr static const Segment p60u     {{{          -500,           -866}, {           500,            866}}, { 866, -500}, -0.57735026919,  1};
    constexpr static const Segment n60u     {{{          -500,           -866}, {           500,            866}}, { 866, -500}, -0.57735026919, -1};
    constexpr static const Segment p60umax  {{{        minx60, Lim::COORD_MIN}, {        maxx60, Lim::COORD_MAX}}, { 866, -500}, -0.57735026919,  1};
    constexpr static const Segment n60umax  {{{        minx60, Lim::COORD_MIN}, {        maxx60, Lim::COORD_MAX}}, { 866, -500}, -0.57735026919, -1};
};

Segment invNormale(const Segment& s)
{//todo
    return s;
}
constexpr Segment move(const Segment& s, const Point2& offset)
{
    return Segment{{s.points[0] + offset, s.points[1] + offset}, s.normale, s.k, s.sign};
}

constexpr Point2 rotate90CCW(const Point2& p)
{
    return {-p.y, p.x};
}

constexpr int getSign(int64_t v)
{
    return (((v >> 62) & 2) ^ 2) - 1;
}

constexpr Segment rotate90CCW(const Segment& s){
    Point2 ro{((s.points[0] + s.points[1])/2)};
    Segment ns {move(s, Point2{0, 0} - ro)};
    Point2 rn {rotate90CCW(ns.normale)};
    const int si = getSign(rn.x);
    Segment ns1 {{rotate90CCW(ns.points[0]), rotate90CCW(ns.points[1])}, rn, std::abs(ns.k) * getSign(rn.y) * si, si};
    return move(ns1, ro);
}

constexpr Segment reverse(const Segment& s)
{
    return {{s.points[1], s.points[0]}, s.normale, s.k, s.sign};
}


INSTANTIATE_TEST_SUITE_P(getPointPosition,
                         GetPointPositionTest,
                         testing::Values(
                             GetPointPositionParam {Point2{-1000,  1000}, TestSegs::n45u, SegmentUtil::PointPosition::OUTSIDE},
                             GetPointPositionParam {Point2{ 1000, -1000}, TestSegs::n45u, SegmentUtil::PointPosition::INSIDE},
                             GetPointPositionParam {Point2{    0,     0}, TestSegs::n45u, SegmentUtil::PointPosition::ONLINE},
                             GetPointPositionParam {Point2{-1000, -1000}, TestSegs::n45u, SegmentUtil::PointPosition::ONLINE},
                             GetPointPositionParam {Point2{ 1000,  1000}, TestSegs::n45u, SegmentUtil::PointPosition::ONLINE},

                             GetPointPositionParam {Point2{ Lim::COORD_MIN, Lim::COORD_MAX},
                                                    TestSegs::n45max,
                                                    SegmentUtil::PointPosition::OUTSIDE},
                             GetPointPositionParam {Point2{ Lim::COORD_MAX, Lim::COORD_MIN},
                                                    TestSegs::n45max,
                                                    SegmentUtil::PointPosition::INSIDE},
                             GetPointPositionParam {Point2{    0,     0},
                                                    TestSegs::n45max,
                                                    SegmentUtil::PointPosition::ONLINE},
                             GetPointPositionParam {Point2{Lim::COORD_MIN, Lim::COORD_MIN},
                                                    TestSegs::n45max,
                                                    SegmentUtil::PointPosition::ONLINE},
                             GetPointPositionParam {Point2{ Lim::COORD_MAX, Lim::COORD_MAX},
                                                    TestSegs::n45max,
                                                    SegmentUtil::PointPosition::ONLINE}
                                                                                       ));


struct MidOffsetParam
{
    Segment s1;
    Segment s2;
    int64_t offset;
    Point2 p_exp;
};

std::ostream& operator<<(std::ostream& os, const MidOffsetParam& p)
{
    os << "s1 = " << p.s1 << " s2 = " << p.s2 << " offs = " << p.offset << " exp p = " << p.p_exp;
    return os;
}

class MidOffsetTest : public testing::TestWithParam<MidOffsetParam>
{
    
};

void areSegmentsEqual(const Segment& s1, const Segment& s2)
{
    EXPECT_EQ(s1.k, s2.k);
    EXPECT_EQ(s1.normale.x, s2.normale.x);
    EXPECT_EQ(s1.normale.y, s2.normale.y);
    EXPECT_EQ(s1.points[0].x, s2.points[0].x);
    EXPECT_EQ(s1.points[0].y, s2.points[0].y);
    EXPECT_EQ(s1.points[1].x, s2.points[1].x);
    EXPECT_EQ(s1.points[1].y, s2.points[1].y);
}

TEST_P(MidOffsetTest, midOffsetTest)
{
    const MidOffsetParam& p = GetParam();
    Segment s1 = p.s1;
    Segment s2 = p.s2;
    std::cout << "S1 = " << s1 << " S2 = " << s2 << std::endl;
    SegmentUtil::midOffset(s1, s2, p.offset);
    
    EXPECT_EQ(p.p_exp, s1.points[1]);
    EXPECT_EQ(p.p_exp, s2.points[0]);
}

constexpr Segment operator*(const Segment& s, int64_t m)
{
  return {{s.points[0] * m, s.points[1] * m}, s.normale, s.k, s.sign};   
}

INSTANTIATE_TEST_SUITE_P(midOffset,
                         MidOffsetTest,
                         testing::Values(MidOffsetParam{ TestSegs::p45u * 2,
                                                         move(reverse(rotate90CCW(TestSegs::n45u))*2,{4000, 0}),/*  2,*/
                                                         707,
                                                         Point2{2000,1000}},
                                         MidOffsetParam{ move(reverse(rotate90CCW(TestSegs::n45u))*2,{-4000, 0}),/*  2,*/
                                                         TestSegs::p45u * 2,
                                                         707,
                                                         Point2{-2000,-3000}}
                                        
                             
                        ));


} // namespace
