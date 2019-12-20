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

    constexpr static const Segment py0uH     {{{         -1000,              0}, {          1000,              0}}, {   0, 1000}, infp,  1};
    constexpr static const Segment py0maxH   {{{Lim::COORD_MIN,              0}, {Lim::COORD_MAX,              0}}, {   0, 1000}, infp,  1};
    constexpr static const Segment ny0uH     {{{         -1000,              0}, {          1000,              0}}, {   0,-1000}, infm,  1};
    constexpr static const Segment ny0maxH   {{{Lim::COORD_MIN,              0}, {Lim::COORD_MAX,              0}}, {   0,-1000}, infm,  1};

    constexpr static const Segment px0uV     {{{             0,          -1000}, {             0,           1000}}, {1000,    0},    0,  1};
    constexpr static const Segment px0maxV   {{{             0, Lim::COORD_MIN}, {             0, Lim::COORD_MAX}}, {1000,    0},    0,  1};
    constexpr static const Segment nx0uV     {{{             0,          -1000}, {             0,           1000}}, {-1000,   0},    0, -1};
    constexpr static const Segment nx0maxV   {{{             0, Lim::COORD_MIN}, {             0, Lim::COORD_MAX}}, {-1000,   0},    0, -1};
    
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
                                                    SegmentUtil::PointPosition::ONLINE},
                             GetPointPositionParam {Point2{-1000, 1000},
                                                    TestSegs::px0uV,
                                                    SegmentUtil::PointPosition::INSIDE},
                             GetPointPositionParam {Point2{ 1000, 1000},
                                                    TestSegs::px0uV,
                                                    SegmentUtil::PointPosition::OUTSIDE},
                             GetPointPositionParam {Point2{-1000, 1000},
                                                    TestSegs::nx0uV,
                                                    SegmentUtil::PointPosition::OUTSIDE},            
                             GetPointPositionParam {Point2{ 1000, 1000},
                                                    TestSegs::nx0uV,
                                                    SegmentUtil::PointPosition::INSIDE},
                             GetPointPositionParam {Point2{ 0, 1000},
                                                    TestSegs::px0uV,
                                                    SegmentUtil::PointPosition::ONLINE},
                             GetPointPositionParam {Point2{ 0, 1000},
                                                    TestSegs::nx0uV,
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
                         testing::Values(MidOffsetParam{ TestSegs::n45u * 2,
                                                         move(reverse(rotate90CCW(TestSegs::p45u))*2,{4000, 0}),
                                                         707,
                                                         Point2{2000, 1000}},   /* o /\ o */ // 45, 60-30, 30-60
                                         MidOffsetParam{ move(reverse(rotate90CCW(TestSegs::n45u))*2,{-4000, 0}),
                                                         TestSegs::p45u * 2,
                                                         707,
                                                         Point2{-2000, -1000}}, /* o \/ o */ // 45, 60-30, 30-60
                                         MidOffsetParam{ TestSegs::p45u * 2,
                                                         move(reverse(rotate90CCW(TestSegs::n45u))*2,{4000, 0}),
                                                         707,
                                                         Point2{2000, 3000}},  /* i /\ i */ // 45, 60-30, 30-60
                                         MidOffsetParam{ move(reverse(rotate90CCW(TestSegs::p45u))*2,{-4000, 0}),
                                                         TestSegs::n45u * 2,
                                                         707,
                                                         Point2{-2000, -3000}}, /* i \/ i */ // 45, 60-30, 30-60
                                         MidOffsetParam{ TestSegs::p45u * 2,
                                                         move(rotate90CCW(TestSegs::p45u)*2,{0, 4000}),
                                                         707,
                                                         Point2{1000, 2000}},  /* i > o */ // 45, 30-60, 60-30
                                         MidOffsetParam{ TestSegs::n45u * 2,
                                                         move(rotate90CCW(TestSegs::n45u)*2,{0, 4000}),
                                                         707,
                                                         Point2{3000, 2000}},   /* o > i */ // 45, 30-60, 60-30
                                         MidOffsetParam{ reverse(TestSegs::p45u * 2),
                                                         move(reverse(rotate90CCW(TestSegs::p45u))*2,{0, -4000}),
                                                         707,
                                                         Point2{-3000, -2000}}, /* i < o */ // 45, 30-60, 60-30
                                         MidOffsetParam{ reverse(TestSegs::n45u * 2),
                                                         move(reverse(rotate90CCW(TestSegs::n45u))*2,{0, -4000}),
                                                         707,
                                                         Point2{-1000, -2000}},  /* o < i */ // 45, 30-60, 60-30
                                         MidOffsetParam{ reverse(move(TestSegs::nx0uV,{0, 2000})),
                                                         move(TestSegs::ny0uH,{1000, 1000}),
                                                         1000,
                                                         Point2 {1000, 2000}},   /* o L i */
                                         MidOffsetParam{ reverse(move(TestSegs::px0uV, {-1000, 0})),
                                                         move(TestSegs::py0uH, {0, -1000}),
                                                         1000,
                                                         Point2 {-2000, -2000}},    /* i L o */
                                         MidOffsetParam{ move(TestSegs::py0uH, { 1000, -1000}),
                                                         move(TestSegs::nx0uV, { 2000,  0}),
                                                         1000,
                                                         Point2 {3000, -2000}},     /* o _| i */
                                         MidOffsetParam{ move(TestSegs::ny0uH, { 1000, 1000}),
                                                         move(TestSegs::px0uV, { 2000, 2000}),
                                                         1000,
                                                         Point2 {1000, 2000}},     /* i _| o */
                                         MidOffsetParam{ move(TestSegs::nx0uV, { 1000, 1000}),
                                                         move(TestSegs::py0uH, { 2000, 2000}),
                                                         1000,
                                                         Point2 {2000, 1000}},      /* o |- i */
                                         MidOffsetParam{ move(TestSegs::px0uV, { 2000, 1000}),
                                                         move(TestSegs::ny0uH, { 3000, 2000}),
                                                         1000,
                                                         Point2 {1000, 3000}},       /* i |- o */
                                         MidOffsetParam{ move(TestSegs::py0uH, { 1000, 2000}),
                                                         reverse(move(TestSegs::px0uV, { 2000, 1000})),
                                                         1000,
                                                         Point2 {1000, 1000}},       /* i -| o */
                                         MidOffsetParam{ move(TestSegs::ny0uH, { 1000, 2000}),
                                                         reverse(move(TestSegs::nx0uV, { 2000, 1000})),
                                                         1000,
                                                         Point2 {3000, 3000}}       /* o -| i */
                             
                        ));


