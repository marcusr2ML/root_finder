#pragma once
#include "function.hpp"
#include "solver.hpp"

#include <cmath>
#include <memory>
#include <optional>

// The contributor's file: the only one that has to be written to add a method.
// Implement findZero() against the Function interface and leave makeAlgorithm
// alone — main.cpp knows nothing else about what lives in here.
//
// Needs a derivative? Take a const DifferentiableFunction& instead, here and in
// makeAlgorithm; a function with no analytic derivative then fails to compile.

namespace roots {

// Secant method: x_next = b - f(b) * (b - a) / (f(b) - f(a))
class Algorithm final : public Solver {
public:
    Algorithm(const Function& f, double x0, double x1, double tol = 1e-6)
        : f_(f), x0_(x0), x1_(x1), tol_(tol) {}

    std::optional<double> findZero() const override {
        double a = x0_, b = x1_;
        double fa = f_(a), fb = f_(b);
        if (!std::isfinite(fa) || !std::isfinite(fb)) return std::nullopt;

        for (int i = 0; i < 100; ++i) {
            if (fb == 0.0) return b;

            const double denom = fb - fa;
            if (!std::isfinite(denom) || std::abs(denom) < 1e-12) return std::nullopt;

            const double next = b - fb * (b - a) / denom;
            // Runaway guard: the secant step is unbounded when the two points
            // straddle a near-flat stretch, so |next - b| < tol never fires.
            if (!std::isfinite(next) || std::abs(next) > 1e12) return std::nullopt;

            if (std::abs(next - b) < tol_) return next;

            a = b;  fa = fb;
            b = next;
            fb = f_(b);
            if (!std::isfinite(fb)) return std::nullopt;
        }
        return std::nullopt;  // exhausting the budget is a failure
    }

private:
    const Function& f_;
    double x0_, x1_, tol_;
};

// Factory the harness calls. Two starting points; use or ignore them as the
// method requires.
inline std::unique_ptr<const Solver>
makeAlgorithm(const Function& f, double a, double b) {
    return std::make_unique<Algorithm>(f, a, b);
}

} // namespace roots
