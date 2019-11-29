#include "../lib/SegmentUtil.h"
#include "../lib/Point2.h"
#include "../lib/Types.h"
#include "gtest/gtest.h"
#include <limits>

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
    Segment p45u;
    Segment n45u;
    Segment p45umax;
    Segment n45umax;
    Segment y0u;
    Segment x0u;
    Segment y0umax;
    Segment x0umax;
    Segment p30u;
    Segment n30u;
    Segment p30umax;
    Segment n30umax;
    Segment p60u;
    Segment n60u;
    Segment p60umax;
    Segment n60umax;
};

Segment invNormale(const Segment& s)
{//todo
    return s;
}


INSTANTIATE_TEST_SUITE_P(getPointPosition,
                         GetPointPositionTest,
                         testing::Values(
                             GetPointPositionParam {Point2{-1000,  1000}, Segment{{{-1000, -1000}, {1000, 1000}},{-707, 707}, -1, -1}, SegmentUtil::PointPosition::OUTSIDE},
                             GetPointPositionParam {Point2{ 1000, -1000}, Segment{{{-1000, -1000}, {1000, 1000}},{-707, 707}, -1, -1}, SegmentUtil::PointPosition::INSIDE},
                             GetPointPositionParam {Point2{    0,     0}, Segment{{{-1000, -1000}, {1000, 1000}},{-707, 707}, -1, -1}, SegmentUtil::PointPosition::ONLINE},
                             GetPointPositionParam {Point2{-1000, -1000}, Segment{{{-1000, -1000}, {1000, 1000}},{-707, 707}, -1, -1}, SegmentUtil::PointPosition::ONLINE},
                             GetPointPositionParam {Point2{ 1000,  1000}, Segment{{{-1000, -1000}, {1000, 1000}},{-707, 707}, -1, -1}, SegmentUtil::PointPosition::ONLINE},

                             GetPointPositionParam {Point2{ Lim::COORD_MIN, Lim::COORD_MAX},
                                                    Segment{{{Lim::COORD_MIN, Lim::COORD_MIN}, {Lim::COORD_MAX, Lim::COORD_MAX}},{-707, 707}, -1, -1},
                                                    SegmentUtil::PointPosition::OUTSIDE},
                             GetPointPositionParam {Point2{ Lim::COORD_MAX, Lim::COORD_MIN},
                                                    Segment{{{Lim::COORD_MIN, Lim::COORD_MIN}, {Lim::COORD_MAX, Lim::COORD_MAX}},{-707, 707}, -1, -1},
                                                    SegmentUtil::PointPosition::INSIDE},
                             GetPointPositionParam {Point2{    0,     0},
                                                    Segment{{{Lim::COORD_MIN, Lim::COORD_MIN}, {Lim::COORD_MAX, Lim::COORD_MAX}},{-707, 707}, -1, -1},
                                                    SegmentUtil::PointPosition::ONLINE},
                             GetPointPositionParam {Point2{Lim::COORD_MIN, Lim::COORD_MIN},
                                                    Segment{{{Lim::COORD_MIN, Lim::COORD_MIN}, {Lim::COORD_MAX, Lim::COORD_MAX}},{-707, 707}, -1, -1},
                                                    SegmentUtil::PointPosition::ONLINE},
                             GetPointPositionParam {Point2{ Lim::COORD_MAX, Lim::COORD_MAX},
                                                    Segment{{{Lim::COORD_MIN, Lim::COORD_MIN}, {Lim::COORD_MAX, Lim::COORD_MAX}},{-707, 707}, -1, -1},
                                                    SegmentUtil::PointPosition::ONLINE}
                                                                                       ));


struct MidOffsetParam
{
    Segment s1;
    Segment s2;
    int64_t offset;
    Segment s1_exp;
    Segment s2_exp;
};

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
    
    areSegmentsEqual(p.s1_exp, s1);
    areSegmentsEqual(p.s2_exp, s2);
}
/*
INSTANTIATE_TEST_SUITE_P(midOffset,
                         MidOffsetTest,
                         testing::Values(
                                  ));
*/

} // namespace
