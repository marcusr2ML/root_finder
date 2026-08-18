#pragma once
#include "function.hpp"
#include "solver.hpp"

#include <cmath>
#include <memory>
#include <optional>

// BROKEN COPY — for exercising the CI gate. The secant update carries the new
// point forward but not its function value, so `fa` stays f(x0) forever and the
// step is computed from a slope that was never there. See `a = b;` below.

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
            if (!std::isfinite(next) || std::abs(next) > 1e12) return std::nullopt;

            if (std::abs(next - b) < tol_) return next;

            a = b;              // BUG: `fa = fb;` belongs here
            b = next;
            fb = f_(b);
            if (!std::isfinite(fb)) return std::nullopt;
        }
        return std::nullopt;
    }

private:
    const Function& f_;
    double x0_, x1_, tol_;
};

inline std::unique_ptr<const Solver>
makeAlgorithm(const Function& f, double a, double b) {
    return std::make_unique<Algorithm>(f, a, b);
}

} // namespace roots
