#pragma once
#include <memory>
#include <optional>
#include <vector>

namespace roots {

// The only view a contributor gets of a test function: evaluate it, maybe
// differentiate it. No concrete class is named here, so nothing downstream can
// depend on a specific formula.

class Function {
public:
    virtual ~Function() = default;
    virtual double eval(double x) const = 0;
    virtual const char* name() const = 0;

    double operator()(double x) const { return eval(x); }
};

// Split out so a derivative-based algorithm is type-checked at compile time.
class DifferentiableFunction : public Function {
public:
    virtual double derivative(double x) const = 0;
};

enum class TestFunction {
    Quadratic,    // one root at +2 on [0,4]
    Exponential,  // one root at ln(5) ~ 1.6094 on [-2,2]
    CubeRoot      // root at 0; Newton diverges on it
};

// nullptr for an unknown id.
std::unique_ptr<const Function> makeFunction(TestFunction id);

// nullptr if that id has no analytic derivative.
std::unique_ptr<const DifferentiableFunction> makeDifferentiable(TestFunction id);

// One judged case: the id, the two starting points handed to the algorithm, and
// the answer it has to land on. `expected` empty means the correct outcome is
// "no root". Only `required` cases decide the exit code; the rest are reported
// for information, because no single method handles every function.
struct TestCase {
    TestFunction id;
    double a, b;
    std::optional<double> expected;
    double tol;
    bool required;
};

std::vector<TestCase> testCases();

} // namespace roots
