#include <pybind11/pybind11.h>

#include "RPN_Calculation.h"
namespace py = pybind11;

PYBIND11_MODULE(SmartCalc, m) {
  py::class_<s21::RPN_Calculation>(m, "RPN")
      .def(py::init<>())
      .def("calc", &s21::RPN_Calculation::calc, py::arg("str"),
           py::arg("x") = 0)
      .def("form_final_expression",
           &s21::RPN_Calculation::form_final_expression)
      .def("check_expression", &s21::RPN_Calculation::check_expression);
}
