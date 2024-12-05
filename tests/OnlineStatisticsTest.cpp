#include <array>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <ranges>

// uses catch2
#include <catch2/catch_all.hpp>
//#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "OnlineStatistics.h"


int Add( int a, int b ) {
    return a + b;
}

TEST_CASE( "Addition", "[basic]" ) {
    REQUIRE( Add(1,0) == 1 );
    REQUIRE( Add(1,1) == 2 );
    REQUIRE( Add(-1,1) == 0 );
    REQUIRE( Add(236,1) == 237 );
}

// just Approx() does not work
TEST_CASE("Approximate Match", "[approx]") {
    REQUIRE( 1.0 == Catch::Approx(1.000000000001));
}

TEST_CASE("No data", "[onlinestatics1d]") {
    auto stats = OnlineStatistics1D();
    REQUIRE_THAT(stats.Mean(), Catch::Matchers::IsNaN());
    REQUIRE_THAT(stats.Variance(), Catch::Matchers::IsNaN());
    REQUIRE_THAT(stats.SampleVariance(), Catch::Matchers::IsNaN());
}

TEST_CASE("Insufficient data", "[onlinestatics1d]") {
    auto stats = OnlineStatistics1D();
    stats.Insert(0.0);
    REQUIRE_THAT(stats.Mean(), Catch::Matchers::WithinRel(0.0));
    REQUIRE_THAT(stats.Variance(), Catch::Matchers::IsNaN());
    REQUIRE_THAT(stats.SampleVariance(), Catch::Matchers::IsNaN());
}

TEST_CASE("Short array of doubles", "[onlinestatics1d]") {
    std::array<double, 5> list = {1.0, 2.0, 3.0, 4.0, 5.0};
    auto stats = OnlineStatistics1D();
    for (auto& x : list) {
        stats.Insert(x);
    }
    REQUIRE_THAT(stats.Mean(), Catch::Matchers::WithinRel(3.0));
    REQUIRE_THAT(stats.Variance(), Catch::Matchers::WithinRel(2.0));
    REQUIRE_THAT(stats.SampleVariance(), Catch::Matchers::WithinRel(2.5));
}

TEST_CASE("Longer array of doubles", "[onlinestatics1d]") {
    std::array<double, 32> list = {17.0, 100.0, 16.0, 38.0, 28.0, 70.0, 81.0, 25.0,
                                    28.0, 57.0, 84.0, 51.0, 11.0, 96.0, 30.0, 90.0,
                                    21.0, 6.0, 68.0, 30.0, 71.0, 17.0, 49.0, 34.0, 
                                    19.0, 86.0, 40.0, 20.0, 42.0, 93.0, 25.0, 56.0};
    auto stats = OnlineStatistics1D();
    for (auto& x : list) {
        stats.Insert(x);
    }
    REQUIRE_THAT(stats.Mean(), Catch::Matchers::WithinRel(46.84375)) ;
    REQUIRE_THAT(stats.Variance(), Catch::Matchers::WithinRel(796.4443359375));
    REQUIRE_THAT(stats.SampleVariance(), Catch::Matchers::WithinRel(822.1360887096774));
}


TEST_CASE("Incremental stats", "[onlinestatics1d]") {
    auto stats = OnlineStatistics1D();
    stats.Insert(1.0);
    REQUIRE_THAT(stats.Mean(), Catch::Matchers::WithinRel(1.0));
    stats.Insert(2.0);
    REQUIRE_THAT(stats.Mean(), Catch::Matchers::WithinRel(1.5));
    stats.Insert(3.0);
    REQUIRE_THAT(stats.Mean(), Catch::Matchers::WithinRel(2.0));
    stats.Insert(1e13 + 2.0);
    REQUIRE_THAT(stats.Mean(), Catch::Matchers::WithinRel(2.5e12 + 2.0));
}

