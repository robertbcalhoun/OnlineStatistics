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

OnlineStatistics1D::OnlineStatistics1D(void) {
    count = 0.0;
    mean = 0.0;
    m2 = 0.0;
}

OnlineStatistics1D::~OnlineStatistics1D(void) {
}

int OnlineStatistics1D::Insert(double value) {
    ++count;
    double delta = value - mean;
    mean += delta / count;
    double delta2 = value - mean;
    m2 += delta * delta2;
    return (int) count;
}

int OnlineStatistics1D::Remove(double value) {
    --count;
    double delta = value - mean;
    mean -= delta / count;
    double delta2 = value - mean;
    m2 -= delta * delta2;
    return (int) count;
}

double OnlineStatistics1D::Count(void) {
    return count;
}

double OnlineStatistics1D::Mean(void) {
    if (count < 1) {
        return std::numeric_limits<double>::quiet_NaN();
    } else {
        return mean;
    }
}

double OnlineStatistics1D::Variance(void) {
    if (count < 2) {
        return std::numeric_limits<double>::quiet_NaN();
    } else {
        return m2 / count;
    }
}

double OnlineStatistics1D::SampleVariance(void) {
    if (count < 2) {
        return std::numeric_limits<double>::quiet_NaN();
    } else {
        return m2 / (count - 1.0);
    }
}

/*** OnlineStatistics2D ***/


OnlineStatistics2D::OnlineStatistics2D() {
    count = 0.0;
    x_mean = 0.0;
    y_mean = 0.0;
    m2x = 0.0;
    m2y = 0.0;
    mxy = 0.0;
}

OnlineStatistics2D::~OnlineStatistics2D(void) {
}

int OnlineStatistics2D::Insert(double x_value, double y_value) {
    ++count;
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

int OnlineStatistics2D::Remove(double x_value, double y_value) {
    --count;
    double deltax = x_value - x_mean;
    x_mean -= deltax / count;
    double deltax2 = x_value - x_mean;
    
    double deltay = y_value - y_mean;
    y_mean -= deltay / count;
    double deltay2 = y_value - y_mean;

    mxy -= deltax * deltay2;
    m2x -= deltax * deltax2;
    m2y -= deltay * deltay2;

    return (int) count;
}

double OnlineStatistics2D::Count(void) {
    return count;
}

double OnlineStatistics2D::MeanX(void) {
    if (count < 1) {
        return std::numeric_limits<double>::quiet_NaN();
    } else {
        return x_mean;
    }
}

double OnlineStatistics2D::MeanY(void) {
    if (count < 1) {
        return std::numeric_limits<double>::quiet_NaN();
    } else {
        return y_mean;
    }
}

double OnlineStatistics2D::VarianceX(void) {
    if (count < 2) {
        return std::numeric_limits<double>::quiet_NaN();
    } else {
        return m2x / count;
    }
}

double OnlineStatistics2D::SampleVarianceX(void) {
    if (count < 2) {
        return std::numeric_limits<double>::quiet_NaN();
    } else {
        return m2x / (count - 1.0);
    }
}

double OnlineStatistics2D::VarianceY(void) {
    if (count < 2) {
        return std::numeric_limits<double>::quiet_NaN();
    } else {
        return m2y / count;
    }
}

double OnlineStatistics2D::SampleVarianceY(void) {
    if (count < 2) {
        return std::numeric_limits<double>::quiet_NaN();
    } else {
        return m2y / (count - 1.0);
    }
}

double OnlineStatistics2D::CovarianceXY(void) {
    if (count < 2) {
        return std::numeric_limits<double>::quiet_NaN();
    } else {
        return mxy / count;
    }
}

double OnlineStatistics2D::SampleCovarianceXY(void) {
    if (count < 2) {
        return std::numeric_limits<double>::quiet_NaN();
    } else {
        return mxy / (count - 1.0);
    }
}
