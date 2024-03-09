#include <pybind11/pybind11.h>

#include "RPN.h"
namespace py = pybind11;

PYBIND11_MODULE(PybindRPN, m) {
  py::class_<s21::RPN>(m, "RPN")
      .def(py::init<>())
      .def("Calculate", &s21::RPN::Calculate, py::arg("expression"),
           py::arg("x") = 0);
}
