#ifndef _CREDIT_H_
#define _CREDIT_H_

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

namespace s21 {

class Credit {
 public:
  struct Credit_info {
    double credit_sum = 0;
    double credit_rate = 0;
    int credit_term = 0;
    bool annuity = true;
  };

  Credit() = default;
  ~Credit() = default;
  void calculate_credit();
  void set_credit_info(const Credit_info &info);
  std::vector<std::string> get_info() const;

 private:
  Credit_info info_;
  std::ostringstream payment_, overpay_, all_sum_;

  void annuity();
  void differentiated();
};

}  // namespace s21

#endif  // _CREDIT_H_
