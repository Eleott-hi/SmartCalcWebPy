#ifndef _RPN_H_
#define _RPN_H_

#include "Lexem.h"

namespace s21 {

class RPN {
 public:
  RPN() = default;
  ~RPN() = default;

  double Calculate(const std::string& expression, double x = 0.0);

 private:
  using Lexems = std::vector<Lexem>;
  Lexems lexems_;
  std::string expression_;

  Lexems FormRPN(Lexems const& lexems);
  double CalculateLexems(Lexems const& lexems, double x);
};

}  // namespace s21

#endif  // _RPN_CALCULATION_H_
