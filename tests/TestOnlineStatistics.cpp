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
    stats.Update(0.0);
    REQUIRE_THAT(stats.Mean(), Catch::Matchers::WithinRel(0.0));
    REQUIRE_THAT(stats.Variance(), Catch::Matchers::IsNaN());
    REQUIRE_THAT(stats.SampleVariance(), Catch::Matchers::IsNaN());
}

TEST_CASE("Short array of doubles", "[onlinestatics1d]") {
    std::array<double, 5> list = {1.0, 2.0, 3.0, 4.0, 5.0};
    auto stats = OnlineStatistics1D();
    for (auto& x : list) {
        stats.Update(x);
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
        stats.Update(x);
    }
    REQUIRE_THAT(stats.Mean(), Catch::Matchers::WithinRel(46.84375)) ;
    REQUIRE_THAT(stats.Variance(), Catch::Matchers::WithinRel(796.4443359375));
    REQUIRE_THAT(stats.SampleVariance(), Catch::Matchers::WithinRel(822.1360887096774));
}


TEST_CASE("Incremental stats", "[onlinestatics1d]") {
    auto stats = OnlineStatistics1D();
    stats.Update(1.0);
    REQUIRE_THAT(stats.Mean(), Catch::Matchers::WithinRel(1.0));
    stats.Update(2.0);
    REQUIRE_THAT(stats.Mean(), Catch::Matchers::WithinRel(1.5));
    stats.Update(3.0);
    REQUIRE_THAT(stats.Mean(), Catch::Matchers::WithinRel(2.0));
    stats.Update(1e13 + 2.0);
    REQUIRE_THAT(stats.Mean(), Catch::Matchers::WithinRel(2.5e12 + 2.0));
}

TEST_CASE("removal","[onlinestatics1d]") {
    auto stats = OnlineStatistics1D();
    stats.Update(1);
    stats.Update(2);
    stats.Update(3);
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
        stats.Update(x);
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
    stats.Update(0.0,0.0);
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
    stats.Update(1.0, 2.0);
    stats.Update(2.0, 4.0);
    REQUIRE_THAT(stats.CovarianceXY(), Catch::Matchers::WithinRel(0.5));
    REQUIRE_THAT(stats.SampleCovarianceXY(), Catch::Matchers::WithinRel(1.0));
}

