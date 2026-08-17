#define NPY_NO_DEPRECATED_API NPY_2_0_API_VERSION
#include <boost/python.hpp>
#include <numpy/arrayobject.h>
#include <string>

std::string greet(const std::string& name) {
    return "Hello, " + name + "!";
}

// Manually mirrors numpy < 2.0's PyArray_Descr layout (do NOT use numpy's own struct)
struct OldPyArrayDescr {
    PyObject_HEAD
    PyTypeObject* typeobj;
    char kind;
    char type;
    char byteorder;
    char flags;
    int type_num;
    int elsize;      // <-- was int pre-2.0, is npy_intp (8 bytes) in 2.0+
    int alignment;
};

double sum_array(boost::python::object arr) {
    PyArrayObject* np_arr = reinterpret_cast<PyArrayObject*>(arr.ptr());
    PyObject* descr_obj = reinterpret_cast<PyObject*>(PyArray_DESCR(np_arr));

    // Bypass PyArray_ITEMSIZE() — read elsize directly via the OLD struct layout
    OldPyArrayDescr* old_view = reinterpret_cast<OldPyArrayDescr*>(descr_obj);
    int claimed_elsize = old_view->elsize;

    double* data = static_cast<double*>(PyArray_DATA(np_arr));
    npy_intp n = PyArray_SIZE(np_arr);
    double total = 0.0;
    for (npy_intp i = 0; i < n; ++i) total += data[i];

    printf("claimed elsize via old struct layout: %d (should be 8 for float64)\n", claimed_elsize);
    return total;
}

static void* init_numpy() {
    import_array();
    return nullptr;
}

BOOST_PYTHON_MODULE(abi_result) {
    init_numpy();
    boost::python::def("greet", greet);
    boost::python::def("sum_array", sum_array);
}
