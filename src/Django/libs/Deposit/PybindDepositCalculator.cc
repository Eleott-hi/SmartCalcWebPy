#include <pybind11/chrono.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "DepositCalculator.h"
namespace py = pybind11;

PYBIND11_MODULE(PybindDepositCalculator, m) {
  py::enum_<s21::Period>(m, "Period")
      .value("NONE", s21::Period::NONE)
      .value("DAY", s21::Period::DAY)
      .value("WEEK", s21::Period::WEEK)
      .value("MONTH", s21::Period::MONTH)
      .value("QUARTER", s21::Period::QUARTER)
      .value("HALF_YEAR", s21::Period::HALF_YEAR)
      .value("YEAR", s21::Period::YEAR);

  py::class_<s21::DepositInput>(m, "DepositInput")
      .def(py::init<>())
      .def_readwrite("date_start", &s21::DepositInput::date_start)
      .def_readwrite("term", &s21::DepositInput::term)
      .def_readwrite("percent", &s21::DepositInput::percent)
      .def_readwrite("percent_max_without_bill",
                     &s21::DepositInput::percent_max_without_bill)
      .def_readwrite("percent_bill", &s21::DepositInput::percent_bill)
      .def_readwrite("sum_in", &s21::DepositInput::sum_in)
      .def_readwrite("sum_add", &s21::DepositInput::sum_add)
      .def_readwrite("sum_sub", &s21::DepositInput::sum_sub)
      .def_readwrite("cop_period", &s21::DepositInput::cop_period)
      .def_readwrite("add_period", &s21::DepositInput::add_period)
      .def_readwrite("sub_period", &s21::DepositInput::sub_period);

  py::class_<s21::DepositOutput>(m, "DepositOutput")
      .def(py::init<>())
      .def_readwrite("income_sum", &s21::DepositOutput::income_sum)
      .def_readwrite("profite", &s21::DepositOutput::profite)
      .def_readwrite("bills", &s21::DepositOutput::bills)
      .def_readwrite("profit_wb", &s21::DepositOutput::profit_wb)
      .def_readwrite("summary", &s21::DepositOutput::summary);

  py::class_<s21::DepositCalculator>(m, "DepositCalculator")
      .def(py::init<>())
      .def("Calculate", &s21::DepositCalculator::Calculate);
}
