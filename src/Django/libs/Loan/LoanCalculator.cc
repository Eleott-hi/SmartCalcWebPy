#include "LoanCalculator.h"

namespace s21 {

LoanResult LoanCalculator::Calculate(LoanInfo info) {
  info.rate = info.rate / 100.0 / 12.0;

  return info.annuity ? Annuity(info) : Differentiated(info);
}

LoanResult LoanCalculator::Annuity(LoanInfo const& info) {
  LoanResult result(info.period);

  auto formula = [](double debth, double p, int monthes) {
    return debth * (p + (p / (pow((1. + p), (double)monthes) - 1.)));
  };

  double debth = info.amount;
  double sum_payment = 0;
  double payment = round(formula(debth, info.rate, info.period) * 100.0) / 100.0;

  for (int i = 0; i < info.period; i++) {
    double percent_part = debth * info.rate;
    double debth_part = payment - percent_part;
    double remain = debth - debth_part;

    result.remain.push_back(remain);
    result.percent.push_back(percent_part);
    result.debth.push_back(debth_part);
    result.payment.push_back(payment);

    sum_payment += payment;
    debth = remain;
    debth = round(debth * 100.0) / 100.0;
  }

  result.overpay = sum_payment - info.amount;
  result.all_sum = sum_payment;

  return result;
}

LoanResult LoanCalculator::Differentiated(LoanInfo const& info) {
  LoanResult result(info.period);

  double main_debt = info.amount / info.period;
  double remaining = info.amount;
  double sum_payment = 0;

  for (int i = 0; i < info.period; i++) {
    double remain = info.amount - (main_debt * (i + 1));
    double rate_payment = remaining * info.rate;
    double payment = main_debt + rate_payment;

    result.remain.push_back(remain);
    result.percent.push_back(rate_payment);
    result.debth.push_back(main_debt);
    result.payment.push_back(payment);

    sum_payment += payment;
    remaining = remain;
  }

  result.overpay = sum_payment - info.amount;
  result.all_sum = sum_payment;

  return result;
}
}  // namespace s21
