OnlineStatistics
----------------

Classes to compute the running mean, variance and covariance of a distribution
using the online [Welford algorithm](https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance).


Prerequisites
-------------
* C++23
* Unit tests require [Catch2](https://github.com/catchorg/Catch2). On Ubuntu 24, it is suffience to `sudo make install catch2`. This will install `catch2` version 3.4.0.

Building
--------
```
mkdir build && cd build
cmake ..
make
```

