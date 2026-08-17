#include "function.hpp"

#include <cmath>

namespace roots {
namespace {

// Anonymous namespace: these names do not exist outside this translation unit,
// so no algorithm can #include, forward-declare, or special-case them.

class Quadratic final : public DifferentiableFunction {
public:
    double eval(double x) const override       { return x * x - 4.0; }
    double derivative(double x) const override { return 2.0 * x; }
    const char* name() const override          { return "x^2 - 4"; }
};

class Exponential final : public DifferentiableFunction {
public:
    double eval(double x) const override       { return std::exp(x) - 5.0; }
    double derivative(double x) const override { return std::exp(x); }
    const char* name() const override          { return "exp(x) - 5"; }
};

class CubeRoot final : public DifferentiableFunction {
public:
    // std::cbrt, not std::pow(x, 1.0/3.0): pow returns NaN for negative x.
    double eval(double x) const override       { return std::cbrt(x); }
    double derivative(double x) const override {
        const double c = std::cbrt(x);
        return 1.0 / (3.0 * c * c);
    }
    const char* name() const override          { return "cbrt(x)"; }
};

// The one place that knows the id -> class mapping.
std::unique_ptr<DifferentiableFunction> create(TestFunction id) {
    switch (id) {
        case TestFunction::Quadratic:   return std::make_unique<Quadratic>();
        case TestFunction::Exponential: return std::make_unique<Exponential>();
        case TestFunction::CubeRoot:    return std::make_unique<CubeRoot>();
    }
    return nullptr;
}

} // namespace

std::unique_ptr<const Function> makeFunction(TestFunction id) {
    return create(id);
}

std::unique_ptr<const DifferentiableFunction> makeDifferentiable(TestFunction id) {
    return create(id);
}

std::vector<TestCase> testCases() {
    return {
        {TestFunction::Quadratic,    0.0, 4.0, 2.0,            1e-3, true},
        {TestFunction::Exponential, -2.0, 2.0, std::log(5.0),  1e-3, true},
        // cbrt defeats every method that steps by slope, Newton included.
        {TestFunction::CubeRoot,    -1.0, 3.0, 0.0,            1e-3, false},
    };
}

} // namespace roots
