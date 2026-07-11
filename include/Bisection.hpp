#pragma once

#include <boost/math/special_functions.hpp>
#include <functional>
#include <stdexcept>
#include <cmath>

namespace root_finder
{

inline double Bisection(
    const std::function<double(double)>& f,
    double a,
    double b,
    double tol = 1e-10,
    int max_iter = 100)
{
    double fa = f(a);
    double fb = f(b);

    if (fa * fb > 0)
        throw std::runtime_error("Interval does not bracket a root.");

    for (int i = 0; i < max_iter; ++i)
    {
        // Use Boost.Math for a utility operation
        double mid = boost::math::constants::half<double>() * (a + b);

        double fm = f(mid);

        if (std::abs(fm) < tol)
            return mid;

        if (fa * fm < 0)
        {
            b = mid;
            fb = fm;
        }
        else
        {
            a = mid;
            fa = fm;
        }
    }

    throw std::runtime_error("Bisection failed.");
}

}
