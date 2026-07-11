**This README was AI generated**
# Root Finder

A modern C++ library for implementing and testing numerical root-finding algorithms while exploring dependency management, package integration, and CI/CD workflows.

## Overview

This project began as a simple implementation of classical root-finding methods but has evolved into a software engineering project focused on modular design and automated testing.

Each algorithm is developed as an independent component with its own external dependencies. This allows the project to explore how different numerical libraries interact within a larger package and how new functionality can be added without affecting existing code.

The long-term objective is to create a framework where contributors can implement a new algorithm, declare its dependencies and requirements, and have it automatically built and tested through a generic CI/CD pipeline.

## Current Algorithms

### Newton's Method

- Uses **Eigen** for linear algebra.
- Demonstrates integration with a header-only external dependency.
- Provides a simple implementation of Newton's method for one-dimensional root finding.

### Bisection Method

- Uses **Boost.Math** as an external dependency.
- Demonstrates integrating a different numerical library while maintaining the same project interface.
- Implements the classical bisection algorithm for one-dimensional root finding.

## Project Goals

The objectives of this project are to:

- Build a collection of reusable root-finding algorithms.
- Keep each algorithm modular and independently maintainable.
- Explore dependency management using **CMake**.
- Investigate compatibility and transitive dependency issues.
- Develop a generic testing framework that can validate any registered algorithm.
- Automate building and testing using **GitHub Actions**.
- Make it easy for contributors to add new algorithms with minimal changes to the existing codebase.

## Project Structure

```text
root_finder/
├── include/
│   ├── Newton.hpp
│   └── Bisection.hpp
├── tests/
│   ├── test_newton.cpp
│   └── test_bisection.cpp
├── CMakeLists.txt
└── README.md
```

## Dependencies

Current external libraries:

- **Eigen**
- **Boost.Math**

Future algorithms may introduce additional dependencies such as:

- LAPACK
- BLAS
- SuiteSparse
- Other numerical libraries

A primary goal of this project is to study how these dependencies interact within a growing C++ package.

## Building

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Running the Tests

```bash
./test_newton
./test_bisection
```

## Future Work

- Add additional root-finding algorithms.
- Implement automatic algorithm registration.
- Build a generic test framework for all algorithms.
- Add continuous integration with GitHub Actions.
- Test compatibility across multiple dependency versions.
- Add benchmarking and performance comparisons.
- Package the library for installation with CMake.

## License

This project is released under the MIT License.
