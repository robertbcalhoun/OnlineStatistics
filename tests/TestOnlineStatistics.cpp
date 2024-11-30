#include <array>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <ranges>

// uses catch2
#include <catch2/catch_all.hpp>
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

TEST_CASE("Short array of doubles", "[onlinestatics1d]") {
    std::array<double, 5> list = {1.0, 2.0, 3.0, 4.0, 5.0};
    auto stats = OnlineStatistics1D();
    for (auto& x : list) {
        stats.Update(x);
    }
    REQUIRE( stats.Mean() == 3.0) ;
    REQUIRE( stats.Variance() == 2.0);
    REQUIRE( stats.SampleVariance() == 2.5 );
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
    REQUIRE( Add(1,0) == 1 );
    REQUIRE( stats.Mean() == 46.84375) ;
    REQUIRE( stats.Variance() == 796.4443359375);
    REQUIRE( stats.SampleVariance() == 822.1360887096774 );
}