struct HaveIntersectParam
{
    Segment s1;
    Segment s2;
    Point2  p_exp;
    bool    result;
};

std::ostream& operator<<(std::ostream& os, const HaveIntersectParam& p)
{
    os << "s1 = " << p.s1 << " s2 = " << p.s2 << " exp p = " << p.p_exp << " exp res = " << p.result;
    return os;
}


class HaveIntersectionTest : public testing::TestWithParam<HaveIntersectParam>
{
    
};

TEST_P(HaveIntersectionTest, haveIntersectionTest)
{
    const HaveIntersectParam& p = GetParam();
    
    bool result;
    Point2 pt;
  //  std::cout << p << std::endl;
    std::tie(result, pt) = SegmentUtil::haveIntersection(p.s1, p.s2);
    EXPECT_EQ(p.result, result);
    
    if (result) {
        EXPECT_EQ (p.p_exp, pt);
    }
}


INSTANTIATE_TEST_SUITE_P(haveIntersection,
                         HaveIntersectionTest,
                         testing::Values(HaveIntersectParam{TestSegs::p45u, rotate90CCW(TestSegs::p45u), {0, 0}, true},
                                         HaveIntersectParam{move(TestSegs::p45u,{1000, 1000}), move(rotate90CCW(TestSegs::p45u),{1000,1000}), {1000, 1000}, true},
                                         HaveIntersectParam{move(TestSegs::p60u,{1000, 1000}), move(rotate90CCW(TestSegs::p30u),{1000,1000}), {1000, 1000}, true},
                                         HaveIntersectParam{move(TestSegs::p45u,{1000, 1000}), move(rotate90CCW(TestSegs::p45u),{4000,4000}), {1000, 1000}, false},
                                         HaveIntersectParam{move(TestSegs::px0uV,{1000, 1000}), move(TestSegs::py0uH, {1000,1000}), {1000, 1000}, true},
                                         HaveIntersectParam{TestSegs::p45u, TestSegs::p45u, {1000, 1000}, false},
                                         HaveIntersectParam{TestSegs::p45u, move(rotate90CCW(TestSegs::p45u),{2000, 0}), {1000, 1000}, true},
                                         HaveIntersectParam{TestSegs::p45u, move(rotate90CCW(TestSegs::p45u),{1000, 1000}), {1000, 1000}, true}
                             
                        ));


struct GetAngleParam
{
    Segment s1;
    Segment s2;
    int64_t angle;
};

std::ostream& operator<<(std::ostream& os, const GetAngleParam& p)
{
    os << "s1 = " << p.s1 << " s2 = " << p.s2 << " exp a = " << p.angle;
    return os;
}


