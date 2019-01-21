#include "math/functions.hpp"

namespace gl::math {

    const int BINOMIAL_MAX_DEGREE = 4;

    // https://en.wikipedia.org/wiki/Binomial_coefficient#Recursive_formula
    int binomialCoeff(int n, int k) {
        static int cache[BINOMIAL_MAX_DEGREE][BINOMIAL_MAX_DEGREE] { 0 };
        if (k == 0 || n == k)
            cache[n][k] = 1;
        if (cache[n][k] == 0)
            cache[n][k] = binomialCoeff(n - 1, k - 1) + binomialCoeff(n - 1, k);
        return cache[n][k]; 
    }
}