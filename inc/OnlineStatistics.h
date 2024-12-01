/*
 * OnlineStatistics.h
 *
 * Created on: Nov 26, 2024
 *
 * (c) 2024 by SoundThinking Inc.
 * Robert Calhoun <rcalhoun@soundthinking.com>
 *
 * Classes to compute the running mean, variance and covariance of a distribution
 * using the online Welford algorithm as presented in 
 * https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance
 *
 * This class diffs from Welford in that an averaging length n can optionally
 * be defined in the constructor. This will approximate a moving average of the last
 * n values. Note as a type of IIR filter it will not give the same answer
 * as a real last-n moving average. Users need in particular to be wary of 
 * poisoning an instance with NaN or infinite values, which once inserted will
 * never leave.
 *
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
