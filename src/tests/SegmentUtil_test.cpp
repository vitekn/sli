#include "../lib/SegmentUtil.h"
#include "../lib/Point2.h"
#include "gtest/gtest.h"

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

INSTANTIATE_TEST_SUITE_P(getPointPosition,
                         GetPointPositionTest,
                         testing::Values(
                             GetPointPositionParam {Point2{-1000,  1000}, Segment{{{-1000, -1000}, {1000, 1000}},{-707, 707}, -1, -1}, SegmentUtil::PointPosition::OUTSIDE},
                             GetPointPositionParam {Point2{ 1000, -1000}, Segment{{{-1000, -1000}, {1000, 1000}},{-707, 707}, -1, -1}, SegmentUtil::PointPosition::INSIDE} ));
} // namespace