TEST_CASE("removal","[onlinestatics1d]") {
    auto stats = OnlineStatistics1D();
    stats.Insert(1);
    stats.Insert(2);
    stats.Insert(3);
    REQUIRE_THAT(stats.Mean(), Catch::Matchers::WithinRel(2.0));
    stats.Remove(3);
    REQUIRE_THAT(stats.Mean(), Catch::Matchers::WithinRel(1.5));
    stats.Remove(2);
    REQUIRE_THAT(stats.Mean(), Catch::Matchers::WithinRel(1.0));
    REQUIRE_THAT(stats.Count(), Catch::Matchers::WithinRel(1.0));
}

TEST_CASE("removal large array", "[onlinestatics1d]") {
    std::array<double, 32> list = {17.0, 100.0, 16.0, 38.0, 28.0, 70.0, 81.0, 25.0,
                                    28.0, 57.0, 84.0, 51.0, 11.0, 96.0, 30.0, 90.0,
                                    21.0, 6.0, 68.0, 30.0, 71.0, 17.0, 49.0, 34.0, 
                                    19.0, 86.0, 40.0, 20.0, 42.0, 93.0, 25.0, 56.0};
    auto stats = OnlineStatistics1D();
    for (auto& x : list) {
        stats.Insert(x);
    }
    stats.Remove(56.0);
    REQUIRE_THAT(stats.Mean(), Catch::Matchers::WithinRel(46.54838709677419));
    REQUIRE_THAT(stats.Variance(), Catch::Matchers::WithinRel(819.3444328824144));
    stats.Remove(90.0);
    REQUIRE_THAT(stats.Mean(), Catch::Matchers::WithinRel(45.1));
    REQUIRE_THAT(stats.Variance(), Catch::Matchers::WithinRel(781.6233333333333));
}
/* OnlineStatistics2D */

TEST_CASE("No data", "[onlinestatics2d]") {
    auto stats = OnlineStatistics2D();
    REQUIRE_THAT(stats.MeanX(), Catch::Matchers::IsNaN());
    REQUIRE_THAT(stats.VarianceX(), Catch::Matchers::IsNaN());
    REQUIRE_THAT(stats.SampleVarianceX(), Catch::Matchers::IsNaN());
}

TEST_CASE("Insufficient data", "[onlinestatics2d]") {
    auto stats = OnlineStatistics2D();
    stats.Insert(0.0,0.0);
    REQUIRE_THAT(stats.MeanX(), Catch::Matchers::WithinRel(0.0));
    REQUIRE_THAT(stats.MeanY(), Catch::Matchers::WithinRel(0.0));
    REQUIRE_THAT(stats.VarianceX(), Catch::Matchers::IsNaN());
    REQUIRE_THAT(stats.VarianceY(), Catch::Matchers::IsNaN());
    REQUIRE_THAT(stats.CovarianceXY(), Catch::Matchers::IsNaN());
    REQUIRE_THAT(stats.SampleVarianceX(), Catch::Matchers::IsNaN());
    REQUIRE_THAT(stats.SampleVarianceY(), Catch::Matchers::IsNaN());
    REQUIRE_THAT(stats.SampleCovarianceXY(), Catch::Matchers::IsNaN());
}

TEST_CASE("Trivial covariance", "[onlinestatics2d]") {

    auto stats = OnlineStatistics2D();
    stats.Insert(1.0, 2.0);
    stats.Insert(2.0, 4.0);
    REQUIRE_THAT(stats.CovarianceXY(), Catch::Matchers::WithinRel(0.5));
    REQUIRE_THAT(stats.SampleCovarianceXY(), Catch::Matchers::WithinRel(1.0));
}

