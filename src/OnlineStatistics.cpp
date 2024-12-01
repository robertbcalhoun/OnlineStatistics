/* OnlineStatistics.cpp
**
** (c) 2024 SoundThinking, Inc 
** Robert B. Calhoun <rcalhoun@shotspotter.com>
**
** SPDX short identifier: MIT
*/

#include "OnlineStatistics.h"
#include <math.h>
#include <limits>


/*** OnlineStatistics1D ***/

OnlineStatistics1D::OnlineStatistics1D(int windowSize) {
    count = 0.0;
    max_count = (double) windowSize;
    mean = 0.0;
    m2 = 0.0;
}

OnlineStatistics1D::OnlineStatistics1D():OnlineStatistics1D::OnlineStatistics1D(-1) {
}

OnlineStatistics1D::~OnlineStatistics1D(void) {
}

int OnlineStatistics1D::Update(double value) {
    if (max_count < 0 || count < max_count ) { ++count; }
    double delta = value - mean;
    mean += delta / count;
    double delta2 = value - mean;
    m2 += delta * delta2;
    return (int) count;
}

double OnlineStatistics1D::Count(void) {
    return count;
}

double OnlineStatistics1D::Mean(void) {
    if (count < 1) {
        return NAN;
    } else {
        return mean;
    }
}

double OnlineStatistics1D::Variance(void) {
    if (count < 2) {
        return NAN;
    } else {
        return m2 / count;
    }
}

double OnlineStatistics1D::SampleVariance(void) {
    if (count < 2) {
        return NAN;
    } else {
        return m2 / (count - 1.0);
    }
}

/*** OnlineStatistics2D ***/


OnlineStatistics2D::OnlineStatistics2D(int windowSize = -1) {
    count = 0.0;
    max_count = (double) windowSize;
    x_mean = 0.0;
    y_mean = 0.0;
    m2x = 0.0;
    m2y = 0.0;
    mxy = 0.0;
}

OnlineStatistics2D::~OnlineStatistics2D(void) {
}

int OnlineStatistics2D::Update(double x_value, double y_value) {
    if (max_count < 0 || count < max_count ) { ++count; }
    double deltax = x_value - x_mean;
    x_mean += deltax / count;
    double deltax2 = x_value - x_mean;
    
    double deltay = y_value - y_mean;
    y_mean += deltay / count;
    double deltay2 = y_value - y_mean;

    mxy += deltax * deltay2;
    m2x += deltax * deltax2;
    m2y += deltay * deltay2;

    return (int) count;
}

double OnlineStatistics2D::Count(void) {
    return count;
}

double OnlineStatistics2D::MeanX(void) {
    if (count < 1) {
        return NAN;
    } else {
        return x_mean;
    }
}

double OnlineStatistics2D::MeanY(void) {
    if (count < 1) {
        return NAN;
    } else {
        return y_mean;
    }
}

double OnlineStatistics2D::VarianceX(void) {
    if (count < 2) {
        return NAN;
    } else {
        return m2x / count;
    }
}

double OnlineStatistics2D::SampleVarianceX(void) {
    if (count < 2) {
        return NAN;
    } else {
        return m2x / (count - 1.0);
    }
}

double OnlineStatistics2D::VarianceY(void) {
    if (count < 2) {
        return NAN;
    } else {
        return m2y / count;
    }
}

double OnlineStatistics2D::SampleVarianceY(void) {
    if (count < 2) {
        return NAN;
    } else {
        return m2y / (count - 1.0);
    }
}

double OnlineStatistics2D::CovarianceXY(void) {
    if (count < 2) {
        return NAN;
    } else {
        return mxy / count;
    }
}

double OnlineStatistics2D::SampleCovarianceXY(void) {
    if (count < 2) {
        return NAN;
    } else {
        return mxy / (count - 1.0);
    }
}


/***********************/

StatisticResult1D::StatisticResult1D(double mean, double variance, double sample_variance) {
    Mean = mean;
    Variance = variance;
    SampleVariance = sample_variance;
}

StatisticResult1D::~StatisticResult1D(void) {
}