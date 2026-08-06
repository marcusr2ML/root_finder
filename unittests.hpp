#pragma once
#include <cstdio>
#include <cmath>

// --- Base interface ---
class UnitTests {
protected:
    double f(double x) {
        return x * x - 4.0;
    }

    double delf(double x) {
        return 2 * x;
    }

public:
    virtual ~UnitTests() {}
    virtual double findZero() = 0;
};

// --- Newton-Raphson ---
class NewtonSolver : public UnitTests {
    double init_guess;
    double tol;

public:
    NewtonSolver(double initial_guess, double tolerance = 1e-6)
        : init_guess(initial_guess), tol(tolerance) {}

    double findZero() override {
        double x = init_guess;

        // Newton's formula: x_next = x - f(x)/f'(x)
        for (int i = 0; i < 100; ++i) {
            double df = delf(x);
            if (std::abs(df) < 1e-9) break; // Avoid division by zero

            double next_x = x - (f(x) / df);

            if (std::abs(next_x - x) < tol) {
                return next_x; // Convergence achieved
            }
            x = next_x;
        }
        return x;
    }
};

// --- Bisection ---
class BisectionSolver : public UnitTests {
private:
    double lower_bound;
    double upper_bound;
    double tolerance;

public:
    BisectionSolver(double a, double b, double tol = 0.0001)
        : lower_bound(a), upper_bound(b), tolerance(tol) {}

    double findZero() override {
        double a = lower_bound;
        double b = upper_bound;
        double midpoint = a;

        // Bisection requires f(a) and f(b) to have opposite signs
        if (f(a) * f(b) >= 0) {
            printf("[ERROR] Bisection invalid bounds: f(a) and f(b) must have opposite signs.\n");
            return 0.0;
        }

        while ((b - a) >= tolerance) {
            midpoint = (a + b) / 2.0;

            // Check if midpoint is the root
            if (std::abs(f(midpoint)) < 1e-9) {
                break;
            }
            // Decide which half to keep
            if (f(midpoint) * f(a) < 0) {
                b = midpoint;
            } else {
                a = midpoint;
            }
        }
        return midpoint;
    }
};
