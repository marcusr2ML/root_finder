#pragma once

#include <Eigen/Dense>
#include <functional>
#include <stdexcept>
#include <cmath>

namespace root_finder
{

inline double Newton(
    const std::function<double(double)>& f,
    const std::function<double(double)>& df,
    double x0,
    double tol = 1e-10,
    int max_iter = 100)
{
    Eigen::VectorXd x(1);
    x(0) = x0;

    for (int i = 0; i < max_iter; ++i)
    {
        double fx = f(x(0));
        double dfx = df(x(0));

        if (std::abs(dfx) < 1e-14)
            throw std::runtime_error("Derivative too small.");

        Eigen::MatrixXd J(1,1);
        J(0,0) = dfx;

        Eigen::VectorXd rhs(1);
        rhs(0) = -fx;

        Eigen::VectorXd delta = J.fullPivLu().solve(rhs);

        x += delta;

        if (delta.norm() < tol)
            return x(0);
    }

    throw std::runtime_error("Newton failed to converge.");
}

} // namespace root_finder
