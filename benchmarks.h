#ifndef BENCHMARKS_H
#define BENCHMARKS_H

#include <vector>
#include <cmath>
#include "config.h"

class Benchmarks {
public:
    // 1. Sphere Function: f(x) = sum(x_i^2) 
    static double sphere(const std::vector<double>& x) {
        double sum = 0;
        for (int i = 0; i < DIMENSIONS; ++i) {
            sum += x[i] * x[i];
        }
        return sum;
    }

    // 2. Rosenbrock Function [cite: 975]
    static double rosenbrock(const std::vector<double>& x) {
        double sum = 0;
        for (int i = 0; i < DIMENSIONS - 1; ++i) {
            sum += 100 * pow(x[i+1] - x[i]*x[i], 2) + pow(x[i] - 1, 2);
        }
        return sum;
    }
};

#endif