TEST_CASE("Straight line", "[onlinestatics2d]") {
    std::array<double, 5> list = {1.0, 2.0, 3.0, 4.0, 5.0};
    auto stats = OnlineStatistics2D();
    for (auto& x : list) {
        stats.Insert(x, x);
    }
    REQUIRE_THAT(stats.MeanX(), Catch::Matchers::WithinRel(3.0));
    REQUIRE_THAT(stats.MeanY(), Catch::Matchers::WithinRel(3.0));
    REQUIRE_THAT(stats.VarianceX(), Catch::Matchers::WithinRel(2.0));
    REQUIRE_THAT(stats.VarianceY(), Catch::Matchers::WithinRel(2.0));
    REQUIRE_THAT(stats.SampleVarianceX(), Catch::Matchers::WithinRel(2.5));
    REQUIRE_THAT(stats.SampleVarianceY(), Catch::Matchers::WithinRel(2.5));
    REQUIRE_THAT(stats.CovarianceXY(), Catch::Matchers::WithinRel(2.0));
    REQUIRE_THAT(stats.SampleCovarianceXY(), Catch::Matchers::WithinRel(2.5));
}


TEST_CASE("Not quite straight line", "[onlinestatics2d]") {
    std::array<double, 5> xvals = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::array<double, 5> yvals = {2.0, 3.8, 6.1, 8.0001, 9.99999999};
    auto stats = OnlineStatistics2D();

    // requires C++20 or maybe later
    for (auto [x, y] : std::views::zip(xvals, yvals)) {
        stats.Insert(x, y);
    }

/* numpy
x=[1.0, 2.0, 3.0, 4.0, 5.0]
y=[2.0, 3.8, 6.1, 8.0001, 9.99999999]
m=np.array([x,y])
m[0].mean(), m[1].mean()
m[0].var(), m[1].var(), m[0].var(ddof=1), m[1].var(ddof=1)
np.cov(m, bias=True)[0][1], np.cov(m, bias=False)[0][1]
np.polyfit(x,y,1)
np.linalg.lstsq(np.vstack([x, np.ones(len(x))]).T,y)[0]
*/

    REQUIRE_THAT(stats.MeanX(), Catch::Matchers::WithinRel(3.0));
    REQUIRE_THAT(stats.MeanY(), Catch::Matchers::WithinRel(5.9800199979999995));
    REQUIRE_THAT(stats.VarianceX(), Catch::Matchers::WithinRel(2.0));
    REQUIRE_THAT(stats.VarianceY(), Catch::Matchers::WithinRel(8.169680785520079));
    REQUIRE_THAT(stats.SampleVarianceX(), Catch::Matchers::WithinRel(2.5));
    REQUIRE_THAT(stats.SampleVarianceY(), Catch::Matchers::WithinRel(10.212100981900099));
    REQUIRE_THAT(stats.CovarianceXY(), Catch::Matchers::WithinRel(4.040019996));
    REQUIRE_THAT(stats.SampleCovarianceXY(), Catch::Matchers::WithinRel(5.050024994999999));

    // Perform linear regression following https://seehuhn.github.io/MATH3714/S01-simple.html
    // Agreement with numpy linalg is a bit worse than other statistics.
    // np.linalg.lstsq(np.vstack([x, np.ones(len(x))]).T,y)[0]
    double slope = stats.SampleCovarianceXY() / stats.SampleVarianceX();
    double intercept = stats.MeanY() - slope * stats.MeanX();
    REQUIRE_THAT(intercept, Catch::Matchers::WithinRel(-0.08001,1e-7));
    REQUIRE_THAT(slope, Catch::Matchers::WithinRel( 2.02001,1e-9)); 
}

