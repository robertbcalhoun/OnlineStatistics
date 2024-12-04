OnlineStatistics
----------------
Classes to compute the running mean, variance and covariance of single-variable and two-variable distributions
using the online Welford algorithm. The code derives from the Wikipedia article [Algorithms for calculating variance](https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance).

I am mostly using this project to learn [CMake](https://cmake.org) and [Catch2](https://github.com/catchorg/Catch2). Catch2 version 3 can be installed as a precompiled library and has a slightly different API than the earlier, header file-only version. I've tried to use the currently-recommended syntax, in particular making floating point comparisons with `Catch2::Matchers` instead of `Approx()`. 

Most of the Catch2 examples I found were for the older versions of the framework and not helpful when working with the precompiled version. With the CMake build straightened out, I am happy with the low overhead of Catch2.

### Prerequisites
* C++23 is required for tests and examples, but not the `OnlineStatistics1D` and `OnlineStatistics2D` classes.
* Unit tests require Catch2.

To install Catch2 on Debian/Ubuntu, run:
```
sudo make install catch2
```
As of this writing, catch2 version 3.4.0 will be installed.

### Minimal Example
```
#include <iostream>
#include "OnlineStatistics.h"

int main() {
    auto stats = OnlineStatistics1D();
    stats.Insert(1.0);
    stats.Insert(2.0);
    stats.Insert(3.0);
    double mean = stats.Mean();
    double var = stats.Variance();
    std::cout << "mean: " << mean << " var: " << var << std::endl;
    exit(0);
}

Outputs:
mean: 2 var: 0.666667
```

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
