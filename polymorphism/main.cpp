#include "algorithm.hpp"
#include "function.hpp"
#include "solver.hpp"

#include <cmath>
#include <cstdio>
#include <optional>

using namespace roots;

namespace {

// Judges one solver on one case and prints the row. Nothing here names a
// formula or a method: the label comes from Solver::name(), the answer from
// the hidden catalog.
bool judge(const Solver& s, const Function& f, const TestCase& c) {
    const std::optional<double> root = s.findZero();

    const bool ok = root ? (c.expected && std::abs(*root - *c.expected) < c.tol)
                         : !c.expected.has_value();

    std::printf("[%s]%s %-10s %-12s ",
                ok ? "PASS" : "FAIL",
                c.required ? " " : "*",
                s.name(), f.name());
    if (root) std::printf("root = %+.10f\n", *root);
    else      std::printf("no root found\n");

    return ok;
}

} // namespace

int main() {
    int failures = 0;

    std::printf("--- Reference solvers ---\n");
    for (const TestCase& c : testCases()) {
        auto f = makeFunction(c.id);
        judge(BisectionSolver(*f, c.a, c.b), *f, c);

        // A one-point method gets b; f'(a) is zero for the quadratic.
        if (auto df = makeDifferentiable(c.id))
            judge(NewtonSolver(*df, c.b), *df, c);
    }

    std::printf("--- Contributed algorithm ---\n");
    for (const TestCase& c : testCases()) {
        auto f = makeFunction(c.id);
        const bool ok = judge(*makeAlgorithm(*f, c.a, c.b), *f, c);

        if (!ok && c.required) ++failures;
    }

    std::printf("\n%d required case(s) failed  (* = informational)\n", failures);
    return failures == 0 ? 0 : 1;
}
