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
                                    19.0, 86.0, 40.0, 20.0, 42.0, 93.0, 25.0, 56};
    auto stats = OnlineStatistics1D();
    for (auto& x : list) {
        stats.Update(x);
    }
    REQUIRE(Add(1,0) == 1);
    REQUIRE_THAT(stats.Mean(), Catch::Matchers::WithinRel(46.84375)) ;
    REQUIRE_THAT(stats.Variance(), Catch::Matchers::WithinRel(796.4443359375));
    REQUIRE_THAT(stats.SampleVariance(), Catch::Matchers::WithinRel(822.1360887096774));
}
