#pragma once
#include "function.hpp"

#include <cmath>
#include <optional>
#include <utility>

namespace roots {

// The abstract base class a contributor plugs into. Solvers depend only on the
// Function interface. nullopt means "no trustworthy root" — 0.0 is a legitimate
// answer here and cannot double as a failure code.

class Solver {
public:
    virtual ~Solver() = default;
    virtual std::optional<double> findZero() const = 0;
    virtual const char* name() const { return "Algorithm"; }
};

class BisectionSolver final : public Solver {
public:
    BisectionSolver(const Function& f, double a, double b, double tol = 1e-4)
        : f_(f), a_(a), b_(b), tol_(tol) {}

    std::optional<double> findZero() const override {
        double a = a_, b = b_;
        if (a > b) std::swap(a, b);
        double fa = f_(a), fb = f_(b);

        // Finiteness before the sign test: NaN slips past `fa * fb >= 0`.
        if (!std::isfinite(fa) || !std::isfinite(fb)) return std::nullopt;
        if (std::signbit(fa) == std::signbit(fb))     return std::nullopt;

        double m = a;
        while (b - a >= tol_) {
            m = a + (b - a) / 2.0;
            const double fm = f_(m);
            if (!std::isfinite(fm)) return std::nullopt;
            if (fm == 0.0 || m == a || m == b) return m;  // m==a||m==b: ULP limit
            if (std::signbit(fm) != std::signbit(fa)) b = m;
            else { a = m; fa = fm; }
        }
        return m;
    }

    const char* name() const override { return "Bisection"; }

private:
    const Function& f_;
    double a_, b_, tol_;
};

class NewtonSolver final : public Solver {
public:
    NewtonSolver(const DifferentiableFunction& f, double x0, double tol = 1e-6)
        : f_(f), x0_(x0), tol_(tol) {}

    std::optional<double> findZero() const override {
        double x = x0_;
        for (int i = 0; i < 100; ++i) {
            const double dfx = f_.derivative(x);
            if (!std::isfinite(dfx) || std::abs(dfx) < 1e-12) return std::nullopt;

            const double next = x - f_(x) / dfx;
            // Runaway guard: on cbrt the iteration is exactly x -> -2x.
            if (!std::isfinite(next) || std::abs(next) > 1e12) return std::nullopt;

            if (std::abs(next - x) < tol_) return next;
            x = next;
        }
        return std::nullopt;  // exhausting the budget is a failure
    }

    const char* name() const override { return "Newton"; }

private:
    const DifferentiableFunction& f_;
    double x0_, tol_;
};

} // namespace roots