TEST_CASE("Random floats", "[onlinestatics2d]") {
    std::array<double, 16> xvals = {0.5525571237, 0.5412206250, 0.8147993422, 0.1510378701, 0.0560028736, 0.3781311581, 0.5456549605, 0.7874939989, 0.9412896414, 0.8458607057, 0.4717614025, 0.8134554498, 0.8864944719, 0.7353193240, 0.9149073578, 0.6548862363};
    std::array<double, 16> yvals = {0.6809272480, 0.7048653974, 0.4096884513, 0.5807519821, 0.3463499743, 0.4886715036, 0.8816185354, 0.0855490408, 0.7777406078, 0.0800553042, 0.7257813523, 0.4143589239, 0.8589390266, 0.1811071473, 0.1962093466, 0.8781437478};
    auto stats = OnlineStatistics2D();

    // requires C++20 or maybe later
    for (auto [x, y] : std::views::zip(xvals, yvals)) {
        stats.Insert(x, y);
    }

/* numpy
x=[0.5525571237, 0.5412206250, 0.8147993422, 0.1510378701, 0.0560028736, 0.3781311581, 0.5456549605, 0.7874939989, 0.9412896414, 0.8458607057, 0.4717614025, 0.8134554498, 0.8864944719, 0.7353193240, 0.9149073578, 0.6548862363]
y=[0.6809272480, 0.7048653974, 0.4096884513, 0.5807519821, 0.3463499743, 0.4886715036, 0.8816185354, 0.0855490408, 0.7777406078, 0.0800553042, 0.7257813523, 0.4143589239, 0.8589390266, 0.1811071473, 0.1962093466, 0.8781437478]
m=np.array([x,y])
m[0].mean(), m[1].mean()
m[0].var(), m[1].var(), m[0].var(ddof=1), m[1].var(ddof=1)
np.cov(m, bias=True)[0][1], np.cov(m, bias=False)[0][1]
np.polyfit(x,y,1)
*/
    REQUIRE_THAT(stats.MeanX(), Catch::Matchers::WithinRel(0.63067953384375));
    REQUIRE_THAT(stats.MeanY(), Catch::Matchers::WithinRel(0.5181723493375));
    REQUIRE_THAT(stats.VarianceX(), Catch::Matchers::WithinRel(0.06644511933383913));
    REQUIRE_THAT(stats.VarianceY(), Catch::Matchers::WithinRel(0.07517831978581213));
    REQUIRE_THAT(stats.SampleVarianceX(), Catch::Matchers::WithinRel(0.07087479395609507));
    REQUIRE_THAT(stats.SampleVarianceY(), Catch::Matchers::WithinRel(0.08019020777153293));
    REQUIRE_THAT(stats.CovarianceXY(), Catch::Matchers::WithinRel(-0.010529283576359396));
    REQUIRE_THAT(stats.SampleCovarianceXY(), Catch::Matchers::WithinRel(-0.011231235814783356));
}

TEST_CASE("removal","[onlinestatics2d]") {
    auto stats = OnlineStatistics2D();
    stats.Insert(1,3);
    stats.Insert(2,2);
    stats.Insert(3,1);
    REQUIRE_THAT(stats.MeanX(), Catch::Matchers::WithinRel(2.0));
    REQUIRE_THAT(stats.MeanY(), Catch::Matchers::WithinRel(2.0));
    stats.Remove(3,1);
    REQUIRE_THAT(stats.MeanX(), Catch::Matchers::WithinRel(1.5));
    REQUIRE_THAT(stats.MeanY(), Catch::Matchers::WithinRel(2.5));
    stats.Remove(2,2);
    REQUIRE_THAT(stats.MeanX(), Catch::Matchers::WithinRel(1.0));
    REQUIRE_THAT(stats.Count(), Catch::Matchers::WithinRel(1.0));
}


