#include <iostream>
#include <format>
#include <cmath>
#include <tuple>
#include <random>
#include "OnlineStatistics.h"

typedef std::tuple<double, double> CurveFit;

bool printit(double x) {
    std::cout << std::format("{:.15f}\n", x);
    return true;
}

 CurveFit bestfit(OnlineStatistics2D s) {
    double slope = s.CovarianceXY() / s.VarianceX();
    double intercept = s.MeanY() - slope * s.MeanX();
    return std::make_tuple(slope, intercept);
};

int main() {
    OnlineStatistics1D stats = OnlineStatistics1D();
    stats.Insert(1.0);
    stats.Insert(2.0);
    stats.Insert(3.0);
    std::cout << std::format("mean: {:.5f}, variance: {:.5f}\n", stats.Mean(), stats.Variance());
    stats.Remove(2.0);
    std::cout << std::format("mean: {:.5f}, variance: {:.5f}\n", stats.Mean(), stats.Variance());

    // reset statistics
    stats = OnlineStatistics1D();
    int iters = 30;
    stats.Insert(1.0);
    printit(stats.Mean());
    for (int i=0; i<iters; i++) {
        stats.Insert(0.0);
        printit(stats.Mean());
    }
    std::cout << std::format("\nexpect: {:.15f}\n", 1.0/31.0);


    std::cout << std::endl;
    std::cout << "Moving linear regression example" << std::endl;
    std::cout << "Linear fit to linear + rnd() data" << std::endl;
    auto stats2d = OnlineStatistics2D();
    iters=100;
    // std::normal_distribution offset of y-values
    double epsilon = 0.1;
    std::random_device rd{};
    std::default_random_engine gen{rd()};
    std::normal_distribution dist{0.0, epsilon};


    for (int i = 0; i < iters; ++i) {
        double newval = (double) i + dist(gen);
        stats2d.Insert((double) i, newval);
        //double slope, intercept;
        const auto [slope, intercept] = bestfit(stats2d);
        std::cout << std::format("update ({:4d}, {:4.6f}), mean={:8.6f}, y = {:8.6f} x + {:8.6f}\n", i, newval, stats2d.MeanY(), slope, intercept);
    }

    exit(0);
}