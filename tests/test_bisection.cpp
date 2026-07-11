#include "Bisection.hpp"

#include <iostream>
#include <cmath>

int main()
{
    auto f = [](double x)
    {
        return x*x - 2.0;
    };

    try
    {
        double root = root_finder::Bisection(
            f,
            0.0,     // a
            2.0      // b
        );

        std::cout << "Root = " << root << '\n';
        std::cout << "sqrt(2) = " << std::sqrt(2.0) << '\n';
        std::cout << "Error = "
                  << std::abs(root - std::sqrt(2.0))
                  << '\n';
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
