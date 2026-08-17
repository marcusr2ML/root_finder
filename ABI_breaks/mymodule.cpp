#include <boost/python.hpp>
#include <string>

std::string greet(const std::string& name) {
    return "Hello, " + name + "!";
}

BOOST_PYTHON_MODULE(abi_result) {
    boost::python::def("greet", greet);
}
