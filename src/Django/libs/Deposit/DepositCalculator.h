#ifndef _DEPOSIT_H_
#define _DEPOSIT_H_

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "date.h"

namespace s21 {

enum Period { NONE, DAY, WEEK, MONTH, QUARTER, HALF_YEAR, YEAR };

struct DepositInput {
  date::sys_days date_start{};
  size_t term{};
  double percent{};
  double percent_max_without_bill{};
  double percent_bill{};
  double sum_in{};
  double sum_add{};
  double sum_sub{};
  Period cop_period{};
  Period add_period{};
  Period sub_period{};

  DepositInput() = default;
};

struct DepositOutput {
  double profite{};
  double bills{};
  double profit_wb{};
  double summary{};
  double income_sum{};

  DepositOutput() = default;
};

class DepositCalculator {
 public:
  DepositCalculator() = default;
  ~DepositCalculator() = default;
  static DepositOutput Calculate(const DepositInput &info);

 private:
  DepositCalculator(const DepositInput &info);

  void calculate_deposit();
  void calc_bills(date::sys_days cur_date, double &profit);
  void check_adding(const date::sys_days &cur_date, date::sys_days &add_date,
                    date::sys_days &sub_date);
  void add_money(bool add_operation, date::sys_days &operation_date);
  static bool check_leap_year(const date::sys_days &d);
  static double simple_percent(double sum_in, double percent, int days,
                               int leap_year);
  date::sys_days calc_next_date(const date::sys_days &day, Period period) const;
  date::sys_days _calc_next_date(const date::year_month_day &ymd) const;

 private:
  date::sys_days m_date_finish_;
  DepositInput m_info_;
  double m_income_sum_{};
  double m_bill_res_{};
  double m_profit_res_{};
  double m_percentage_{};
};

}  // namespace s21

#endif  // _DEPOSIT_H_
