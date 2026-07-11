#include "Newton.hpp"

#include <iostream>
#include <cmath>

int main()
{
    auto f = [](double x)
    {
        return x * x - 2.0;
    };

    auto df = [](double x)
    {
        return 2.0 * x;
    };

    try
    {
        double root = root_finder::Newton(f, df, 1.0);

        std::cout << "Root = " << root << '\n';
        std::cout << "sqrt(2) = " << std::sqrt(2.0) << '\n';
        std::cout << "Error = " << std::abs(root - std::sqrt(2.0)) << '\n';
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