TEST_CASE("Random floats with remove", "[onlinestatics2d]") {
    std::array<double, 16> xvals = {0.5525571237, 0.5412206250, 0.8147993422, 0.1510378701, 0.0560028736, 0.3781311581, 0.5456549605, 0.7874939989, 0.9412896414, 0.8458607057, 0.4717614025, 0.8134554498, 0.8864944719, 0.7353193240, 0.9149073578, 0.6548862363};
    std::array<double, 16> yvals = {0.6809272480, 0.7048653974, 0.4096884513, 0.5807519821, 0.3463499743, 0.4886715036, 0.8816185354, 0.0855490408, 0.7777406078, 0.0800553042, 0.7257813523, 0.4143589239, 0.8589390266, 0.1811071473, 0.1962093466, 0.8781437478};
    auto stats = OnlineStatistics2D();

    // requires C++20 or maybe later
    for (auto [x, y] : std::views::zip(xvals, yvals)) {
        stats.Insert(x, y);
    }

    stats.Remove(0.1510378701, 0.5807519821);
    stats.Remove(0.9412896414, 0.7777406078);
    stats.Remove(0.8134554498, 0.4143589239);
    stats.Remove(0.5525571237, 0.6809272480);

/* numpy
x=[0.5412206250, 0.8147993422, 0.0560028736, 0.3781311581, 0.5456549605, 0.7874939989, 0.8458607057, 0.4717614025, 0.8864944719, 0.7353193240, 0.9149073578, 0.6548862363]
y=[0.7048653974, 0.4096884513, 0.3463499743, 0.4886715036, 0.8816185354, 0.0855490408, 0.0800553042, 0.7257813523, 0.8589390266, 0.1811071473, 0.1962093466, 0.8781437478]
m=np.array([x,y])
m[0].mean(), m[1].mean()
m[0].var(), m[1].var(), m[0].var(ddof=1), m[1].var(ddof=1)
np.cov(m, bias=True)[0][1], np.cov(m, bias=False)[0][1]
np.polyfit(x,y,1)
*/
    REQUIRE_THAT(stats.MeanX(), Catch::Matchers::WithinRel(0.636044371375));
    REQUIRE_THAT(stats.MeanY(), Catch::Matchers::WithinRel(0.48641490229999995));
    REQUIRE_THAT(stats.VarianceX(), Catch::Matchers::WithinRel(0.058060968385441114));
    REQUIRE_THAT(stats.VarianceY(), Catch::Matchers::WithinRel(0.09018270130727217));
    REQUIRE_THAT(stats.SampleVarianceX(), Catch::Matchers::WithinRel(0.06333923823866304));
    REQUIRE_THAT(stats.SampleVarianceY(), Catch::Matchers::WithinRel(0.09838112869884236));
    REQUIRE_THAT(stats.CovarianceXY(), Catch::Matchers::WithinRel(-0.015445281777668733));
    REQUIRE_THAT(stats.SampleCovarianceXY(), Catch::Matchers::WithinRel(-0.016849398302911347));
}


/* numpy
x=[ -1.0, -1.0, 0.0, 0.0, 1.0, 1.0 ]
y=[ -1.0,  1.0, 0.0, 2.0, 1.0, 3.0 ]
m=np.array([x,y])
m[0].mean(), m[1].mean()
m[0].var(), m[1].var(), m[0].var(ddof=1), m[1].var(ddof=1)
np.cov(m, bias=True)[0][1], np.cov(m, bias=False)[0][1]
np.polyfit(x,y,1)
np.linalg.lstsq(np.vstack([x, np.ones(len(x))]).T,y)[0]
*/
TEST_CASE("data with bestfit y = x + 1", "[onlinestatics2d]") {
    std::array<double, 6> xvals = { -1.0, -1.0, 0.0, 0.0, 1.0, 1.0 };
    std::array<double, 6> yvals = { -1.0,  1.0, 0.0, 2.0, 1.0, 3.0};
    auto stats = OnlineStatistics2D();

    // requires C++20 or maybe later
    for (auto [x, y] : std::views::zip(xvals, yvals)) {
        stats.Insert(x, y);
    }
    REQUIRE_THAT(stats.MeanX(), Catch::Matchers::WithinAbs(0.0,1e-12));
    REQUIRE_THAT(stats.MeanY(), Catch::Matchers::WithinRel(1.0));
    REQUIRE_THAT(stats.VarianceX(), Catch::Matchers::WithinRel(0.6666666666666666));
    REQUIRE_THAT(stats.VarianceY(), Catch::Matchers::WithinRel(1.6666666666666667));
    REQUIRE_THAT(stats.SampleVarianceX(), Catch::Matchers::WithinRel(0.8));
    REQUIRE_THAT(stats.SampleVarianceY(), Catch::Matchers::WithinRel(2.0));
    REQUIRE_THAT(stats.CovarianceXY(), Catch::Matchers::WithinRel(0.6666666666666666));
    REQUIRE_THAT(stats.SampleCovarianceXY(), Catch::Matchers::WithinRel(0.8));

    double slope = stats.SampleCovarianceXY() / stats.SampleVarianceX();
    double intercept = stats.MeanY() - slope * stats.MeanX();
    REQUIRE_THAT(slope, Catch::Matchers::WithinRel(1.0));
    REQUIRE_THAT(intercept, Catch::Matchers::WithinRel(1.0));
}

