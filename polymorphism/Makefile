CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

algorithm_test: main.cpp functions.cpp function.hpp solver.hpp algorithm.hpp
	$(CXX) $(CXXFLAGS) main.cpp functions.cpp -o algorithm_test

.PHONY: clean
clean:
	rm -f algorithm_test
