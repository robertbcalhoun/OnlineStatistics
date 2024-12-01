/*
 * OnlineStatistics.h
 *
 *  Created on: Nov 26, 2024
 *
 * (c) 2024 by SoundThinking Inc.
 * 
 * http://www.shotspotter.com
 *
 * See Licenses/sst/license.txt for license terms.
 *
 * Author: Robert Calhoun <rcalhoun@soundthinking.com>
 * Many of the algorithms in this file from
 * https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance
 */

#ifndef INC_SUPPORT_ONLINESTATISTICS_H_
#define INC_SUPPORT_ONLINESTATISTICS_H_

class OnlineStatistics1D {
private:
    double count;
    double max_count;
    double mean;
    double m2;
public:
    OnlineStatistics1D();
    OnlineStatistics1D(int windowSize);
    virtual ~OnlineStatistics1D(void);
    int Update(double value);
    double Count(void);
    double Mean(void);
    double Variance(void);
    double SampleVariance(void);
};

class OnlineStatistics2D {
private:
    double count;
    double max_count;
    double x_mean;
    double y_mean;
    double m2x;
    double m2y;
    double mxy;
public:
    OnlineStatistics2D() : OnlineStatistics2D(-1){};
    OnlineStatistics2D(int windowSize);
    virtual ~OnlineStatistics2D(void);
    int Update(double x_value, double y_value);
    double Count(void);
    double MeanX(void);
    double MeanY(void);
    double VarianceX(void);
    double VarianceY(void);
    double SampleVarianceX(void);
    double SampleVarianceY(void);
    double CovarianceXY(void);
    double CovarianceYX(void);
    double SampleCovarianceXY(void);
    double SampleCovarianceYX(void);
};

class StatisticResult1D {
public:
    double Mean;
    double Variance;
    double SampleVariance;
    StatisticResult1D(double mean, double variance, double sample_variance);
    ~StatisticResult1D(void);
};

class StatisticResult2D {
public:
    double MeanX;
    double VarianceX;
    double SampleVarianceX;
	double MeanY;
    double VarianceY;
    double SampleVarianceY;
	double Covariance;
    StatisticResult2D(double meanx, double variancex, double sample_variancex,
					double meany, double variancey, double sample_variancey,
					double covariance);
    ~StatisticResult2D(void);
};

#endif /* INC_SUPPORT_ONLINESTATISTICS_H_ */