/* numpy 
rng = np.random.default_rng(12345)
x = np.array([i + rng.random() - 0.5 for i in range(25)])
y = np.array([i + rng.random() - 0.5 for i in range(25)])
>>> x
array([-0.27266398,  0.81675834,  2.29736546,  3.17625467,  3.89110955,
        4.83281393,  6.09830875,  6.68673419,  8.17275604,  9.44180287,
        9.74824571, 11.44888115, 12.16723745, 12.59589794, 13.94183967,
       15.38647992, 16.1974535 , 16.82647286, 18.23392816, 18.72013496,
       19.58159457, 20.6598956 , 21.84010018, 22.96519315, 23.76642103])
>>> y
array([ 0.3157764 ,  0.69329439,  1.62946908,  2.59166475,  4.09856801,
        5.3547419 ,  6.10162124,  7.43198836,  8.22478136,  9.36055132,
       10.4293378 , 11.04618601, 12.43767296, 12.99498794, 13.77377318,
       14.95177871, 16.16503892, 16.83089093, 18.40345401, 18.75707418,
       19.83982834, 20.7588534 , 21.85544648, 22.50502233, 24.12860454])
m=np.array([x,y])
m[0].mean(), m[1].mean()
m[0].var(), m[1].var(), m[0].var(ddof=1), m[1].var(ddof=1)
np.cov(m, bias=True)[0][1], np.cov(m, bias=False)[0][1]
np.polyfit(x,y,1)
np.linalg.lstsq(np.vstack([x, np.ones(len(x))]).T,y)[0]
*/
TEST_CASE("random slope near 1.0", "[onlinestatics2d]") {
    std::array<double, 25> xvals = {
        -0.27266398, 0.81675834,  2.29736546,  3.17625467,  3.89110955,
         4.83281393, 6.09830875,  6.68673419,  8.17275604,  9.44180287,
         9.74824571, 11.44888115, 12.16723745, 12.59589794, 13.94183967,
        15.38647992, 16.1974535 , 16.82647286, 18.23392816, 18.72013496,
        19.58159457, 20.6598956 , 21.84010018, 22.96519315, 23.76642103 };
    std::array<double, 25> yvals = {
        0.3157764 ,  0.69329439,  1.62946908,  2.59166475,  4.09856801,
        5.3547419 ,  6.10162124,  7.43198836,  8.22478136,  9.36055132,
       10.4293378 , 11.04618601, 12.43767296, 12.99498794, 13.77377318,
       14.95177871, 16.16503892, 16.83089093, 18.40345401, 18.75707418,
       19.83982834, 20.7588534 , 21.85544648, 22.50502233, 24.12860454 };
    auto stats = OnlineStatistics2D();

    // requires C++20 or maybe later
    for (auto [x, y] : std::views::zip(xvals, yvals)) {
        stats.Insert(x, y);
    }
    // needing to customize margin, use CHECK_THAT so we keep going
    CHECK_THAT(stats.MeanX(), Catch::Matchers::WithinRel(11.968840627129982,1e-9));
    CHECK_THAT(stats.MeanY(), Catch::Matchers::WithinRel(12.027216261969004,1e-9));
    CHECK_THAT(stats.VarianceX(), Catch::Matchers::WithinRel(51.31807432427908,1e-9));
    CHECK_THAT(stats.VarianceY(), Catch::Matchers::WithinRel(51.216447073764414,1e-9));
    CHECK_THAT(stats.SampleVarianceX(), Catch::Matchers::WithinRel(53.45632742112404,1e-9));
    CHECK_THAT(stats.SampleVarianceY(), Catch::Matchers::WithinRel(53.350465701837926,1e-9));
    CHECK_THAT(stats.CovarianceXY(), Catch::Matchers::WithinRel(51.19784460521081,1e-9));
    CHECK_THAT(stats.SampleCovarianceXY(), Catch::Matchers::WithinRel(53.33108813042793,1e-9));

    double slope = stats.SampleCovarianceXY() / stats.SampleVarianceX();
    double intercept = stats.MeanY() - slope * stats.MeanX();
    CHECK_THAT(slope, Catch::Matchers::WithinRel(0.99765717,1e-7));
    CHECK_THAT(intercept, Catch::Matchers::WithinRel(0.08641664,1e-6));
}


