#include "../headers/Credit.h"

namespace s21 {

double an_formula(double debth, double p, int monthes) {
  return debth * (p + (p / (pow((1. + p), (double)monthes) - 1.)));
}

std::vector<std::string> Credit::get_info() const {
  return std::vector<std::string>{payment_.str(), overpay_.str(),
                                  all_sum_.str()};
}

void Credit::set_credit_info(const Credit_info &info) {
  info_ = info;
  info_.credit_rate = info.credit_rate / 100.0 / 12.0;
}

void Credit::calculate_credit() {
  payment_.clear(), payment_.str("");
  overpay_.clear(), overpay_.str("");
  all_sum_.clear(), all_sum_.str("");

  info_.annuity ? annuity() : differentiated();
}

void Credit::annuity() {
  double debth = info_.credit_sum;
  double sum_payment = 0;
  double payment =
      round(an_formula(debth, info_.credit_rate, info_.credit_term) * 100) /
      100;

  for (int i = 0; i < info_.credit_term; i++) {
    double percent_part = debth * info_.credit_rate;
    double debth_part = payment - percent_part;
    double remain = debth - debth_part;
    sum_payment += payment;
    debth = remain;
    debth = round(debth * 100) / 100;
  }

  payment_ << std::fixed << std::setprecision(2) << payment;
  overpay_ << std::fixed << std::setprecision(2)
           << sum_payment - info_.credit_sum;
  all_sum_ << std::fixed << std::setprecision(2) << sum_payment;
}

void Credit::differentiated() {
  double main_debt = info_.credit_sum / info_.credit_term;
  double remaining = info_.credit_sum;
  double sum_payment = 0;
  double max = -INFINITY;
  double min = INFINITY;

  for (int i = 0; i < info_.credit_term; i++) {
    double remain = info_.credit_sum - (main_debt * (i + 1));
    double rate_payment = remaining * info_.credit_rate;
    double monthly_payment = main_debt + rate_payment;
    if (min > monthly_payment) min = monthly_payment;
    if (max < monthly_payment) max = monthly_payment;
    sum_payment += monthly_payment;
    remaining = remain;
  }

  payment_ << std::fixed << std::setprecision(2) << min << " - " << max;
  overpay_ << std::fixed << std::setprecision(2) << sum_payment - info_.credit_sum;
  all_sum_ << std::fixed << std::setprecision(2) << sum_payment;
}
}  // namespace s21