class GetAngleTest : public testing::TestWithParam<GetAngleParam>
{
    
};

TEST_P(GetAngleTest, getAngleTest)
{
    const GetAngleParam& p = GetParam();
//    std::cout << p << std::endl;
    int64_t a = SegmentUtil::getAngle(p.s1, p.s2);
  
    EXPECT_EQ(p.angle, a);
}

INSTANTIATE_TEST_SUITE_P(getAngle,
                         GetAngleTest,
                         testing::Values(GetAngleParam{TestSegs::p45u, reverse(move(rotate90CCW(TestSegs::p45u), {2000, 0})), std::numeric_limits<int64_t>::min()/2},
                                         GetAngleParam{TestSegs::n45u, reverse(move(rotate90CCW(TestSegs::p45u), {2000, 0})), std::numeric_limits<int64_t>::max()/2 + 1},
                                         GetAngleParam{TestSegs::p45u, move(TestSegs::p30u, {1866, 1500}), -157124229638861824},
                                         GetAngleParam{TestSegs::p45u, move(TestSegs::p60u, {1500, 1866}),  157124229638861824},
                                         GetAngleParam{TestSegs::n45u, move(TestSegs::p30u, {1866, 1500}),  157124229638861824},
                                         GetAngleParam{TestSegs::n45u, move(TestSegs::p60u, {1500, 1866}), -157124229638861824},
                                         GetAngleParam{move(TestSegs::px0uV, {1000,0}), move(TestSegs::p60u, {1500, 1866}), -617878061727699968},
                                         GetAngleParam{move(TestSegs::nx0uV, {1000,0}), move(TestSegs::p60u, {1500, 1866}),  617878061727699968},
                                         GetAngleParam{move(TestSegs::px0uV, {1000,0}), move(TestSegs::py0uH,{2000, 1000}),  std::numeric_limits<int64_t>::min()/2},
                                         GetAngleParam{move(TestSegs::nx0uV, {1000,0}), move(TestSegs::py0uH,{2000, 1000}),  std::numeric_limits<int64_t>::max()/2 + 1}

                                  ));

struct ValidCornerParam
{
    Segment s1;
    Segment s2;
    bool    result;
};

std::ostream& operator<<(std::ostream& os, const ValidCornerParam& p)
{
    os << "s1 = " << p.s1 << " s2 = " << p.s2 << " exp res = " << p.result;
    return os;
}


class ValidCornerTest : public testing::TestWithParam<ValidCornerParam>
{
    
};

TEST_P(ValidCornerTest, validCornerTest)
{
    const ValidCornerParam& p = GetParam();
//    std::cout << p << std::endl;
    int64_t a = SegmentUtil::getAngle(p.s1, p.s2);
    bool result = SegmentUtil::validCorner(p.s1, p.s2, a);
  
    EXPECT_EQ(p.result, result);
}

INSTANTIATE_TEST_SUITE_P(validCorner,
                         ValidCornerTest,
                         testing::Values(ValidCornerParam{ TestSegs::n45u * 2, move(reverse(rotate90CCW(TestSegs::p45u))*2,{4000, 0}), true },
                                         ValidCornerParam{ TestSegs::p45u * 2, move(reverse(rotate90CCW(TestSegs::n45u))*2,{4000, 0}), true },
                                         ValidCornerParam{ TestSegs::p45u * 2, move(reverse(rotate90CCW(TestSegs::p45u))*2,{4000, 0}), false },
                                         ValidCornerParam{ TestSegs::p45u * 2, move(rotate90CCW(TestSegs::p45u)*2,{0, 4000}), true },
                                         ValidCornerParam{ TestSegs::n45u * 2, move(rotate90CCW(TestSegs::n45u)*2,{0, 4000}), true },
                                         ValidCornerParam{ TestSegs::p45u * 2, move(rotate90CCW(TestSegs::n45u)*2,{0, 4000}), false },
                                         ValidCornerParam{ TestSegs::n45u * 2, move(rotate90CCW(TestSegs::p45u)*2,{0, 4000}), false },
                                         ValidCornerParam{ reverse(move(TestSegs::nx0uV,{0, 2000})), move(TestSegs::ny0uH,{1000, 1000}), true },
                                         ValidCornerParam{ reverse(move(TestSegs::px0uV,{0, 2000})), move(TestSegs::py0uH,{1000, 1000}), true },
                                         ValidCornerParam{ reverse(move(TestSegs::nx0uV,{0, 2000})), move(TestSegs::py0uH,{1000, 1000}), false },
                                         ValidCornerParam{ reverse(move(TestSegs::px0uV,{0, 2000})), move(TestSegs::ny0uH,{1000, 1000}), false }
                                  ));


} // namespace