TEST_CASE("add 31 points, remove 25", "[onlinestatics2d]") {
    std::array<double, 31> xvals = {
        -0.27266398, 0.81675834,  2.29736546,  3.17625467,  3.89110955,
         4.83281393, 6.09830875,  6.68673419,  8.17275604,  9.44180287,
         9.74824571, 11.44888115, 12.16723745, 12.59589794, 13.94183967,
        15.38647992, 16.1974535 , 16.82647286, 18.23392816, 18.72013496,
        19.58159457, 20.6598956 , 21.84010018, 22.96519315, 23.76642103,
         -1.0, -1.0, 0.0, 0.0, 1.0, 1.0 };
    std::array<double, 31> yvals = {
        0.3157764 ,  0.69329439,  1.62946908,  2.59166475,  4.09856801,
        5.3547419 ,  6.10162124,  7.43198836,  8.22478136,  9.36055132,
       10.4293378 , 11.04618601, 12.43767296, 12.99498794, 13.77377318,
       14.95177871, 16.16503892, 16.83089093, 18.40345401, 18.75707418,
       19.83982834, 20.7588534 , 21.85544648, 22.50502233, 24.12860454,
        -1.0,  1.0, 0.0, 2.0, 1.0, 3.0 };
    auto stats = OnlineStatistics2D();

    // requires C++20 or maybe later
    for (auto [x, y] : std::views::zip(xvals, yvals)) {
        stats.Insert(x, y);
    }
    int i = 0;
    for (auto [x, y] : std::views::zip(xvals, yvals)) {
        stats.Remove(x, y);
        ++i;
        if (i >= 25) break;
    }
    CHECK_THAT(stats.MeanX(), Catch::Matchers::WithinAbs(0.0,1e-10));
    CHECK_THAT(stats.MeanY(), Catch::Matchers::WithinRel(1.0,1e-9));
    CHECK_THAT(stats.VarianceX(), Catch::Matchers::WithinRel(0.6666666666666666,1e-9));
    CHECK_THAT(stats.VarianceY(), Catch::Matchers::WithinRel(1.6666666666666667,1e-9));
    CHECK_THAT(stats.SampleVarianceX(), Catch::Matchers::WithinRel(0.8,1e-9));
    CHECK_THAT(stats.SampleVarianceY(), Catch::Matchers::WithinRel(2.0,1e-9));
    CHECK_THAT(stats.CovarianceXY(), Catch::Matchers::WithinRel(0.6666666666666666,1e-9));
    CHECK_THAT(stats.SampleCovarianceXY(), Catch::Matchers::WithinRel(0.8,1e-9));

    double slope = stats.SampleCovarianceXY() / stats.SampleVarianceX();
    double intercept = stats.MeanY() - slope * stats.MeanX();
    CHECK_THAT(slope, Catch::Matchers::WithinRel(1.0,1e-9));
    CHECK_THAT(intercept, Catch::Matchers::WithinRel(1.0,1e-9));
}


