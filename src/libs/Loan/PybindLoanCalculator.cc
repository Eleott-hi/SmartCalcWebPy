#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "LoanCalculator.h"
namespace py = pybind11;

PYBIND11_MODULE(PybindLoanCalculator, m) {
  py::class_<s21::LoanInfo>(m, "LoanInfo")
      .def(py::init<>())
      .def_readwrite("sum", &s21::LoanInfo::sum)
      .def_readwrite("rate", &s21::LoanInfo::rate)
      .def_readwrite("term", &s21::LoanInfo::term)
      .def_readwrite("annuity", &s21::LoanInfo::annuity);

  py::class_<s21::LoanResult>(m, "LoanResult")
      .def(py::init<>())
      .def_readwrite("debth", &s21::LoanResult::debth)
      .def_readwrite("remain", &s21::LoanResult::remain)
      .def_readwrite("percent", &s21::LoanResult::percent)
      .def_readwrite("payment", &s21::LoanResult::payment)
      .def_readwrite("overpay", &s21::LoanResult::overpay)
      .def_readwrite("all_sum", &s21::LoanResult::all_sum);

  py::class_<s21::LoanCalculator>(m, "LoanCalculator")
      .def(py::init<>())
      .def("Calculate", &s21::LoanCalculator::Calculate);
}
