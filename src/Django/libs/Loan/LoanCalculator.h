#ifndef _CREDIT_H_
#define _CREDIT_H_

#include <cmath>
#include <vector>

namespace s21 {

struct LoanInfo {
  double amount = 0;
  double rate = 0;
  int period = 0;
  bool annuity = true;

  LoanInfo() = default;
};

struct LoanResult {
  std::vector<double> payment;
  std::vector<double> debth;
  std::vector<double> percent;
  std::vector<double> remain;
  double overpay;
  double all_sum;

  LoanResult() = default;
  LoanResult(int period) {
    payment.reserve(period);
    debth.reserve(period);
    percent.reserve(period);
    remain.reserve(period);
  }
};

class LoanCalculator {
 public:
  LoanCalculator() = default;
  ~LoanCalculator() = default;
  static LoanResult Calculate(LoanInfo info);

 private:
  static LoanResult Annuity(LoanInfo const& info);
  static LoanResult Differentiated(LoanInfo const& info);
};

}  // namespace s21

#endif  // _CREDIT_H_