TEST_CASE("Straight line", "[onlinestatics2d]") {
    std::array<double, 5> list = {1.0, 2.0, 3.0, 4.0, 5.0};
    auto stats = OnlineStatistics2D();
    for (auto& x : list) {
        stats.Update(x, x);
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
        stats.Update(x, y);
    }

/* numpy
x=[1.0, 2.0, 3.0, 4.0, 5.0]
y=[2.0, 3.8, 6.1, 8.0001, 9.99999999]
m=np.array([x,y])
m[0].mean(), m[1].mean()
m[0].var(), m[1].var(), m[0].var(ddof=1), m[1].var(ddof=1)
np.cov(m, bias=True)[0][1], np.cov(m, bias=False)[0][1]
np.polyfit(x,y,1)
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
    double slope = stats.CovarianceXY() / stats.VarianceX();
    double intercept = stats.MeanY() - slope * stats.MeanX();
    REQUIRE_THAT(intercept, Catch::Matchers::WithinRel(-0.08001,1e-6));
    REQUIRE_THAT(slope, Catch::Matchers::WithinRel( 2.02001,1e-6)); 
}

TEST_CASE("Random floats", "[onlinestatics2d]") {
    std::array<double, 16> xvals = {0.5525571237, 0.5412206250, 0.8147993422, 0.1510378701, 0.0560028736, 0.3781311581, 0.5456549605, 0.7874939989, 0.9412896414, 0.8458607057, 0.4717614025, 0.8134554498, 0.8864944719, 0.7353193240, 0.9149073578, 0.6548862363};
    std::array<double, 16> yvals = {0.6809272480, 0.7048653974, 0.4096884513, 0.5807519821, 0.3463499743, 0.4886715036, 0.8816185354, 0.0855490408, 0.7777406078, 0.0800553042, 0.7257813523, 0.4143589239, 0.8589390266, 0.1811071473, 0.1962093466, 0.8781437478};
    auto stats = OnlineStatistics2D();

    // requires C++20 or maybe later
    for (auto [x, y] : std::views::zip(xvals, yvals)) {
        stats.Update(x, y);
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

    double slope = stats.CovarianceXY() / stats.VarianceX();
    double intercept = stats.MeanY() - slope * stats.MeanX();
    REQUIRE_THAT(intercept, Catch::Matchers::WithinRel( 0.61811353,1e-6));
    REQUIRE_THAT(slope, Catch::Matchers::WithinRel(-0.15846587,1e-6));
}

TEST_CASE("removal","[onlinestatics2d]") {
    auto stats = OnlineStatistics2D();
    stats.Update(1,3);
    stats.Update(2,2);
    stats.Update(3,1);
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
        stats.Update(x, y);
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

    double slope = stats.CovarianceXY() / stats.VarianceX();
    double intercept = stats.MeanY() - slope * stats.MeanX();
    REQUIRE_THAT(intercept, Catch::Matchers::WithinRel( 0.65561436, 1e-6));
    REQUIRE_THAT(slope, Catch::Matchers::WithinRel(-0.26601833, 1e-6));
}


TEST_CASE("Sawtooth", "[onlinestatics2d]") {
    // triangle wave; add all 10, then remove first 7, should get slope 1.0 intecept -8.0
    std::array<double, 10> xvals = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    std::array<double, 10> yvals = {0.0, 1.0, 2.0, 1.0, 0.0,-1.0,-2.0,-1.0, 0.0, 1.0};  
    auto stats = OnlineStatistics2D();

    // requires C++20 or maybe later
    for (auto [x, y] : std::views::zip(xvals, yvals)) {
        stats.Update(x, y);
    }

    int i = 0;
    for (auto [x, y] : std::views::zip(xvals, yvals)) {
        stats.Remove(x, y);
        ++i;
        if (i >= 7) break;
    }

/* numpy
x=[ 7.0, 8.0, 9.0]
y=[-1.0, 0.0, 1.0]
m=np.array([x,y])
m[0].mean(), m[1].mean()
m[0].var(), m[1].var(), m[0].var(ddof=1), m[1].var(ddof=1)
np.cov(m, bias=True)[0][1], np.cov(m, bias=False)[0][1]
np.polyfit(x,y,1)
*/

    REQUIRE_THAT(stats.MeanX(), Catch::Matchers::WithinRel(8.0));
    REQUIRE_THAT(stats.MeanY(), Catch::Matchers::WithinRel(0.0));
    REQUIRE_THAT(stats.VarianceX(), Catch::Matchers::WithinRel(0.6666666666666666));
    REQUIRE_THAT(stats.VarianceY(), Catch::Matchers::WithinRel(0.6666666666666666));
    REQUIRE_THAT(stats.SampleVarianceX(), Catch::Matchers::WithinRel(1.0));
    REQUIRE_THAT(stats.SampleVarianceY(), Catch::Matchers::WithinRel(1.0));
    REQUIRE_THAT(stats.CovarianceXY(), Catch::Matchers::WithinRel(0.6666666666666666));
    REQUIRE_THAT(stats.SampleCovarianceXY(), Catch::Matchers::WithinRel(1.0));

    // Perform linear regression following https://seehuhn.github.io/MATH3714/S01-simple.html
    // Agreement with numpy linalg is a bit worse than other statistics.
    // np.linalg.lstsq(np.vstack([x, np.ones(len(x))]).T,y)[0]
    double slope = stats.CovarianceXY() / stats.VarianceX();
    double intercept = stats.MeanY() - slope * stats.MeanX();
    REQUIRE_THAT(slope, Catch::Matchers::WithinRel(1.0));
    REQUIRE_THAT(intercept, Catch::Matchers::WithinRel(-8.0));
}
