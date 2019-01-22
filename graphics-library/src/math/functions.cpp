#include "math/functions.hpp"

#include <cstdio>
#include <vector>

namespace gl::math {

    const int BINOMIAL_MAX_DEGREE = 31;

    // https://en.wikipedia.org/wiki/Binomial_coefficient#Recursive_formula
    int binomialCoeff(int n, int k) {
        static std::vector<int> cache(sumToN(BINOMIAL_MAX_DEGREE + 1));

        int nIndex { sumToN(n) };
        if (cache[nIndex + k] > 0) {
            return cache[nIndex + k];
        }

        static int baseN { 0 };
        static int baseK { 0 };

        for (int i { baseN }; i <= n; i++) {
            for (int j { baseK }; j <= i; j++) {
                if (j == 0 || i == j) {
                    cache[sumToN(i) + j] = 1;
                } else {
                    int prevIIndex { sumToN(i - 1) };
                    cache[sumToN(i) + j] = cache[prevIIndex + j - 1] + cache[prevIIndex + j];
                }
            }
        }

        baseN = n;
        baseK = k;
        
        return cache[nIndex + k];
    }

    int sumToN(int n) {
        return n * (n + 1) / 2;
    }
}