#include "DepositCalculator.h"

namespace s21 {

bool DepositCalculator::check_leap_year(const date::sys_days &d) {
  return date::year_month_day(d).year().is_leap();
}

double DepositCalculator::simple_percent(double sum_in, double percent,
                                         int days, int leap_year) {
  return sum_in * days * percent / (leap_year ? 366. : 365.);
}

static bool IsLastDayOfYear(date::year_month_day const &cur_ymd) {
  return cur_ymd.month() == date::December &&  //
         cur_ymd.day() == date::day{31};
}

date::sys_days DepositCalculator::calc_next_date(const date::sys_days &day,
                                                 Period period) const {
  date::sys_days res;

  switch (period) {
    case DAY:
      res = day + date::days{1};
      break;
    case WEEK:
      res = day + date::weeks{7};
      break;
    case MONTH:
      res = _calc_next_date(date::year_month_day{day} + date::months{1});
      break;
    case QUARTER:
      res = _calc_next_date(date::year_month_day{day} + date::months{3});
      break;
    case HALF_YEAR:
      res = _calc_next_date(date::year_month_day{day} + date::months{6});
      break;
    case YEAR:
      res = _calc_next_date(date::year_month_day{day} + date::years{1});
      break;

    default:
      break;
  }
  return res;
}

date::sys_days DepositCalculator::_calc_next_date(
    const date::year_month_day &ymd) const {
  date::year_month_day tmp = {ymd.year() / ymd.month() /
                              date::year_month_day{m_info_.date_start}.day()};
  return ymd.ok() ? tmp
                  : date::year_month_day{tmp.year() / tmp.month() /
                                         date::literals::last};
}

DepositCalculator::DepositCalculator(const DepositInput &info)
    : m_info_(info),
      m_date_finish_(_calc_next_date(date::year_month_day{info.date_start} +
                                     date::months{info.term})) {
  m_info_.percent /= 100.0;
  m_info_.percent_max_without_bill /= 100.0;
  m_info_.percent_bill /= 100.0;
  m_percentage_ = m_info_.percent - m_info_.percent_max_without_bill;
}

DepositOutput DepositCalculator::Calculate(const DepositInput &info) {
  DepositCalculator deposit(info);
  deposit.calculate_deposit();

  return {
      deposit.m_profit_res_,                        //
      deposit.m_bill_res_,                          //
      deposit.m_profit_res_ - deposit.m_bill_res_,  //
      deposit.m_info_.sum_in,                       //
      deposit.m_income_sum_,                        //
  };
}

void DepositCalculator::calculate_deposit() {
  m_bill_res_ = 0;
  m_profit_res_ = 0;
  double income = 0;
  double profit = 0;
  bool complicated = m_info_.cop_period != NONE;

  auto cur_date = m_info_.date_start;
  auto add_date = calc_next_date(cur_date, m_info_.add_period);
  auto sub_date = calc_next_date(cur_date, m_info_.sub_period);
  auto cop_date = calc_next_date(cur_date,  //
                                 complicated ? m_info_.cop_period : MONTH);

  auto round_100 = [](double num) { return round(num * 100.0) / 100.0; };

  while (cur_date != m_date_finish_) {
    cur_date += date::days{1};

    income += simple_percent(m_info_.sum_in,            //
                             m_info_.percent,           //
                             1,                         //
                             check_leap_year(cur_date)  //
    );

    if (cur_date == cop_date) {
      m_profit_res_ += round_100(income);
      profit += income;

      if (complicated) m_info_.sum_in += round_100(income);

      cop_date = calc_next_date(cur_date,  //
                                complicated ? m_info_.cop_period : MONTH);

      income = 0;
    }

    check_adding(cur_date, add_date, sub_date);
    calc_bills(cur_date, profit);
  }
}

void DepositCalculator::calc_bills(date::sys_days cur_date, double &profit) {
  auto cur_ymd = date::year_month_day{cur_date};

  if ((IsLastDayOfYear(cur_ymd) || cur_date == m_date_finish_)) {
    if (cur_ymd.year() > date::year{2022}) {
      double billAmount =
          (profit - 1000000 * m_info_.percent_max_without_bill) *
          m_info_.percent_bill;

      if (billAmount > 0.0) m_bill_res_ += billAmount;
    }

    profit = 0.0;
  }
}

void DepositCalculator::check_adding(date::sys_days const &cur_date,  //
                                     date::sys_days &add_date,        //
                                     date::sys_days &sub_date) {
  if (m_info_.add_period != NONE && cur_date == add_date)
    add_money(true, add_date);

  if (m_info_.sub_period != NONE && cur_date == sub_date)
    add_money(false, sub_date);
}

void DepositCalculator::add_money(bool add_operation,
                                  date::sys_days &operation_date) {
  m_income_sum_ += add_operation ? m_info_.sum_add : -m_info_.sum_sub;
  m_info_.sum_in += add_operation ? m_info_.sum_add : -m_info_.sum_sub;

  operation_date = calc_next_date(operation_date,
                                  add_operation ? m_info_.add_period  //
                                                : m_info_.sub_period);
}

}  // namespace s21
