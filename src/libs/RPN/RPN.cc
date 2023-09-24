#include "RPN.h"

#include <stack>
#include <stdexcept>

#include "algorithm.h"

namespace s21 {

template <typename... Args>
void Print(Args const &...args) {
  // #ifdef DEBUG
  ((std::cout << args << ' '), ...);
  std::cout << std::endl;
  // #endif
}

RPN::Lexems RPN::FormRPN(Lexems const &lexems) {
  Lexems rpn;
  std::stack<Lexem> stack;

  for (auto const &lexem : lexems) {
    if (lexem == Priority::NUM) {
      rpn.push_back(lexem);

    } else if (lexem == Priority::PARENTHESIS_OPEN) {
      stack.push(lexem);

    } else if (lexem == Priority::PARENTHESIS_CLOSE) {
      while (stack.top() != Priority::PARENTHESIS_OPEN) {
        rpn.push_back(Pop(stack));
      }
      stack.pop();

    } else {
      while (!stack.empty() &&
             (lexem < stack.top() ||
              lexem != Priority::POW && lexem == stack.top())) {
        rpn.push_back(Pop(stack));
      }
      stack.push(lexem);
    }
  }

  while (!stack.empty()) rpn.push_back(Pop(stack));

  return rpn;
}

double RPN::CalculateLexems(Lexems const &lexems, double x_value) {
  std::stack<double> stack;

  for (auto &lexem : lexems_) {
    if (lexem == Priority::NUM) {
      if (lexem == "x") lexem.value_ = x_value;
      stack.push(lexem.value_);

    } else if (lexem == Priority::FUN) {
      stack.push(lexem.func_(Pop(stack), 0.0));

    } else {
      double y = Pop(stack), x = Pop(stack);
      stack.push(lexem.func_(x, y));
    }
  }

  if (stack.size() != 1)
    throw std::invalid_argument("CalculateLexems: stack.size() != 1");

  return stack.top();
}

double RPN::Calculate(std::string const &expression, double x) {
  if (expression_ != expression) {
    auto lexems = Lexem::GetLexemList(expression);
    lexems_ = FormRPN(lexems);
    expression_ = expression;
  }

  return CalculateLexems(lexems_, x);
}

}  // namespace s21