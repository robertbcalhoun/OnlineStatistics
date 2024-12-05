OnlineStatistics
----------------
This repo contains classes to compute the mean, variance and covariance of single-variable and two-variable datasets using the online Welford algorithm.

The code derives from the [Wikipedia](https://wikipedia.org) article ["Algorithms for calculating variance"](https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance). Because computation of the mean and variance doesn't depend on order, the Welford algorithm can also be used in reverse to update the mean and variance when a sample is removed. We still have to track which values are in the dataset in order to remove them, but we preserve numeric stability while dramatically reducing the amount of computation required to keep the statistics up-to-date.

### Minimal Example
```
#include <iostream>
#include "OnlineStatistics.h"

int main() {
    auto stats = OnlineStatistics1D();
    stats.Insert(1.0);
    stats.Insert(2.0);
    stats.Insert(3.0);
    std::cout << std::format("mean: {:.5f}, var: {:.5f}\n", stats.Mean(), stats.Variance());
    stats.Remove(2.0);
    std::cout << std::format("mean: {:.5f}, var: {:.5f}\n", stats.Mean(), stats.Variance());
    exit(0);
}

Outputs:
mean: 2.00000, var: 0.66667
mean: 2.00000, var: 1.00000

```
### Applications

The least-squares linear fit of a 2D dataset can be derived from these basic statistics, see [this very nice writeup](https://seehuhn.github.io/MATH3714/S01-simple.html) by [Jochen Voss](https://www.youtube.com/channel/UCAqF9X0DqdsZroyGL8zWl8A).

The familiar $y = m x + b$ best-fitting line to a dataset can be written in terms of $\bar{x}$,  $\bar{y}$, variance $s_{xx}$, and covariance $s_{xy}$ as follows:

$m = s_{xy}/s_{xx}$

$b = \bar{y} - m \bar{x}$.

By combining this relationship with the Welford algorithm and a buffer of size $n$, we can compute the best-fitting line to the last $n$ points in a stream of data at a per-sample computational cost of 18 flops plus the overhead of the [deque](https://cplusplus.com/reference/deque/deque/). Pretty neat!

### Test

I am mostly using this project to learn [CMake](https://cmake.org) and [Catch2](https://github.com/catchorg/Catch2). Catch2 version 3 can be installed as a precompiled library and has a slightly different API than the earlier, header file-only version. I've tried to use the currently-recommended syntax, in particular making floating point comparisons with `Catch2::Matchers` instead of `Approx()`. 

Most of the Catch2 examples I found were for the older versions of the framework and not helpful when working with the precompiled version. With the CMake build straightened out, I am happy with the low overhead of Catch2.

### Prerequisites
* C++23 is required for tests and examples, but not the `OnlineStatistics1D` and `OnlineStatistics2D` classes. (C++23 is nice; many common tasks can now be handled with the standard library.)
* Unit tests require Catch2 to be installed as library. To install Catch2 on Debian/Ubuntu, run `make install catch2`. This code was tested with catch2 version 3.4.0.

### Building
This project uses CMake.
```
mkdir build && cd build
cmake ..
make
```

### Run Tests
These use Catch2; the `-s` options enables verbose output.
```
./tests -s
```

### Run Example
```
./example
```

### Install
There is no install step defined at this time.


