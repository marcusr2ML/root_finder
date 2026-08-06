#include <stdio.h>
#include <cmath>
#include "unittests.hpp"

// --- Unit Testing Engine ---
void verifyRoot(UnitTests* solver, double expected, const char* algorithmName) {
    double actual = solver->findZero();

    if (std::abs(expected - actual) < 0.001) {
        printf("[PASS] %s successfully found root at: %f\n", algorithmName, actual);
    } else {
        printf("[FAIL] %s expected %f but got %f\n", algorithmName, expected, actual);
    }
}

int main() {
    double expected_root = 2.0;

    // Use polymorphic pointers to switch algorithms at runtime
    UnitTests* newton = new NewtonSolver(3.0);          // Initial guess = 3
    UnitTests* bisection = new BisectionSolver(0.5, 4.0); // Bracket bounds = [0.5, 4.0]

    printf("--- Running Polynomial Zero Finder Tests ---\n");
    verifyRoot(newton, expected_root, "Newton-Raphson");
    verifyRoot(bisection, expected_root, "Bisection Method");

    // Memory Cleanup
    delete newton;
    delete bisection;

    return 0;
}
